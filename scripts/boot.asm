[BITS 16]

cli ; stack settings
	xor ax, ax ; getting 0
	mov ss, ax ; ss = 0
	mov sp, 0x7C00 ; setting stack to right position

gdt_start:
    dq 0x0 ; null descriptor
gdt_code:
    dw 0xffff
    dw 0x0000
    dw 0x9200
    dw 0x00cf
gdt_data:
    dw 0xffff
    dw 0x0000
    dw 0x9a00
    dw 0x00cf
gdt_end:
lgdt [gdt_descriptor]
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start + 0x20000 ; linear address in copy vbr

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
mov cr0,ax
jmp CODE_SEG:protected_mode_tramplin + 0x7C00

[BITS 32]
protected_mode_tramplin:
  mov esp, 0x20000
  mov ds, DATA_SEG
  mov ss, ds
  mov es, ds
  mov ds, ds
  mov gs, ds
  mov fs, ds
  jmp CODE_SEG:0x20200
  ;mov dw[0xB8000], 0
sti



infinite_loop: ; infinite loop
  jmp infinite_loop

times 510-($-$$) db 0


dw 0xAA55
