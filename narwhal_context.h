#ifndef _NARWHAL_CONTEXT
#define _NARWHAL_CONTEXT

#include <unicorn/unicorn.h>

struct NarwhalContext {
    uint16_t version;
    uc_arch arch;
    uc_mode mode;
    uc_engine *uc;
    uc_err ucerr;
};

struct NarwhalUIContext {
    bool new_window_open;
    int arch_selection;
    int mode_selection;
    int endianess;

    bool open_window_open;
    bool save_window_open;
    bool cpu_window_open;
    bool config_window_open;
    bool memory_window_open;
    bool debug_window_open;
    bool demo_window_open;
};

extern struct NarwhalContext ctx;
extern struct NarwhalUIContext ui;

#endif