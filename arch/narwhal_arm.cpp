#include <vector>
#include <stdio.h>
#include <unicorn/unicorn.h>

#include "narwhal_arm.h"
#include "../narwhal_context.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_memory_editor.h"

#define ARM_CODE "\x37\x00\xa0\xe3\x03\x10\x42\xe0" // mov r0, #0x37; sub r1, r2, r3
#define ADDRESS 0x10000

void show_arm_cpu_window();
void show_arm_memory_window();

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
                ImGui::Text("Edit Value for %s:", arm_reg_names[i]);
                ImGui::InputText("", edit_input, 9, ImGuiInputTextFlags_CharsHexadecimal);
                if (ImGui::Button("OK")) {
                    uint64_t edit_value = 0;
                    edit_value = strtol(edit_input, NULL, 16);
                    uc_reg_write(ctx.uc, arm_regs[i], &edit_value);
                    ImGui::CloseCurrentPopup();
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
    static char name_buf[64] = "";
    static char addr_buf[32] = ""; 
    static char size_buf[32] = ""; 
    
    ImGui::Begin("Memory Regions", &ui.memory_window_open);
    
    if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_TabListPopupButton)) {
        for(uint64_t i = 0; i < ctx.mapped_regions.size(); i++) {
            struct memory_region region = ctx.mapped_regions.at(i); 
            if (ImGui::BeginTabItem(region.name)) {
                ImGui::Text(region.name);
                ImGui::Text("Address: 0x%X", region.address);
                ImGui::SameLine();
                ImGui::Text("Size: 0x%X", region.size);
                if(region.perms & 1) {
                    ImGui::Text("Readable");
                    ImGui::SameLine();
                }
                if (region.perms & 2) {
                    ImGui::Text("Writable");
                    ImGui::SameLine();
                }
                if (region.perms & 4) {
                    ImGui::Text("Executable");
                    ImGui::SameLine();
                }
                ImGui::Text("");

                if (ImGui::Button("Edit")) {
                    printf("EDIT %s\n", region.name);
                }
                ImGui::SameLine();
                
                if (ImGui::Button("Clone")) {
                    printf("CLONE %s\n", region.name);
                }
                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.0f, 0.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(1.0f, 0.3f, 0.3f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0.8f, 0.0f, 0.0f));
                if(ImGui::Button("Delete")) {
                    printf("DELETE %s\n", region.name);
                }
                ImGui::PopStyleColor(3);
                
                mem_edit.DrawContents(region.ptr, region.size, region.address);
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

            ImGui::InputText("Name", name_buf, 64);
            ImGui::InputText("Address (hex, x4KB)", addr_buf, 32, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            ImGui::InputText("Size (hex, x4KB)", size_buf, 32, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);

            long addr = strtol(addr_buf, NULL, 16);
            long size = strtol(size_buf, NULL, 16);
            bool valid = (addr > 0) && (size > 0) && (addr % 4096 == 0) && (size % 4096 == 0);

            static bool readable, writable, executable;
            ImGui::Checkbox("Readable", &readable); ImGui::SameLine();
            ImGui::Checkbox("Writable", &writable); ImGui::SameLine();
            ImGui::Checkbox("Executable", &executable);
            if (valid) {
                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    struct memory_region new_memory_region;
                    new_memory_region.name = (char*) malloc(64);
                    memcpy(new_memory_region.name, name_buf, 64);
                    new_memory_region.address = addr;
                    new_memory_region.size = size;
                    new_memory_region.perms = readable ? UC_PROT_READ : 0;
                    new_memory_region.perms |= writable ? UC_PROT_WRITE : 0;
                    new_memory_region.perms |= executable ? UC_PROT_EXEC: 0;
                    new_memory_region.ptr = calloc(1, new_memory_region.size);
                    ctx.mapped_regions.push_back(new_memory_region);
                    uc_err err = uc_mem_map_ptr(ctx.uc, new_memory_region.address, new_memory_region.size, new_memory_region.perms, new_memory_region.ptr);
                    if (err) {
                        printf("Failed on uc_mem_map_ptr() with error returned: %u with %p, %08lX, %08lX, %08X, %p\n", err, ctx.uc, new_memory_region.address, new_memory_region.size, new_memory_region.perms, new_memory_region.ptr);
                    }
                    ImGui::CloseCurrentPopup();
                }
            } else {
                ImGui::Text("Must be 4KB aligned");
            }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
        }
        
        ImGui::EndTabBar();
    }
    ImGui::End();
    
}