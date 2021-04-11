#pragma once

#include "common.h"

class Io {
    public:
        enum {
            BLACK = 0x0,
            BLUE = 0x1,
            GREEN = 0x2,
            CYAN = 0xb,
            RED = 0xc,
            MAGENTA = 0xd,
            BROWN = 0xe,
            LIGHT_GRAY = 0xf
        };

        u8 inb(u16 port);
        void outb(u16 port, u8 data);
        int get_cursor();
        void set_cursor(u32 offset);
        void enable_cursor(u8 start, u8 finish);
        void putc(u8 character);
        void clear_screen();
        void printk(char string[]);
    private:
        u32 vga_ctrl_reg  = 0x3d4;
        u32 vga_data_reg = 0x3d5;
        u32 vga_len = 4000;
        u32 vga_addr = 0xb8000;
 
};
