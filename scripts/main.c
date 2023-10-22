typedef void *va_list;
extern void va_end(va_list);
#define va_start(list, name) (void) (list = (void *)((char *)&...))
#define va_arg(list, mode) ((mode *)(list = (char *)list + sizeof(mode)))[-1]
#define va_end(list) (void)0
int main(){

}