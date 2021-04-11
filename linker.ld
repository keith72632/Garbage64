OUTPUT_FORMAT(binary)

ENTRY(_kernel_start)

/*
INPUT
(
    extended_boot.o
    kernel.o
    io.o
)
*/

OUTPUT
(
    kernel.bin
)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(0x1000)
    {
        *(.text)
    }

    /*This is for things in C code like global variables*/
    .data : ALIGN(0x1000)
    {
        *(.data)
    }

    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }

    /*Block Started by Symbol. Unititalized data*/
    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }
}
