#include <screen.h>
#include <stdint.h>
#include <portio.h>
#include <stdarg.h> 

uint16_t *video_memory = (uint16_t *)0xb8000;
int cursor_x = 0;
int cursor_y = 0;

uint16_t loc;

void move_cursor(int y, int x){
    uint16_t cursorLocation = y * 80 + x;
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_CTRL, cursorLocation >> 8);
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_CTRL, cursorLocation);
    loc = cursorLocation;
    cursor_x = x;
    cursor_y = y;
}

void clear_screen(){
    for(int i = 0; i < MAX_COLS * MAX_ROWS; i++){
        video_memory[i] = (WHITE_ON_BLACK << 8) | ' ';
    }
    move_cursor(0, 0);
}

void kprint_at(char *message, int col, int row){
    if(col >= 0 && row >= 0){
        move_cursor(row, col);
    }
    int i = 0;
    while(message[i] != 0){
        if(cursor_x >= MAX_COLS){
            cursor_x = 0;
            cursor_y++;
        }
        if(cursor_y >= MAX_ROWS){
            clear_screen();
            cursor_x = 0;
            cursor_y = 0;
        }
        if(message[i] == '\n'){
            cursor_x = 0;
            cursor_y++;
        }else{
            video_memory[loc] = (WHITE_ON_BLACK << 8) | message[i];
            loc++;
            cursor_x++;
        }
        i++;
    }
}

void kput(char c){
    video_memory[loc] = (WHITE_ON_BLACK << 8) | c;
    move_cursor(cursor_y, cursor_x + 1);
}

void kprint(char *message){
    kprint_at(message, cursor_x, cursor_y);
    move_cursor(cursor_y, cursor_x);
}

void kprint_backspace(){
    if(cursor_x == 0 && cursor_y == 0){
        return;
    }
    if(cursor_x == 0){
        cursor_x = MAX_COLS - 1;
        cursor_y--;
    }else{
        cursor_x--;
    }
    video_memory[loc] = (WHITE_ON_BLACK << 8) | ' ';
    loc--;
    move_cursor(cursor_y, cursor_x);
}

void kprint_hex(uint32_t n){
    char hex[8];
    int i = 0;
    while(n > 0){
        int rem = n % 16;
        if(rem < 10){
            hex[i] = rem + 48;
        }else{
            hex[i] = rem + 55;
        }
        n = n / 16;
        i++;
    }
    hex[i] = 0;
    char hex2[8];
    int j = 0;
    for(int k = i - 1; k >= 0; k--){
        hex2[j] = hex[k];
        j++;
    }
    hex2[j] = 0;
    kprint(hex2);
}

void kprint_dec(uint32_t n){
    char dec[8];
    int i = 0;
    while(n > 0){
        int rem = n % 10;
        dec[i] = rem + 48;
        n = n / 10;
        i++;
    }
    dec[i] = 0;
    char dec2[8];
    int j = 0;
    for(int k = i - 1; k >= 0; k--){
        dec2[j] = dec[k];
        j++;
    }
    dec2[j] = 0;
    kprint(dec2);
}

void kprintf(char *format, ...){
    char *traverse;
    unsigned int i;
    char *s;
    va_list arg;
    va_start(arg, format);
    for(traverse = format; *traverse != 0; traverse++){
        while(*traverse != '%'){
            if(*traverse == 0){
                break;
            }
            kprint(traverse);
            traverse++;
        }
        if(*traverse == 0){
            break;
        }
        traverse++;
        switch(*traverse){
            case 'c': i = va_arg(arg, int);
                      kprint_at(&i, cursor_x, cursor_y);
                      break;
            case 'd': i = va_arg(arg, int);
                      if(i < 0){
                          i = -i;
                          kprint_at("-", cursor_x, cursor_y);
                      }
                      kprint_dec(i);
                      break;
            case 'x': i = va_arg(arg, unsigned int);
                      kprint_hex(i);
                      break;
            case 's': s = va_arg(arg, char *);
                      kprint_at(s, cursor_x, cursor_y);
                      break;
        }
    }
    va_end(arg);
}


