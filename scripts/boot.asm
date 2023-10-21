[BITS 16]

cli ; stack settings
	xor ax, ax ; getting 0
	mov ss, ax ; ss = 0
	mov sp, 0x7C00 ; setting stack to right position

gdt_start:
    dq 0x0 ; null descriptor
gdt_code:
    db ...
gdt_data:
    db ...
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start + 0x20000 ; linear address in copy vbr

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

lgdt [gdt_descriptor]

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start + 0x20000


sti



infinite_loop: ; infinite loop
  jmp infinite_loop

times 510-($-$$) db 0


dw 0xAA55
