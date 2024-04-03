#include "hal/accelerometer.h"
#include "../../app/include/helper.h"
static pthread_t xtid, ytid;
static int i2cFileDesc; 

void Accelerometer_init(){
    // configure pins
	runCommand(i2c_config1);
    runCommand(i2c_config2); 

    initI2cBus(); 
    // enable chip
    writeI2cReg(CTRL_REG1, 0x3F);
    sleepForMs(5); 
    
    // create one thread for each directon
    if(pthread_create(&xtid, NULL, &playAccelX, NULL ) < 0){
        perror("pthread_create() error in Sampler"); 
        exit(1); 
    }

    if(pthread_create(&ytid, NULL, &playAccelY, NULL ) < 0){
        perror("pthread_create() error in Sampler"); 
        exit(1); 
    } 

}
void Accelerometer_cleanup(){
    pthread_cancel(xtid); 
	pthread_join(xtid, NULL);
    pthread_cancel(ytid); 
    pthread_join(ytid, NULL);
}

void initI2cBus(){

	i2cFileDesc = open(I2CDRV_LINUX_BUS1, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C DRV: Unable to open bus for read/write (%s)\n", I2CDRV_LINUX_BUS1);
		perror("Error is:");
		exit(-1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, I2C_DEVICE_ADDRESS);
	if (result < 0) {
		perror("Unable to set I2C device to slave address.");
		exit(-1);
	}
}

void writeI2cReg(unsigned char regAddr, unsigned char value)
{
	unsigned char buff[2];
	buff[0] = regAddr;
	buff[1] = value;
	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("Unable to write i2c register");
		exit(-1);
	}
}

unsigned char readI2cReg(unsigned char regAddr)
{
	// To read a register, must first write the address
	int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
	if (res != sizeof(regAddr)) {
		perror("Unable to write i2c register.");
		exit(-1);
	}

	// Now read the value and return it
	char value = 0;
	res = read(i2cFileDesc, &value, sizeof(value));
	if (res != sizeof(value)) {
		perror("Unable to read i2c register");
		exit(-1);
	}
	return value;
}

void* playAccelX(){
    while(1){

    }
}

void* playAccelY(){
    while(1){
        
    }
}

float readX(){
    uint8_t buff[2]; 
    int REG_XMSB = 0; 
    int REG_XLSB = 1;
    buff[REG_XMSB] = (unsigned int)readI2cReg(OUT_X_H);
    buff[REG_XLSB] = (unsigned int)readI2cReg(OUT_X_L);
    int16_t floatx = ((buff[REG_XMSB] << 8) | buff[REG_XLSB]);
    return (float)floatx/100;

}

float readY(){
    int REG_YLSB = 1;
    uint8_t lsb = (unsigned int)readI2cReg(OUT_Y_L);
    uint8_t msb = (unsigned int)readI2cReg(OUT_Y_H);
    int16_t floatx = (msb << 8) | lsb; 
    return (float)floatx/100;
}