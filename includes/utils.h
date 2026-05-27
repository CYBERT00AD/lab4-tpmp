#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void read_line(const char *prompt, char *buffer, size_t size);
int read_int(const char *prompt);
double read_double(const char *prompt);
void pause_screen(void);

#endif