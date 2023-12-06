#include "../utils/utils.h"
#include "../print/print.h"
#include "../idt/idt.h"
#include "context.h"
#include "../pic/pic.h"


typedef struct {
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    
    u16 gs;
    u16 padding_1;

    u16 fs;
    u16 padding_2;
    
    u16 es;
    u16 padding_3;
    
    u16 ds;
    u16 padding_4;
    
    u32 vector;
    u32 error_code;

    u32 eip;
    u16 cs;
    u16 padding_5;
    u32 eflags;

    // u32 esp;

    // u16 ss;
    // u16 padding_6;

} Context;


void pop_context(Context* ctx);


void default_handler(Context* ctx, unsigned short vector) {
    print_format("Kernel panic: unhandled interrupt %x, interrupt process context:\n", vector);
    print_format("  EAX = %x ECX = %x EDX = %x EBX = %x\n", ctx->eax, ctx->ecx, ctx->edx, ctx->ebx);
    print_format("  ESP = %x EBP = %x ESI = %x EDI = %x\n", ctx->esp, ctx->ebp, ctx->esi, ctx->edi);
    print_format("  DS = %x ES = %x FS = %x GS = %x\n", ctx->ds, ctx->es, ctx->fs, ctx->gs);
    print_format("  CS = %x SS = TODO EIP = %x\n", ctx->cs, ctx->eip);
    print_format("  EFLAG = %x\n", ctx->eflags);
    print_format("  error code = %x\n", ctx->error_code);
    
}

void timer_handler(int error_code) {
    print_format("Timer with error_code: %x\n", error_code);
}


void switch_handlers(Context* ctx){
    // print_format("%x\n", ctx);
    u32 vector = ctx->vector;
    switch (vector)
    {
    case 0x20:
        timer_handler(ctx->error_code);
        send_eoi(0);

        break;
    
    default:
        default_handler(ctx, vector);
        send_eoi(0);
        break;
    }
    pop_context(ctx);
}