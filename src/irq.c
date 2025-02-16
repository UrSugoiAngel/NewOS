#include <irq.h>
#include <portio.h>
#include <screen.h>

void irq_handler(registers_t regs){
    asm volatile("cli");
    // kprint("IRQ: ");
    // kprint_hex(regs.int_no);
    // kprint("\n");
    if (interrupt_handlers[regs.int_no] != 0)
        interrupt_handlers[regs.int_no](&regs);
    // // eoi signal to PIC
    // if(regs.int_no < 40){
    //     outb(0x20, 0x20);
    // }
    // else {
    //     outb(0xA0, 0x20);
    //     outb(0x20, 0x20);
    // }
    asm volatile("sti");
}

void irq_unmask(uint8_t irq){
    uint16_t port;
    uint8_t value;
    if(irq < 8){
        port = 0x21;
    }
    else {
        port = 0xA1;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq & 0xFF);
    outb(port, value);
}

void register_interrupt_handler(uint8_t n, void (*handler)(registers_t*)){
    irq_unmask(n - IRQ_BASE);
    interrupt_handlers[n] = handler;
}