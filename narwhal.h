#ifndef NARWHAL
#define NARWHAL

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>            // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

void narwhal_start(SDL_Window* window, ImGuiIO* io);

// not used anywhere else
void build_main_menu();
void create_project();
const char* mode_strings();

const char* const architecture_strings = "ARM\0ARM64\0Mips\0x86\0Sparc\0M68K\0\0";
const char* const arm_mode_strings = "ARM Mode\0THUMB Mode\0ARM926\0ARM946\0ARM1176\0\0";
const char* const arm64_mode_strings = "ARM Mode\0THUMB Mode\0\0";
const char* const mips_mode_strings = "Mips32 ISA\0Mips64 ISA\0\0";
const char* const x86_mode_strings = "16-bit mode\00032-bit mode\00064-bit mode\0\0";
const char* const sparc_mode_strings = "32-bit mode\00064-bit mode\0\0";
const char* const blank_mode_strings = "No Modes For Selected Archetecture\0\0";
#endif