// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include "hal/neopixel.h"

int main()
{
    printf("Hello world!\n");
    Neopixel_init();
} 