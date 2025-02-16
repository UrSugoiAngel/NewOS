#include <memset.h>
#include <stdint.h>

void memset(void *ptr, uint8_t value, uint32_t num){
    uint8_t *p = (uint8_t *)ptr;
    for(uint32_t i = 0; i < num; i++){
        p[i] = value;
    }
}