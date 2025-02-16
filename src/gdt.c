#include <gdt.h>
#include <stdint.h>

gdt_entry_t gdt[GDT_ENTRIES];

gdt_ptr_t gdtp;

extern void enter_protected_mode(uint32_t);

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;
}

void gdt_load(){
    gdtp.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
    gdtp.base = (uint32_t)&gdt;

    //get the address the function will return to
    uint32_t ret_addr;
    asm volatile("call 1f\n1: pop %0" : "=r"(ret_addr));

    enter_protected_mode((uint32_t)&gdtp);
}

int gdt_init(){
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);  // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);  // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);  // User mode data segment

    gdt_load();
    return 0;
}