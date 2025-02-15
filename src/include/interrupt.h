#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

typedef struct {
    uint32_t ds;                                     // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;                        // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically.
} registers_t;

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

extern void register_interrupt_handler(uint8_t n, void (*handler)(registers_t*));

#endif
