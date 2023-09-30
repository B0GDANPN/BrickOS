[BITS 16]

cli ; stack settings
  xor ax, ax ; getting 0 
  mov ss, ax ; ss = 0
  mov sp, 0x7C00 ; setting stack to right position
sti

%macro write_char 1
  mov al, %1  ; ascii code of H
  int 0x10 ; interrupt to the command of displaying  
%endmacro

mov ah, 0xE ; display char command

write_char 72 ; "H"
write_char 101 ; "e"
write_char 108 ; "l"
write_char 108 ; "l"
write_char 111 ; "o"
write_char 32 ; " " 
write_char 119 ; "w"
write_char 111 ; "o"
write_char 114 ; "r"
write_char 108 ; "l"
write_char 100 ; "d"
write_char 33 ; "!"

loop: ; infinite loop
  jmp loop

times 510-($-$$) db 0

dw 0xAA55
