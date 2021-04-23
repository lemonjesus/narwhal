#include <unicorn/unicorn.h>

#include "narwhal_arm.h"
#include "../narwhal_context.h"
#include "../imgui/imgui.h"

#define ARM_CODE "\x37\x00\xa0\xe3\x03\x10\x42\xe0" // mov r0, #0x37; sub r1, r2, r3
#define ADDRESS 0x10000

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

    int r2 = 0x100;
    int r3 = 0x97;

    if(ImGui::Button("Step")) {
        if(ctx.uc == NULL) {
            uc_open(UC_ARCH_ARM, UC_MODE_ARM, &ctx.uc);
            uc_mem_map(ctx.uc, ADDRESS, 2 * 1024, UC_PROT_ALL);
            uc_mem_write(ctx.uc, ADDRESS, ARM_CODE, sizeof(ARM_CODE) - 1);
            uc_reg_write(ctx.uc, UC_ARM_REG_R2, &r2);
            uc_reg_write(ctx.uc, UC_ARM_REG_R3, &r3);
        }
        uc_emu_start(ctx.uc, ADDRESS, ADDRESS + sizeof(ARM_CODE) -1, 0, 2);
    }

    ImGui::End();
}