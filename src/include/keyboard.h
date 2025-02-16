#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include <interrupt.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define KEYBOARD_BUFFER_SIZE 256

#define KEYBOARD_KEY_RELEASED 0x80

typedef enum {
    CAPS_LOCK = 0x3A,
    L_SHIFT = 0x2A,
    R_SHIFT = 0x36,
    L_CTRL = 0x1D,
    R_CTRL = 0x1D,
    L_ALT = 0x38,
    R_ALT = 0x38,
    L_SUPER = 0x5B,
    R_SUPER = 0x5C,
    L_ARROW = 0x4B,
    R_ARROW = 0x4D,
} KB_SpecialKey;

typedef struct {
    uint8_t buffer[KEYBOARD_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
} KeyboardBuffer;

void keyboard_init();
void keyboard_handler(registers_t *regs);

bool keyboard_has_key();

uint8_t keyboard_get_key();

#endif