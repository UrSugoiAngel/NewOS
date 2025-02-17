#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void memset(void *ptr, uint8_t value, uint32_t num);
void memcpy(void *dest, void *src, uint32_t num);
int strcmp(char *str1, char *str2);
void strcpy(char *dest, char *src);

#endif