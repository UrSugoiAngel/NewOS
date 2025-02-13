#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stdarg.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4

extern void clear_screen();
extern void kprint_at(char *message, int col, int row);
extern void kprint(char *message);
extern void kprint_backspace();

extern void kprint_hex(uint32_t n);
extern void kprint_dec(uint32_t n);

extern void kprintf(char *format, ...);

#endif