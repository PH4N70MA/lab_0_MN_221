#ifndef OWN_STDIO_H
#define OWN_STDIO_H

#include <Arduino.h>
#include <stdio.h>
#include "../include/config.h"

void own_stdio_setup(void);
int own_getchar(FILE *stream);
int own_putchar(char ch, FILE *stream);

#endif // OWN_STDIO_H