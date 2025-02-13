#include <irq.h>
#include <portio.h>

void irq_handler(registers_t regs){
     
    interrupt_handlers[regs.int_no](regs);
    // eoi signal to PIC
    if(regs.int_no < 40){
        outb(0x20, 0x20);
    }
}