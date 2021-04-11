
jmp EnterProtectedMode

%include "sector2/gdt.asm"


EnterProtectedMode:                        ;Enter protect: disable interruts, enable a20 line, load gdt
    call EnableA20
    cli
    lgdt [gdt_descripter]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp codeseg:start_prototected_mode     ;far jump to codeseg

EnableA20:
    in al, 0x02
    or al, 2
    out 0x02, al
    ret

[bits 32]

%include "sector2/cpu_id.asm"
%include "sector2/simple_paging.asm"

start_prototected_mode:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov [0xb8000], byte 'X'
    mov [0xb8001], byte 2

    call DetectCPUID

    mov [0xb8000], byte 'Y'
    mov [0xb8001], byte 2

    call DetectLongMode

    mov [0xb8000], byte 'Z'
    mov [0xb8001], byte 2

    call setup_indentity_paging
    call EditGdt

    jmp codeseg:start_64_bit

[bits 64]
[extern _kernel_start]
start_64_bit:
 
    call _kernel_start
    jmp $

times 2048-($-$$) db 0                                      ;padded with 2048 bytes 
