#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>
#include <SDL.h>

void check_error(int val, char* msg);
void check_null(void* val, char* msg);
void print_error(char* msg);

#endif
