#include <keyboard.h>
#include <portio.h>
#include <stdint.h>
#include <stdbool.h>
#include <interrupt.h>
#include <kbmap.h>
#include <screen.h>

bool keyboard_has_key(){
    return inb(KEYBOARD_STATUS_PORT) & 0x01;
}

uint8_t keyboard_get_key(){
    return inb(KEYBOARD_DATA_PORT);
}

void keyboard_handler(registers_t *regs){
    outb(0x20, 0x20);
    uint8_t status = inb(KEYBOARD_STATUS_PORT);
    if(!(status & 0x01)){
        return;
    }
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    char key = keyboard_map[scancode];
    // kprintf("Key: %c\n", key);
    // asm volatile("xchg %bx, %bx");
    if(key >= 0){
        char str[2] = {key, 0};
        kprint(str);
    }
}

void keyboard_init(){
    register_interrupt_handler(IRQ1, &keyboard_handler);
}