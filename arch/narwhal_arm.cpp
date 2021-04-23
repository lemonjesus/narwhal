#include <vector>
#include <unicorn/unicorn.h>

#include "narwhal_arm.h"
#include "../narwhal_context.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_memory_editor.h"

#define ARM_CODE "\x37\x00\xa0\xe3\x03\x10\x42\xe0" // mov r0, #0x37; sub r1, r2, r3
#define ADDRESS 0x10000

void show_arm_config_window();
void show_arm_cpu_window();
void show_arm_memory_window();

void show_arm_windows() {
    show_arm_config_window();
    show_arm_cpu_window();
    show_arm_memory_window();
}

void show_arm_config_window() {
    ImGui::Begin("ARM Environment", &ui.config_window_open);
    ImGui::Button("Memory Map");
    ImGui::End();
}

void* mem = NULL;

void show_arm_cpu_window() {
    ImGui::Begin("ARM CPU State", &ui.cpu_window_open, ImGuiWindowFlags_AlwaysAutoResize);

    uint32_t value = 0;
    if (ImGui::BeginTable("Registers", 2)) {
        for(int i = 0; i < IM_ARRAYSIZE(arm_regs); i++) {
            if(ctx.uc != NULL) uc_reg_read(ctx.uc, arm_regs[i], &value);
            ImGui::TableNextColumn();
            ImGui::Text("%s", arm_reg_names[i]);
            ImGui::TableNextColumn();
            ImGui::Text("0x%08X", value);
        }
        ImGui::EndTable();
    }

    if(ImGui::Button("Step")) {
        
    }

    ImGui::End();
}

void show_arm_memory_window() {
    static MemoryEditor mem_edit;
    
    ImGui::Begin("Memory Regions", &ui.memory_window_open);
    
    if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_TabListPopupButton)) {
        for(struct memory_region region : ctx.mapped_regions) {
            if (ImGui::BeginTabItem(region.name)) {
                ImGui::Text(region.name);
                ImGui::Text("addr: 0x%X", region.address);
                ImGui::Text("size: 0x%X", region.size);
                ImGui::Text("perm: %d", region.perms);
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

            static char buf1[64] = ""; ImGui::InputText("Name", buf1, 64);
            static char buf2[64] = ""; ImGui::InputText("Starting Address", buf2, 64, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            static char buf3[64] = ""; ImGui::InputText("Size", buf3, 64, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);

            static bool readable, writable, executable;
            ImGui::Checkbox("Readable", &readable); ImGui::SameLine();
            ImGui::Checkbox("Writable", &writable); ImGui::SameLine();
            ImGui::Checkbox("Executable", &executable);

            if (ImGui::Button("OK", ImVec2(120, 0))) {
                struct memory_region new_memory_region;
                new_memory_region.name = (char*) malloc(64);
                memcpy(new_memory_region.name, buf1, 64);
                new_memory_region.address = strtol(buf2, NULL, 16);
                new_memory_region.size = strtol(buf3, NULL, 16);
                new_memory_region.perms = readable ? UC_PROT_READ : 0;
                new_memory_region.perms |= writable ? UC_PROT_WRITE : 0;
                new_memory_region.perms |= executable ? UC_PROT_EXEC: 0;
                new_memory_region.ptr = calloc(1, new_memory_region.size);
                ctx.mapped_regions.push_back(new_memory_region);
                ImGui::CloseCurrentPopup();
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