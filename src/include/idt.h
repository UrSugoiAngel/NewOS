#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

#define IDT_INTERRUPT_GATE 0xE

#define IRQ_BASE 32
#define IRQ_COUNT 16
#define IRQ_SLAVE 2

#define IRQ0 IRQ_BASE
#define IRQ1 IRQ_BASE + 1
#define IRQ2 IRQ_BASE + 2
#define IRQ3 IRQ_BASE + 3
#define IRQ4 IRQ_BASE + 4
#define IRQ5 IRQ_BASE + 5
#define IRQ6 IRQ_BASE + 6
#define IRQ7 IRQ_BASE + 7
#define IRQ8 IRQ_BASE + 8
#define IRQ9 IRQ_BASE + 9
#define IRQ10 IRQ_BASE + 10
#define IRQ11 IRQ_BASE + 11
#define IRQ12 IRQ_BASE + 12
#define IRQ13 IRQ_BASE + 13
#define IRQ14 IRQ_BASE + 14
#define IRQ15 IRQ_BASE + 15

// Segment selectors
#define KERNEL_CS 0x08

typedef struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

extern void idt_load();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

extern int idt_init();

#endif