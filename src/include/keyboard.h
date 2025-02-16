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
    ESCAPE = 0x01,
    LEFT_CONTROL = 0x1D,
    LEFT_SHIFT_PRESS = 0x2A,
    RIGHT_SHIFT_PRESS = 0x36,
    LEFT_SHIFT_RELEASE = 0xAA,
    RIGHT_SHIFT_RELEASE = 0xB6,
    ALT = 0x38,
    CAPS_LOCK = 0x3A,
    F1 = 0x3B,
    F2 = 0x3C,
    F3 = 0x3D,
    F4 = 0x3E,
    F5 = 0x3F,
    F6 = 0x40,
    F7 = 0x41,
    F8 = 0x42,
    F9 = 0x43,
    F10 = 0x44
} KB_SpecialKey;

typedef struct {
    uint8_t buffer[KEYBOARD_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
} kbbuffer_t;

void keyboard_init();
void keyboard_handler(registers_t *regs);

bool keyboard_has_key();

uint8_t keyboard_get_key();

#endif