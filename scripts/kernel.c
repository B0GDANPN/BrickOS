void vga_clear_screen();
void vga_print_char(char symbol, short color, int x, int y);

void kernel_entry() {
  vga_clear_screen();
  vga_print_char('!', 0x0f, 0, 0);
  
  for (;;);
}

void vga_clear_screen(){
  int a = 0xb8000;
  while (a < 0xb8fa0){
    *((int*) a) = 0;
    a++;
  }   
}

void vga_print_char(char symbol, short color, int x, int y){
    int a = 0xb8000 + 2*(y*80 + x);
    int printed_char = (int)color << 8 + symbol;
    *((int*)a) = printed_char;
    
}