DetectCPUID:
pushfd
pop eax

mov ecx, eax

xor eax, 1 << 21

push eax
popfd

pushfd
pop eax

push eax
popfd

xor eax, ecx
jc NoCPUID
ret

DetectLongMode:
mov eax, 0x80000001
cpuid
test eax, 1 << 29
jc NoLongMode
ret

NoLongMode:
    mov [0xb8000], byte 'L'
    mov [0xb8001], byte 2
    mov [0xb8002], byte 'O'
    mov [0xb8003], byte 2
    mov [0xb8004], byte 'N'
    mov [0xb8005], byte 2
    mov [0xb8006], byte 'G'
    mov [0xb8007], byte 2

    hlt

NoCPUID:
hlt