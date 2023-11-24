[BITS 32]

[GLOBAL _init_pic]
[GLOBAL _mask_irq]
[GLOBAL _mask_timer]

%define MASTER_PORT_COMMAND 0X20
%define SLAVE_PORT_COMMAND 0xA0
%define MASTER_PORT_DATA 0x21
%define SLAVE_PORT_DATA 0xA1

%define TRASH_PORT 0X80

; ICW1 init (define main flags and number of additional words)
_init_pic:

mov al, 0b00010001 
; (-, -, -, 1, level / edge trigerred mode bit, CALL Address interval bit, Single / Cascade mode bit, ICW4 needed bit)
out MASTER_PORT_COMMAND, al ; master port COMMAND
; out 0x80, al

out SLAVE_PORT_COMMAND, al ; slave port COMMAND
; out 0x80, al

; ICW2 init (define range of vectors, which irq translate to)
mov al, 0x20 
; start range of interrupt vectors for master
out MASTER_PORT_DATA, al ; master port DATA
; out 0x80, al

mov al, 0x28 
; start range of interrupt vectors for slave
out SLAVE_PORT_DATA, al ; slave port DATA
; out 0x80, al

; ICW3 init (cascade config)
mov al, 0b00000100
; mask bits of slave for master
out MASTER_PORT_DATA, al
; out 0x80, al

mov al, 2 
; port number of master for slave
out SLAVE_PORT_DATA, al
; out 0x80, al

; ICW4 init (sets additional flags)
mov al, 0b00000001

out MASTER_PORT_DATA, al
; out 0x80, al

out SLAVE_PORT_DATA, al
; out 0x80, al
ret

_mask_irq:
mov al, 0b11111011

out MASTER_PORT_DATA, al
; out 0x80, al

mov al, 0b11111111
out SLAVE_PORT_DATA, al
; out 0x80, al
ret

_mask_timer:
mov al, 0b00000001
out MASTER_PORT_DATA, al
; out 0x80, al
ret