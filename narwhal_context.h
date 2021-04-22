#ifndef NARWHAL_CONTEXT
#define NARWHAL_CONTEXT

#include <stdint.h>
#include <unicorn/unicorn.h>

typedef struct {
    uint16_t version;
    uc_arch arch;
    uc_mode mode;
} NarwhalContext;

typedef struct {
    bool new_window_open;
    int arch_selection;
    int mode_selection;
    int endianess;

    bool open_window_open;
    bool save_window_open;
    bool cpu_window_open;
    bool memory_window_open;
    bool debug_window_open;
    bool demo_window_open;
} NarwhalUIContext;

const char* architecture_strings =  "ARM\0ARM64\0Mips\0x86\0Sparc\0M68K\0\0";
const char* arm_mode_strings =  "ARM Mode\0THUMB Mode\0ARM926\0ARM946\0ARM1176\0\0";
const char* arm64_mode_strings =  "ARM Mode\0THUMB Mode\0\0";
const char* mips_mode_strings = "Mips32 ISA\0Mips64 ISA\0\0";
const char* x86_mode_strings = "16-bit mode\00032-bit mode\00064-bit mode\0\0";
const char* sparc_mode_strings = "32-bit mode\00064-bit mode\0\0";
const char* blank_mode_strings = "No Modes For Selected Archetecture\0\0";

#endif