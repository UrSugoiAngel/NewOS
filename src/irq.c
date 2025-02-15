#include <irq.h>
#include <portio.h>

void irq_handler(registers_t regs){
     
    interrupt_handlers[regs.int_no](regs);
    // eoi signal to PIC
    if(regs.int_no < IRQ_BASE + IRQ_COUNT){
        outb(0x20, 0x20);
    }
}

void irq_unmask(uint8_t irq){
    uint16_t port;
    uint8_t value;
    if(irq < 8){
        port = 0x21;
    } else {
        port = 0xA1;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
}

void register_interrupt_handler(uint8_t n, void (*handler)(registers_t*)){
    irq_unmask(n - IRQ_BASE);
    interrupt_handlers[n] = handler;
}