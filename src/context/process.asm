[BITS 32]

[GLOBAL _process_method]
[GLOBAL _load_context]
[GLOBAL _process_print_char]


; _process_print_char:
;     add esp, 4
;     pop eax
;     int 100
;     sub esp, 4
;     ret

_process_method:
    sti
    mov eax, 0x40
loop:
    add eax, 1
    int 100
    jmp loop
    ret


_load_context:
    pop eax
    
	pop esp

    ; pop eax
    ; pop eax
    ; pop eax
    ; pop esp

    popa

	pop gs
	pop fs
	pop es
	pop ds

	add esp, 8
    iretd
