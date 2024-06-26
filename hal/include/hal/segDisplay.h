// segDisply.h
// module continuously reads number of hits from the accelerometer and updates the 14 seg display using thread 
// segDisplay uses i2c on zen cape red at address 0x20 

#ifndef _SEG_DISPLAY_H_
#define _SEG_DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <pthread.h>
#include <stdbool.h>

#define i2c_config1 "config-pin P9_18 i2c"
#define i2c_config2 "config-pin P9_17 i2c"

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS2 0x20

#define REG_DIRA 0x02
#define REG_DIRB 0x03
#define REG_OUTA 0x00
#define REG_OUTB 0x01

// green zencape registers
// #define REG_DIRA 0x00
// #define REG_DIRB 0x01
// #define REG_OUTA 0x14
// #define REG_OUTB 0x15

#define GPIO61_VAL "/sys/class/gpio/gpio61/value"
#define GPIO44_VAL "/sys/class/gpio/gpio44/value"
#define GPIO61_DIR "/sys/class/gpio/gpio61/direction"
#define GPIO44_DIR "/sys/class/gpio/gpio44/direction"
#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO61 "/sys/class/gpio/gpio61"
#define GPIO44 "/sys/class/gpio/gpio44"

// initializes threads
void segDisplay_init();

// cleans up thread
void segDisplay_cleanup();

// continuously reads number of hits from accelerometer and displays 
void* displayNum();

// i2c logic for zencape red
void initI2cBus_14Seg();
void writeI2cReg_14Seg(unsigned char regAddr, unsigned char value);

// similar to runCommand, used for exporting pins and writing to specific segDisplay files 
void segDisplay_write(char *filename, char* param);

// checks if pins are already exported 
bool checkIfExported(char *gpioPin);
#endif