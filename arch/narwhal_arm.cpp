#include <unicorn/unicorn.h>
#include "narwhal_arm.h"
#include "../narwhal_context.h"
#include "../imgui/imgui.h"

void show_arm_cpu_window() {
    ImGui::Begin("Narwhal Debug");
    ImGui::Text("ARM CPU WINDOW! %d", ui.arch_selection);
    ImGui::End();
}