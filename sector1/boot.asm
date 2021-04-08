[org 0x7c00]

mov [BOOT_DISK], dl                       ;store disk loaction for later use

mov bp, 0x7c00
mov sp, bp

call read_disk

jmp PROGRAM_SPACE 
    
%include "sector1/print.asm"
%include "sector1/disk_read.asm"
teststring:
    db 'fuck you', 0

times 510-($-$$) db 0
dw 0xaa55

