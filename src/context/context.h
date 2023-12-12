#pragma once


// void default_handler(Context* ctx, unsigned short vector);
// void timer_handler(int error_code);
// void switch_handlers(Context* ctx);

//void default_handler(unsigned short vector);


// void default_handler(Context* ctx) {
//     print_format("Kernel panic: unhandled interrupt %x, interrupt process context:\n", vector);
//     print_format("  EAX = %x ECX = %x EDX = %x EBX = %x\n", ctx->eax, ctx->ecx, ctx->edx, ctx->ebx);
//     print_format("  ESP = %x EBP = %x ESI = %x EDI = %x\n", ctx->esp, ctx->ebp, ctx->esi, ctx->edi);
//     print_format("  DS = %x ES = %x FS = %x GS = %x\n", ctx->ds, ctx->es, ctx->fs, ctx->gs);
//     print_format("  CS = %x SS = TODO EIP = %x\n", ctx->cs, ctx->eip);
//     print_format("  EFLAG = %x\n", ctx->eflags);
//     print_format("  error code = %x\n", ctx->error_code);
    
// }

// void timer_handler(unsigned short error_code) {
//     print_format("Timer with error_code: %x", error_code);
// }

// void return_by_context(Context* ctx){
//     for (;;);
// }

