PROGRAM_SPACE equ 0x8000                         ;a macro that essentially points to the end of program. 512 byte after 0x7c00

read_disk:
    mov ah, 0x02                                 ;bios function for reading disk
    mov bx, PROGRAM_SPACE
    mov al, 32                                    ;number of sectors to read. Increase as prgram grows
    mov dl, [BOOT_DISK]                          ;location
    mov ch, 0x00                                 ;cylinder 0
    mov dh, 0x00                                 ;head 0
    mov cl, 0x02                                 ;read from 2nd sector. where prgram starts

    int 0x13

    jc DISK_READ_ERROR                           ;if disk read error, carry flag is set

    ret
BOOT_DISK:
    db 0 

DISK_READ_SUCCESS_MSG:
    db 'Disk read success', 0

DISK_READ_ERROR_MSG:
    db 'Disk read fail', 0

DISK_READ_ERROR:

    jmp $
    