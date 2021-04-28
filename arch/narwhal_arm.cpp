#include <algorithm>
#include <vector>
#include <stdio.h>
#include <unicorn/unicorn.h>

#include "narwhal_arm.h"
#include "../narwhal_context.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_memory_editor.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

#define ARM_CODE "\x37\x00\xa0\xe3\x03\x10\x42\xe0" // mov r0, #0x37; sub r1, r2, r3
#define ADDRESS 0x10000

void show_arm_cpu_window();
void show_arm_memory_window();
bool render_memory_map_modal(struct memory_region*);

void show_arm_windows() {
    if(ctx.uc == NULL) {
        uc_open(UC_ARCH_ARM, UC_MODE_ARM, &ctx.uc);
    }
    show_arm_cpu_window();
    show_arm_memory_window();
}

void show_arm_cpu_window() {
    ImGui::Begin("ARM CPU State", &ui.cpu_window_open, ImGuiWindowFlags_AlwaysAutoResize);

    uint32_t value = 0;
    char edit_id[16] = "";
    static bool reg_edit = false;
    if (ImGui::BeginTable("Registers", 2)) {
        for(int i = 0; i < IM_ARRAYSIZE(arm_regs); i++) {
            uc_reg_read(ctx.uc, arm_regs[i], &value);
            sprintf(edit_id, "editreg%d", i);
            ImGui::TableNextColumn();
            ImGui::Text("%s", arm_reg_names[i]);
            ImGui::TableNextColumn();
            ImGui::Text("0x%08X", value);
            ImGui::OpenPopupOnItemClick(edit_id, ImGuiPopupFlags_MouseButtonRight);
            if (ImGui::BeginPopupContextItem(edit_id)) {
                static char edit_input[9] = "";
                if(!reg_edit) {
                    snprintf(edit_input, 9, "%X", value);
                    reg_edit = true;
                }
                ImGui::Text("Edit Value for %s:", arm_reg_names[i]);
                ImGui::InputText("", edit_input, 9, ImGuiInputTextFlags_CharsHexadecimal);
                if (ImGui::Button("OK")) {
                    uint64_t edit_value = 0;
                    edit_value = strtol(edit_input, NULL, 16);
                    uc_reg_write(ctx.uc, arm_regs[i], &edit_value);
                    ImGui::CloseCurrentPopup();
                    reg_edit = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel")) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        ImGui::EndTable();
    }

    if(ImGui::Button("Step")) {
        uint64_t pc;
        uc_reg_read(ctx.uc, UC_ARM_REG_PC, &pc);
        printf("Starting emulation from %08lX to %08lX\n", pc, pc+4);
        uc_err err = uc_emu_start(ctx.uc, pc, pc+8, 0, 1);
        if (err) {
            printf("Failed on uc_emu_start() with error returned: %u\n", err);
        }
    }

    ImGui::End();
}

void show_arm_memory_window() {
    static MemoryEditor mem_edit;
    
    ImGui::Begin("Memory Regions", &ui.memory_window_open);
    
    if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_TabListPopupButton)) {
        for(int i = 0; i < ctx.mapped_regions.size(); i++) {
            struct memory_region* region = ctx.mapped_regions.data() + i;
        // for(struct memory_region region : ctx.mapped_regions) {
            if (ImGui::BeginTabItem(region->name)) {
                ImGui::BeginGroup();
                ImGui::Text(region->name);
                ImGui::Text("Address: 0x%X", region->address);
                ImGui::SameLine();
                ImGui::Text("Size: 0x%X", region->size);
                if(region->perms & 1) {
                    ImGui::Text("Readable");
                    ImGui::SameLine();
                }
                if (region->perms & 2) {
                    ImGui::Text("Writable");
                    ImGui::SameLine();
                }
                if (region->perms & 4) {
                    ImGui::Text("Executable");
                    ImGui::SameLine();
                }
                ImGui::Text("");

                char edit_id[68]; char link_id[68]; char del_id[68];
                sprintf(edit_id, "Edit %s", region->name);
                sprintf(link_id, "Link %s", region->name);
                sprintf(del_id, "Delete %s?", region->name);

                if (ImGui::Button("Edit")) {
                    ImGui::OpenPopup(edit_id);
                }
                ImGui::SameLine();
                
                if (ImGui::Button("Link")) {
                    ImGui::OpenPopup(link_id);
                }
                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.0f, 0.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(1.0f, 0.3f, 0.3f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0.8f, 0.0f, 0.0f));
                if(ImGui::Button("Delete")) {
                    ImGui::OpenPopup(del_id);
                }
                ImGui::PopStyleColor(3);
                ImGui::EndGroup();

                if(region->links.size() > 0) {
                    ImGui::SameLine();
                    ImGui::Dummy(ImVec2(40,40));
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    ImGui::Text("Linked To:");
                    for (uint64_t addr : region->links) {
                        static char label[32];
                        snprintf(label, 32, "%lX", addr);
                        ImGui::Selectable(label);
                        if (ImGui::BeginPopupContextItem()) {
                            if (ImGui::Button("Separate")) {}
                            ImGui::SameLine();
                            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.0f, 0.0f));
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(1.0f, 0.3f, 0.3f));
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0.8f, 0.0f, 0.0f));
                            if (ImGui::Button("Delete")){
                                uc_err err = uc_mem_unmap(ctx.uc, addr, region->size);
                                if (err) {
                                    printf("Failed on uc_mem_unmap() with error returned: %u with %p, %08lX, %08lX\n", err, ctx.uc, region->address, region->size);
                                }
                                region->links.erase(std::remove(region->links.begin(), region->links.end(), addr), region->links.end());
                                ImGui::CloseCurrentPopup();
                            }
                            ImGui::PopStyleColor(3);
                            ImGui::EndPopup();
                        }
                    }
                    ImGui::EndGroup();
                }
                
                mem_edit.DrawContents(region->ptr, region->size, region->address);

                if (ImGui::BeginPopupModal(edit_id, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    static struct memory_region edit_copy;
                    if(!edit_copy.editing) memcpy(&edit_copy, region, sizeof(struct memory_region));

                    if(render_memory_map_modal(&edit_copy)) {
                        // 1. unmap the memory from unicorn
                        uc_err err = uc_mem_unmap(ctx.uc, region->address, region->size);
                        if (err) {
                            printf("Failed on uc_mem_unmap() with error returned: %u with %p, %08lX, %08lX\n", err, ctx.uc, region->address, region->size);
                        }
                        for(uint64_t addr : region->links) {
                            uc_err err = uc_mem_unmap(ctx.uc, addr, region->size);
                            if (err) {
                                printf("Failed on uc_mem_unmap() with error returned: %u with %p, %08lX, %08lX\n", err, ctx.uc, region->address, region->size);
                            }
                        }

                        // 2. reallocate the actual memory backing with the new size and copy contents
                        region->ptr = calloc(1, edit_copy.size);
                        memcpy(region->ptr, edit_copy.ptr, MIN(region->size, edit_copy.size));
                        free(edit_copy.ptr);

                        // 3. copy the edited attributes back into the canonical object
                        memcpy(region->name, edit_copy.name, 64);
                        region->address = edit_copy.address;
                        region->size = edit_copy.size;
                        region->perms = edit_copy.perms;

                        // 4. remap the memory into unicorn
                        err = uc_mem_map_ptr(ctx.uc, region->address, region->size, region->perms, region->ptr);
                        if (err) {
                            printf("Failed on uc_mem_map_ptr() with error returned: %u with %p, %08lX, %08lX, %08X, %p\n", err, ctx.uc, region->address, region->size, region->perms, region->ptr);
                        }
                        for(uint64_t addr : region->links) {
                            uc_err err = uc_mem_map_ptr(ctx.uc, addr, region->size, region->perms, region->ptr);
                            if (err) {
                                printf("Failed on uc_mem_map_ptr() with error returned: %u with %p, %08lX, %08lX, %08X, %p\n", err, ctx.uc, addr, region->size, region->perms, region->ptr);
                            }
                        }
                    }

                    ImGui::EndPopup();
                }
                if (ImGui::BeginPopupModal(link_id, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    static char addr_buf[32];
                    ImGui::Text("Linking a memory map allows it to be accessed from two base addresses.");
                    ImGui::InputText("Address (hex, x4KB)", addr_buf, 32, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
                    
                    bool valid = true;
                    const char* reason;
                    
                    long addr = strtol(addr_buf, NULL, 16);
                    if(addr % 4096 != 0) {
                        valid = false;
                        reason = "Must be 4KB aligned";
                    }

                    if(valid) {
                        if (ImGui::Button("Link", ImVec2(120, 0))) {
                            region->links.push_back(addr);
                            uc_err err = uc_mem_map_ptr(ctx.uc, addr, region->size, region->perms, region->ptr);
                            if (err) {
                                printf("Failed on uc_mem_map_ptr() with error returned: %u with %p, %08lX, %08lX, %08X, %p\n", err, ctx.uc, addr, region->size, region->perms, region->ptr);
                            }
                            ImGui::CloseCurrentPopup(); 
                        }
                    } else {
                        ImGui::Text(reason);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                    ImGui::EndPopup();
                }
                if (ImGui::BeginPopupModal(del_id, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    ImGui::Text("Are you sure you want to DELETE %s?", region->name);

                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.0f, 0.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(1.0f, 0.3f, 0.3f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0.8f, 0.0f, 0.0f));
                    if(ImGui::Button("Delete", ImVec2(120, 0))) {
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::PopStyleColor(3);

                    ImGui::SameLine();
                    if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                    ImGui::EndPopup();
                }
                ImGui::EndTabItem();

            }
        }
        
        if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip)) {
            ImGui::OpenPopup("Map New Region Of Memory");
        }

        // Always center this window when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("Map New Region Of Memory", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Define a new region of memory usable by the emulation.");
            ImGui::Separator();

            static struct memory_region new_memory_region;
            if(!new_memory_region.editing) memset(&new_memory_region, 0, sizeof(struct memory_region));
            if(render_memory_map_modal(&new_memory_region)) {
                new_memory_region.ptr = calloc(1, new_memory_region.size);
                ctx.mapped_regions.push_back(new_memory_region);
                uc_err err = uc_mem_map_ptr(ctx.uc, new_memory_region.address, new_memory_region.size, new_memory_region.perms, new_memory_region.ptr);
                if (err) {
                    printf("Failed on uc_mem_map_ptr() with error returned: %u with %p, %08lX, %08lX, %08X, %p\n", err, ctx.uc, new_memory_region.address, new_memory_region.size, new_memory_region.perms, new_memory_region.ptr);
                }
            }
            ImGui::EndPopup();
        }
        
        ImGui::EndTabBar();
    }
    ImGui::End();
    
}

