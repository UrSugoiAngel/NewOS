#include <kstring.h>
#include <stdint.h>

void memset(void *ptr, uint8_t value, uint32_t num){
    uint8_t *p = (uint8_t *)ptr;
    for(uint32_t i = 0; i < num; i++){
        p[i] = value;
    }
}

void memcpy(void *dest, void *src, uint32_t num){
    uint8_t *d = (uint8_t *)dest;
    uint8_t *s = (uint8_t *)src;
    for(uint32_t i = 0; i < num; i++){
        d[i] = s[i];
    }
}

int strcmp(char *str1, char *str2){
    while(*str1 && *str2 && *str1 == *str2){
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void strcpy(char *dest, char *src){
    while(*src){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = 0;
}