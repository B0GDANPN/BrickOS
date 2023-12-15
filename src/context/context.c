#include "../utils/utils.h"
#include "../print/print.h"
#include "../idt/idt.h"
#include "../utils/utils.h"
#include "context.h"
#include "../pic/pic.h"
#include "../console/console.h"
#include "../alloc/alloc.h"



Context* process_context_pointers[2];
Console* consoles;
int iter = -1;

void process_print_char(u32 symbol){
    asm ("mov %0, %%eax" : : "r"(symbol));
    asm("int $0x64");
}


void process_1(){
    asm("sti");
    while(1){
        process_print_char(iter + 48);
    }
}

void process_2(){
    asm("sti");
    while(1){
        process_print_char('H');
        process_print_char('E');
        process_print_char('L');
        process_print_char('L');
        process_print_char('O');
    }
}

void process_3(){
    asm("sti");
    while(1){
        process_print_char('*');
        process_print_char('-');
    }
}


void process_4(){
    asm("sti");
    while(1){
        process_print_char('W');
        process_print_char('O');
        process_print_char('R');
        process_print_char('L');
        process_print_char('D');
    }
}

void init_consoles(){
    consoles = kernel_malloc(sizeof(Console) * 4);

    init_console(consoles, 40, 12, 0, 0);
    init_console(consoles + 1, 40, 12, 40, 0);
    // init_console(consoles + 2, 40, 12, 0, 12);
    // init_console(consoles + 3, 40, 12, 40, 12);
}



Context* create_process(u32 process){
    u32 esp_ptr = (u32)kernel_malloc(sizeof(BLOCK_SIZE)) + BLOCK_SIZE;
    Context* ctx_ptr = (Context*)(esp_ptr - (sizeof(Context)));
    ctx_ptr->esp = 0;
    ctx_ptr->eax = 0;
    ctx_ptr->ebx = 0;
    ctx_ptr->ecx = 0;
    ctx_ptr->edx = 0;
    ctx_ptr->esi = 0;
    ctx_ptr->edi = 0;
    ctx_ptr->ebp = 0;
    ctx_ptr->vector = 0;
    ctx_ptr->error_code = 0;
    ctx_ptr->eip = process;
    ctx_ptr->cs = 0x8;
    ctx_ptr->eflags = 0;
    ctx_ptr->es = 0x10;
    ctx_ptr->ds = 0x10;
    ctx_ptr->fs = 0x10;
    ctx_ptr->gs = 0x10;

    return ctx_ptr;
}

void init_contexts(){
    process_context_pointers[0] = create_process((u32)process_1);
    process_context_pointers[1] = create_process((u32)process_2);
    // process_context_pointers[2] = create_process((u32)process_3);
    // process_context_pointers[3] = create_process((u32)process_4);
}

void default_handler(Context* ctx, unsigned short vector) {
    vga_clear_screen();
    print_format("Kernel panic: unhandled interrupt %x, interrupt process context:\n", vector);
    print_format("  EAX = %x ECX = %x EDX = %x EBX = %x\n", ctx->eax, ctx->ecx, ctx->edx, ctx->ebx);
    print_format("  ESP = %x EBP = %x ESI = %x EDI = %x\n", ctx->esp, ctx->ebp, ctx->esi, ctx->edi);
    print_format("  DS = %x ES = %x FS = %x GS = %x\n", ctx->ds, ctx->es, ctx->fs, ctx->gs);
    print_format("  CS = %x SS = TODO EIP = %x\n", ctx->cs, ctx->eip);
    print_format("  EFLAG = %x\n", ctx->eflags);
    print_format("  error code = %x\n", ctx->error_code);
    kernel_panic("END OF KERNEL PANIC!");
}

void copy_context(Context* dst, Context* src){
    dst->edi = src->edi;
    dst->esi = src->esi;
    dst->ebp = src->ebp;
    dst->esp = src->esp;
    dst->ebx = src->ebx;
    dst->edx = src->edx;
    dst->ecx = src->ecx;
    dst->eax = src->eax;

    dst->gs = src->gs;
    dst->fs = src->fs;
    dst->es = src->es;
    dst->ds = src->ds;

    dst->vector = src->vector;
    dst->error_code = src->error_code;
    
    dst->eip = src->eip;
    dst->cs = src->cs;
    dst->eflags = src->eflags;
}



void timer_handler(Context* context) {
    if (iter == -1){
        iter = 0;
        copy_context(context, process_context_pointers[iter]);
        // default_handler(context, 0);
        return;
    }
    // default_handler(context, 0);

    copy_context(process_context_pointers[iter], context);
    iter = (iter + 1) % 2;
    copy_context(context, process_context_pointers[iter]);
    // default_handler(context, 0);
}

void print_char_handler(Context* context){
    console_print_char(consoles + iter, context->eax);
    console_display(consoles + iter);
    // if (iter == 3){
    //     default_handler(context, 0);
    // }
}

void switch_handlers(Context* ctx){
    u32 vector = ctx->vector;
    switch (vector)
    {
    case 0x20:
        timer_handler(ctx);
        send_eoi(0);
        break; 
    case 100:
        print_char_handler(ctx);
        break;

    default:
        default_handler(ctx, vector);
        break;
    }
    
    // load_context(ctx);
    return;
}