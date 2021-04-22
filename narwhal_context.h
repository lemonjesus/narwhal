#ifndef NARWHAL_CONTEXT
#define NARWHAL_CONTEXT

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

extern NarwhalContext ctx;
extern NarwhalUIContext ui;

#endif