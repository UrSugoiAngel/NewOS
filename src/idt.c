#include <idt.h>
#include <stdint.h>
#include <interrupt.h>
#include <portio.h>

idt_entry_t idt[IDT_ENTRIES];

idt_ptr_t idtp;

extern void load_idt(uint32_t);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags){
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_load(){
    idtp.limit = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
    idtp.base = (uint32_t)&idt;

    load_idt((uint32_t)&idtp);
}

int idt_init(){

    // Remap the irq table.
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
    
    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    idt_set_gate(IRQ0, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(IRQ1, (uint32_t)irq1, 0x08, 0x8E);
    idt_set_gate(IRQ2, (uint32_t)irq2, 0x08, 0x8E);
    idt_set_gate(IRQ3, (uint32_t)irq3, 0x08, 0x8E);
    idt_set_gate(IRQ4, (uint32_t)irq4, 0x08, 0x8E);
    idt_set_gate(IRQ5, (uint32_t)irq5, 0x08, 0x8E);
    idt_set_gate(IRQ6, (uint32_t)irq6, 0x08, 0x8E);
    idt_set_gate(IRQ7, (uint32_t)irq7, 0x08, 0x8E);
    idt_set_gate(IRQ8, (uint32_t)irq8, 0x08, 0x8E);
    idt_set_gate(IRQ9, (uint32_t)irq9, 0x08, 0x8E);
    idt_set_gate(IRQ10, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(IRQ11, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(IRQ12, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(IRQ13, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(IRQ14, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(IRQ15, (uint32_t)irq15, 0x08, 0x8E);

    idt_load();
    return 1;
}