// Returns true if the modal's 'ok' was clicked and `region` was modified
bool render_memory_map_modal(struct memory_region* region) {
    static char name_buf[64] = "";
    static char addr_buf[32] = "";
    static char size_buf[32] = "";
    static bool readable, writable, executable;

    if(!region->editing) {
        region->editing = true;
        if(region->name) {
            memcpy(name_buf, region->name, 64);
        } else {
            name_buf[0] = 0;
        }

        if(region->address > 0) {
            snprintf(addr_buf, 32, "%lX", region->address);
        } else {
            addr_buf[0] = 0;
        }

        if(region->size > 0) {
            snprintf(size_buf, 32, "%lX", region->size);
        } else {
            size_buf[0] = 0;
        }
        
        readable = region->perms & 1;
        writable = region->perms & 2;
        executable = region->perms & 4;
    }

    ImGui::InputText("Name", name_buf, 64);
    ImGui::InputText("Address (hex, x4KB)", addr_buf, 32, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
    ImGui::InputText("Size (hex, x4KB)", size_buf, 32, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);

    bool valid = true;
    const char* reason;

    ImGui::Checkbox("Readable", &readable); ImGui::SameLine();
    ImGui::Checkbox("Writable", &writable); ImGui::SameLine();
    ImGui::Checkbox("Executable", &executable);
    
    if(!(readable || writable || executable)) {
        valid = false;
        reason = "Must have some permission";
    }

    long addr = strtol(addr_buf, NULL, 16);
    long size = strtol(size_buf, NULL, 16);
    if(!((size > 0) && (addr % 4096 == 0) && (size % 4096 == 0))) {
        valid = false;
        reason = "Must be 4KB aligned";
    }

    if(strlen(name_buf) == 0) {
        valid = false;
        reason = "Must have a name";
    }

    if (valid) {
        if (ImGui::Button("OK", ImVec2(120, 0))) {
            region->name = (char*) malloc(64);
            memcpy(region->name, name_buf, 64);
            region->address = addr;
            region->size = size;
            region->perms = readable ? UC_PROT_READ : 0;
            region->perms |= writable ? UC_PROT_WRITE : 0;
            region->perms |= executable ? UC_PROT_EXEC: 0;
            region->editing = false;
            ImGui::CloseCurrentPopup();
            return true;
        }
    } else {
        ImGui::Text(reason);
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
    return false;
}