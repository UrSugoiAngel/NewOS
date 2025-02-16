#include <multiboot.h>
#include <stdint.h>
#include <screen.h>
#include <idt.h>
#include <gdt.h>
#include <keyboard.h>

void kernel_main(multiboot_info_t *mboot_ptr, uint32_t initial_stack){
    clear_screen();

    kprint("Loading gdt...\n");
    gdt_init();

    kprint("Loading idt...\n");
    idt_init();

    kprint("Loading keyboard...\n");
    keyboard_init();

    kprint("kernel loaded\n");

    asm volatile("sti");
    volatile unsigned int i = 0;

    while(1){
        // Infinite loop
        i++;
    }
    i--;
    return;
}