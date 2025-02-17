#include <keyboard.h>
#include <portio.h>
#include <stdint.h>
#include <stdbool.h>
#include <interrupt.h>
#include <kbmap.h>
#include <screen.h>
#include <kstring.h>

bool shift = false;
bool caps = false;

kbbuffer_t kbbuffer;

bool keyboard_has_key(){
    return inb(KEYBOARD_STATUS_PORT) & 0x01;
}

uint8_t keyboard_get_key(){
    return inb(KEYBOARD_DATA_PORT);
}

void cmd_handler(char *cmd){
    if(strcmp(cmd, "clear") == 0){
        clear_screen();
    }else{
        kprint("Command not found: ");
        kprint(cmd);
        kprint("\n");
    }
}

void keyboard_handler(registers_t *regs){
    outb(0x20, 0x20);
    if(!keyboard_has_key()){
        return;
    }
    uint8_t scancode = keyboard_get_key();
    char key = keyboard_map[scancode];
    // kprintf("Key: %c\n", key);
    // asm volatile("xchg %bx, %bx");
    if(key >= 0){
        if(key == '\n'){
            kprint("\n");
            kbbuffer.buffer[kbbuffer.head] = 0;
            char cmd[KEYBOARD_BUFFER_SIZE];
            strcpy(cmd, kbbuffer.buffer);
            kbbuffer.head = 0;
            cmd_handler(cmd);
        }else if(key == '\b'){
            kprint_backspace();
            kbbuffer.head = (kbbuffer.head - 1) % KEYBOARD_BUFFER_SIZE;
            kbbuffer.buffer[kbbuffer.head] = 0;
        }else{
            switch(scancode){
                case CAPS_LOCK:
                    caps = !caps;
                    break;
                case LEFT_SHIFT_PRESS:
                case RIGHT_SHIFT_PRESS:
                    shift = true;
                    break;
                case LEFT_SHIFT_RELEASE:
                case RIGHT_SHIFT_RELEASE:
                    shift = false;
                    break;
                default:
                    if(shift ^ caps){
                        if(key >= 'a' && key <= 'z'){
                            key -= 32;
                        }
                    }
                    if(key != 0){
                        kbbuffer.buffer[kbbuffer.head] = key;
                        kbbuffer.head = (kbbuffer.head + 1) % KEYBOARD_BUFFER_SIZE;
                    }
                    char str[2] = {key, 0};
                    kprint(str);
                    break;
            }
            
        }
    }
}

void keyboard_init(){
    kbbuffer.head = 0;
    kbbuffer.tail = 0;
    memset(kbbuffer.buffer, 0, KEYBOARD_BUFFER_SIZE);
    register_interrupt_handler(IRQ1, &keyboard_handler);
}