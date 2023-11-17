[BIT 32]

[GLOBAL _pic_init]


; ICW1 init
_pic_init:

; mov esp, ebp

mov al, 0b00010001 
out 0x20, al ; master port COMMAND
out 0xA0, al ; slave port COMMAND

; ICW2 init
mov al, 0x20 ; start interrupt vector for master
out 0x21, al ; master port DATA

mov al, 0x28 ; start interrupt vector for slave
out 0xA1, al ; slave port DATA

; ICW3 init
mov al, 0b00000100 ; mask byte of slave for master
out 0x21, al

mov al, 2 ; port number of master for slave
out 0xA1, al

; ICW4 init
mov al, 0b00000001 ; TODO maybe wrong (if so, replace with 0b10000000)
out 0x21, al
out 0xA1, al
ret


[GLOBAL _send_eoi]

_send_eoi:

