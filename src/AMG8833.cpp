#include "AMG8833.h"


AMG8833::AMG8833(){


}

void AMG8833::inititialize(uint8_t mode=AMG8833_NORMAL_MODE, uint8_t fps=AMG8833_10FPS){
	Wire.begin(); // set master mode 
  	Wire.setClock(400000); // I2C frequency at 400 kHz 
  	writeByte(AMG8833_ADDRESS, AMG8833_RST, AMG8833_SOFTWARE_RESET);  // initialize with a reset
  	writeByte(AMG8833_ADDRESS, AMG8833_PCTL, mode); // set operating mode
  	writeByte(AMG8833_ADDRESS, AMG8833_FPSC, fps); // sample rate (0x00 = 10 fps or 0x01 = 1 fps)
}


void AMG8833::readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest) {
			Wire.transfer(address, &subAddress, 1, dest, count); 
}

uint8_t AMG8833::readByte(uint8_t address, uint8_t subAddress) {
	uint8_t temp[1];
	Wire.transfer(address, &subAddress, 1, &temp[0], 1);
	return temp[0];
}

void AMG8833::writeByte(uint8_t address, uint8_t subAddress, uint8_t data) {
	uint8_t temp[2];
	temp[0] = subAddress;
	temp[1] = data;
	Wire.transfer(address, &temp[0], 2, NULL, 0); 
}

int16_t AMG8833::readThermistor()
{
 uint8_t rawData[2] = {0, 0};
 readBytes(AMG8833_ADDRESS, AMG8833_TTHL, 2, &rawData[0]);
 return (int16_t) (((int16_t) rawData[1] << 8) | rawData[0]);
}