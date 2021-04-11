typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

#define VGA_ARRAY_LEN (80 * 25) * 2

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
        void putc(u8 character, u32 cursor_pos, u8 color);
        void clear_screen();
    private:
        u32 vga_ctrl_reg  = 0x3d4;
        u32 vga_data_reg = 0x3d5;
 
};

u8 Io::inb(u16 port)
{
    u8 result;
    asm volatile("inb %1, %0": "=a"(result) : "dN"(port));
    return result;
}

void Io::outb(u16 port, u8 data)
{
    asm volatile("outb %1, %0"::"dN"(port), "a"(data));
}

int Io::get_cursor()
{
    u32 offset;
    //request high bit
    outb(vga_ctrl_reg, 0x0e);
    offset = inb(vga_data_reg)<<8;
    //request low byte
    outb(vga_ctrl_reg, 0x0f);
    offset += inb(vga_data_reg);
    return offset * 2;
}

void Io::set_cursor(u32 offset)
{
    offset /= 2;
    //writing to high bit
    outb(vga_ctrl_reg, 0x0e);
    outb(vga_data_reg, (u8)(offset >> 8));
    //wrting to low bit
    outb(vga_ctrl_reg, 0x0f);
    outb(vga_data_reg, (u8)(offset & 0xff));
}

void Io::enable_cursor(u8 start, u8 finish)
{
	outb(vga_ctrl_reg, 0x0A);
	outb(vga_data_reg, (inb(0x3D5) & 0xC0) | start);
 
	outb(vga_ctrl_reg, 0x0B);
	outb(vga_data_reg, (inb(0x3D5) & 0xE0) | finish);
}

void Io::putc(u8 character, u32 cursor_pos, u8 color)
{
    u8 *vga = (u8*)0xb8000;
    vga[cursor_pos] = character;
    vga[cursor_pos + 1] = color;
    set_cursor(cursor_pos+2);
}

void Io::clear_screen()
{
    for(int i = 0; i < VGA_ARRAY_LEN; i++)
    {
        putc('\0', i, 0xf);
    }
    set_cursor(0);
}

extern "C" void _start()
{
    Io io;

    io.clear_screen();

    io.set_cursor(0);

    u32 postion = io.get_cursor();

    io.putc('K', postion, 0xf);
    postion += 2;
    io.putc('E', postion, 0xf);
    postion += 2;
    io.putc('I', postion, 0xf);
    postion += 2;
    io.putc('T', postion, 0xf);
    postion += 2;
    io.putc('H', postion, 0xf);

    io.set_cursor(postion);




    for(;;)
        asm volatile("hlt");
}
