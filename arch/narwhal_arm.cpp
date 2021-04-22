#include <unicorn/unicorn.h>

#include "narwhal_arm.h"
#include "../narwhal_context.h"
#include "../imgui/imgui.h"

void show_arm_cpu_window() {
    ImGui::Begin("ARM CPU State", &ui.cpu_window_open, ImGuiWindowFlags_AlwaysAutoResize);

    ctx.ucerr = uc_open(UC_ARCH_ARM, UC_MODE_ARM, &ctx.uc);
    if (ctx.ucerr) {
        ImGui::Text("Failed on uc_open() with error returned: %u (%s)\n", ctx.ucerr, uc_strerror(ctx.ucerr));
        ImGui::End();
        return;
    }

    uint32_t value;
    for(int i = 0; i < IM_ARRAYSIZE(arm_regs); i++) {
        uc_reg_read(ctx.uc, arm_regs[i], &value);
        ImGui::Text("%s: 0x%08X", arm_reg_names[i], value);
    }

    ImGui::End();
}