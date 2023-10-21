void kernel_entry() {
  *((short int*) 0xB8000) = 0;
  
  // asm("movb $'X'  , %al\n");
  // asm("movb $0x0e, %ah\n");
  // asm("int $0x10\n");
  for (;;);
}