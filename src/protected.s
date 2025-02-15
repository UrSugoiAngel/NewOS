[GLOBAL enter_protected_mode]

enter_protected_mode:
    cli
    ; gdt address
    mov eax, [esp + 4]
    ; return address
    mov ebx, [esp + 8]
    lgdt [eax]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp 0x08:.ret
.ret:
    ret