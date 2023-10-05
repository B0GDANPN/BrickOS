[BITS 16]

cli ; stack settings
	xor ax, ax ; getting 0
	mov ss, ax ; ss = 0
	mov sp, 0x7C00 ; setting stack to right position
sti

mov bx, 0x0 ; const shift
mov ax, 0x2000
mov es, ax ; mutable address
mov ah, 0x2 ; number command for interrupt
mov al, 0x1 ; count of sector for reading
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
    int 0x13 read in buffer
    mov ax, es ; es - address register, add number - prohibited
    add ax, 0x20
    mov es, ax
    mov ah, 0x2 ; return value AX
    mov al, 0x1 ; return value AX
    add cl, 0x1 ; next sector
    jmp reading_sector
end_sector: after reading second head
    add dh, 0x1 ; next head
	jmp reading_head
end_head:
	add ch, 0x1 ; next cylinder
	jmp reading_cylinder
end_cylinder:

mov ax, es ; end of range
mov dx, 0x2000 ; start of range
mov es, dx ; ES - address register, mov number - prohibited
mov ecx, 0 ; checksum=0
mov ch, 0 ; correct print checksum, we use only CL
count_checksum:
    cmp dx, ax
    je infinite_loop ; quit cycle
    inner_checksum: ; bl 0..15, for reading all bytes
        cmp bl, 0x10 ; bl<16
        je end_inner_checksum
        add cl, byte[es:bx]
        add bx, 0x1
        jmp inner_checksum
    end_inner_checksum:
    mov bx, 0 ; bl = 0
    add dx, 0x1 ; next address
    mov es, dx
    jmp count_checksum


infinite_loop: ; infinite loop
  jmp infinite_loop

times 510-($-$$) db 0


dw 0xAA55