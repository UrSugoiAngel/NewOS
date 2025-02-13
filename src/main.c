#include <multiboot.h>
#include <stdint.h>
#include <screen.h>
#include <idt.h>
#include <gdt.h>
void kernel_main(multiboot_info_t *mboot_ptr, uint32_t initial_stack){
    // Clear the screen
    clear_screen();
    // Print a message
    kprint("Loading gdt...\n");
    // Load the GDT
    gdt_init();
    // Print a message
    kprint("Loading idt...\n");
    // Load the IDT
    idt_init();
    // Print a message
    kprint("kernel loaded\n"); 

    while(1){
        // Infinite loop
    }
    return;
}