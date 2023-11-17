[BITS 32]

[GLOBAL _init_pic]
[GLOBAL _mask_irq]
[GLOBAL _mask_timer]

; ICW1 init
_init_pic:

; mov esp, ebp

mov al, 0b00010001 
out 0x20, al ; master port COMMAND
out 0x80, al

out 0xA0, al ; slave port COMMAND
out 0x80, al

; ICW2 init
mov al, 0x20 ; start interrupt vector for master
out 0x21, al ; master port DATA
out 0x80, al

mov al, 0x28 ; start interrupt vector for slave
out 0xA1, al ; slave port DATA
out 0x80, al

; ICW3 init
mov al, 0b00000100 ; mask byte of slave for master
out 0x21, al
out 0x80, al

mov al, 2 ; port number of master for slave
out 0xA1, al
out 0x80, al

; ICW4 init
mov al, 0b00000001
out 0x21, al
out 0x80, al

out 0xA1, al
out 0x80, al
ret

_mask_irq:
mov al, 0b11111011
out 0x21, al
out 0x80, al

mov al, 0b11111111
out 0xA1, al
out 0x80, al
ret

_mask_timer:
mov al, 0b00000001
out 0x21, al
out 0x80, al
ret