[org 0x7c00]

mov [BOOT_DISK], dl                       ;store disk loaction for later use


call read_disk

jmp PROGRAM_SPACE 
    
%include "sector1/print.asm"
%include "sector1/disk_read.asm"
teststring:
    db 'fuck you', 0

times 510-($-$$) db 0
dw 0xaa55

;This initial boot is only 512 mb. Jump to bigger 'chunk' called Program space