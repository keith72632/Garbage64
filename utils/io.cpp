#include "../includes/io.h"

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

void Io::putc(u8 character)
{
    u32 offset = get_cursor();
    u8 *vga = (u8*)vga_addr;
    vga[offset] = character;
    vga[offset + 1] = GREEN;
    offset += 2;
    set_cursor(offset);
}

void Io::clear_screen()
{
    int offset = 0;
    set_cursor(offset);
    int num = (80 * 25) * 2;
    
    for(int i = 0; i < num; i++, offset += 2)
    {
        putc(' ');
        set_cursor(offset);
    }
    set_cursor(0);
}

void Io::printk(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '\n')
        {
            //print_nl();
            break;
        }
        else
        {
            putc(str[i]);
            i++;
        }
    }
}