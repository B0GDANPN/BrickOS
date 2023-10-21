[BITS 16]

cli ; stack settings
	xor ax, ax ; getting 0
	mov ss, ax ; ss = 0
	mov sp, 0x7C00 ; setting stack to right position
sti



infinite_loop: ; infinite loop
  jmp infinite_loop

times 510-($-$$) db 0


dw 0xAA55
