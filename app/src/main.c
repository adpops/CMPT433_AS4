// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h> 
#include "helper.h"
#include "hal/neopixel.h"
#include "hal/accelerometer.h"
#include "hal/segDisplay.h"
#include "hal/joystick.h"

static pthread_mutex_t xLock = PTHREAD_MUTEX_INITIALIZER; 
static pthread_mutex_t yLock = PTHREAD_MUTEX_INITIALIZER; 
static enum xDirections xState; 
static enum yDirections yState; 

int main()
{
    printf("Hello world!\n");

    Locks locks = {&xLock, &yLock, &xState, &yState}; 
    Accelerometer_init(&locks); 
    Neopixel_init(&locks);
    segDisplay_init(); 
    Joystick_init(); //JOYSTICK SHOULD BE LAST THING TO INIT. I do a pthread_join() in Joystick_init()

    segDisplay_cleanup();
    Neopixel_cleanup();
    Accelerometer_cleanup(); 
    //don't call Joystick_cleanup()
} 