#ifndef IRQ_H
#define IRQ_H

#include <interrupt.h>

void (*interrupt_handlers[256])(registers_t *);

void irq_handler(registers_t regs);

#endif