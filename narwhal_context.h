#ifndef _NARWHAL_CONTEXT
#define _NARWHAL_CONTEXT

#include <vector>
#include <stdint.h>
#include <unicorn/unicorn.h>

struct memory_region {
    char* name;
    uint64_t address;
    std::vector<uint64_t> links;
    size_t size;
    uint32_t perms;
    void *ptr;
    bool editing;
};

struct narwhal_context {
    uint16_t version;
    uc_arch arch;
    uc_mode mode;
    uc_engine *uc;
    uc_err ucerr;

    std::vector<struct memory_region> mapped_regions;
};

struct narwhal_ui_context {
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

extern struct narwhal_context ctx;
extern struct narwhal_ui_context ui;

#endif