#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

char* stringLowerCopy(const char* str);
void clear_stdin_buffer();
void clearScreen(); // Khai báo hàm xóa màn hình
void pauseScreen(const char* message); // Khai báo hàm dừng màn hình

#endif
