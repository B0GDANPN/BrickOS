[BITS 16]

cli ; stack settings
	xor ax, ax ; getting 0
	mov ss, ax ; ss = 0
	mov sp, 0x7C00 ; setting stack to right position

  mov bx, 0x0 ; const shift
mov ax, 0x2000
mov es, ax ; mutable address
mov ch, 0x0 ; number start cylinder

reading_cylinder:
    cmp ch, 0x14 ; max count cylinders
    je end_cylinder ; after read last cylinder
	mov dh, 0x0 ; start number head
reading_head:
    cmp dh, 0x2 ; head < 2
    je end_head ; after reading second head
    mov cl, 0x1 ; number of start sector
reading_sector:
    cmp cl, 0x13 ; sector <19
    je end_sector ; after reading second head
    mov ah, 0x2 ; number command for interrupt
    mov al, 0x1 ; count of sector for reading
    int 0x13 ; read in buffer
    jc error_handler
    mov ax, es ; es - address register, add number - prohibited
    add ax, 0x20 ; increase address
    mov es, ax ; es is address
    add cl, 0x1 ; next sector
    jmp reading_sector
end_sector: ; after reading second head
    add dh, 0x1 ; next head
	jmp reading_head
end_head:
	add ch, 0x1 ; next cylinder
	jmp reading_cylinder
end_cylinder:

mov ah, 0x01
mov ch, 0x3F
int 0x10; disable cursor

lgdt [gdt_descriptor + 0x7c00]

mov eax, cr0 
or al, 1
mov cr0, eax 
jmp CODE_SEG:protected_mode_tramplin + 0x7C00

[BITS 32]
protected_mode_tramplin:
  mov esp, 0x20000
  mov ax, DATA_SEG 
  mov ss, ax
  mov ds, ax
  mov es, ax
  mov gs, ax
  mov fs, ax
  jmp CODE_SEG:0x20200



infinite_loop: ; infinite loop
  jmp infinite_loop

error_handler:
  mov ax, 0xDEAD
  jmp infinite_loop


align 8
gdt_start:
    dw 0x0000 ; null descriptor
    dw 0x0000
    dw 0x0000
    dw 0x0000
gdt_code:
    dw 0xffff
    dw 0x0000
    dw 0x9a00
    dw 0x00cf
gdt_data:
    dw 0xffff
    dw 0x0000
    dw 0x9200
    dw 0x00cf
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start + 0x20000 ; linear address in copy vbr

times 510-($-$$) db 0


CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

dw 0xAA55