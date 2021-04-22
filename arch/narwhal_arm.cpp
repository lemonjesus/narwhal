#include <unicorn/unicorn.h>

#include "narwhal_arm.h"
#include "../narwhal_context.h"
#include "../imgui/imgui.h"

void show_arm_cpu_window() {
    ImGui::Begin("ARM CPU State");

    ctx.ucerr = uc_open(UC_ARCH_ARM, UC_MODE_ARM, &ctx.uc);
    if (ctx.ucerr) {
        ImGui::Text("Failed on uc_open() with error returned: %u (%s)\n", ctx.ucerr, uc_strerror(ctx.ucerr));
        ImGui::End();
        return;
    }
    ImGui::End();
}