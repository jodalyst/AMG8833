#include "AMG8833.h"


AMG8833::AMG8833(){
  for (uint8_t i=0; i<64; i++){
    rawData[i]=0;
  }
}

void AMG8833::initialize(uint8_t address, uint8_t mode, uint8_t fps){
	Wire.begin(); // set master mode 
  	Wire.setClock(400000); // I2C frequency at 400 kHz 
  	writeByte(AMG8833_ADDRESS, AMG8833_RST, AMG8833_SOFTWARE_RESET);  // initialize with a reset
  	writeByte(AMG8833_ADDRESS, AMG8833_PCTL, mode); // set operating mode
  	writeByte(AMG8833_ADDRESS, AMG8833_FPSC, fps); // sample rate (0x00 = 10 fps or 0x01 = 1 fps)
}


uint8_t AMG8833::readBytes(uint8_t deviceAddress, uint8_t registerAddress, uint8_t count, uint8_t * dest) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.endTransmission(false);
  uint8_t i = 0;
  Wire.requestFrom(deviceAddress, count);
  while (Wire.available())
  {
    dest[i] = Wire.read();
    i++;
  }
  return i;
}

uint8_t AMG8833::readByte(uint8_t deviceAddress, uint8_t registerAddress) {
	uint8_t value;
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(deviceAddress, (uint8_t) 1);
  value = Wire.read();
  return value;
}

void AMG8833::writeByte(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress); 
  Wire.write(data);
  Wire.endTransmission();
}

int16_t AMG8833::readThermistor()
{
    uint8_t rawData[2] = {0, 0};
    readBytes(AMG8833_ADDRESS, AMG8833_TTHL, 2, &rawData[0]);
    return (int16_t) (((int16_t) rawData[1] << 8) | rawData[0]);
}

void AMG8833::readGrid(float* tempValues){
    readBytes(AMG8833_ADDRESS, AMG8833_DATA01L, 128, &rawData[0]);
    for(uint16_t ii = 0; ii < 64; ii++) {
      tempValues[ii] = (float) ((int16_t) ( (int16_t) rawData[2*ii + 1] << 8) | rawData[2*ii]);
      tempValues[ii] *=0.25f; // scale to get temperatures in degrees C
    }
}
