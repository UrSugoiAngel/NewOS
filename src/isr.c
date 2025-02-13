#include <isr.h>
#include <screen.h>

void isr_handler(registers_t regs){
    kprint("Received interrupt: ");
    kprint_dec(regs.int_no);
    kprint("\n");

    switch (regs.int_no) {
        case 0:
            kprint("Division by zero exception\n");
            break;
        case 13:
            kprint("General protection fault\n");
            break;
        case 14:
            kprint("Page fault\n");
            break;
        default:
            kprint("Unhandled exception\n");
            break;
    }
}