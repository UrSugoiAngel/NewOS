#include <multiboot.h>
#include <stdint.h>
#include <screen.h>
#include <idt.h>
#include <gdt.h>
void kernel_main(multiboot_info_t *mboot_ptr, uint32_t initial_stack){
    clear_screen();

    kprint("Loading gdt...\n");
    gdt_init();

    kprint("Loading idt...\n");
    idt_init();

    kprint("Loading keyboard...\n");
    keyboard_init();

    kprint("kernel loaded\n");


    while(1){
        // Infinite loop
    }
    return;
}