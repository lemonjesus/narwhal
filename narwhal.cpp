// NARWHAL MAIN CODE
// Called from main.cpp after the SDL and GL stuff are set up

#include "narwhal.h"
#include "narwhal_context.h"

#include <unicorn/unicorn.h>

static NarwhalContext ctx;
static NarwhalUIContext ui;

void narwhal_start(SDL_Window* window, ImGuiIO* pio) {
    ImGuiIO io = *pio;

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        build_main_menu();

        // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        if (ui.demo_window_open) ImGui::ShowDemoWindow(&show_demo_window);

        if (ui.debug_window_open) {
            ImGui::Begin("Narwhal Debug");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (ui.new_window_open) {
            ImGui::Begin("New Project", &ui.new_window_open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Select an architecture and mode to begin:");
            ImGui::Combo("Archetecture", &ui.arch_selection, architecture_strings);
            ImGui::Combo("Mode", &ui.mode_selection, mode_strings(ui.arch_selection));

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
}

void build_main_menu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New", "Ctrl+N", false, !ui.new_window_open)) {ui.new_window_open = true;}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {ui.open_window_open = true;}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As..")) {ui.save_window_open = true;}

            ImGui::Separator();

            if (ImGui::MenuItem("Quit", "Alt+F4")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            ImGui::Checkbox("Debug Window", &ui.debug_window_open);
            ImGui::Checkbox("Demo Window", &ui.demo_window_open);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

const char* mode_strings(int ui_arch_selection) {
    switch(ui_arch_selection) {
    case 0: return arm_mode_strings;
    case 1: return arm64_mode_strings;
    case 2: return mips_mode_strings;
    case 3: return x86_mode_strings;
    case 4: return sparc_mode_strings;
    default: return blank_mode_strings;
    }
}