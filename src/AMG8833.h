#ifndef AMG8833_H
#define EMG8833_H

#include <Wire.h>

#define SERIAL_DEBUG true

// Status and configuration registers
#define AMG8833_PCTL     0x00
#define AMG8833_RST      0x01
#define AMG8833_FPSC     0x02
#define AMG8833_INTC     0x03
#define AMG8833_STAT     0x04
#define AMG8833_SCLR     0x05
#define AMG8833_AVE      0x07
#define AMG8833_INTHL    0x08
#define AMG8833_INTHH    0x09
#define AMG8833_INTLL    0x0A
#define AMG8833_INTLH    0x0B
#define AMG8833_IHYSL    0x0C
#define AMG8833_IHYSH    0x0D
#define AMG8833_TTHL     0x0E
#define AMG8833_TTHH     0x0F

//  Interrupt result registers
#define AMG8833_INT0     0x10  // threshold interrupt for pixels 0 - 7, etc
#define AMG8833_INT1     0x11
#define AMG8833_INT2     0x12
#define AMG8833_INT3     0x13
#define AMG8833_INT4     0x14
#define AMG8833_INT5     0x15
#define AMG8833_INT6     0x16
#define AMG8833_INT7     0x17

// 64, 16-bit words for the 8 x 8 IR array
#define AMG8833_DATA01L  0x80 // pixel 1 low byte
#define AMG8833_DATA01H  0x81 // pixel 1 high byte
//  ...
// These go up and up until we reach below:
#define AMG8833_DATA64L  0xFE // pixel 64 low byte
#define AMG8833_DATA64H  0xFF // pixel 64 high byte

#define AMG8833_ADDRESS 0x68  // 0x68 when ADO = LOW, 0x69 when ADO = HIGH


//Use these with the Power Control Register: AMG8833_PCTL (0x00)

#define AMG8833_NORMAL_MODE 0b00000000 //
#define AMG8833_SLEEP_MODE 0b00010000
#define AMG8833_SB_60I 0b00100000
#define AMG8833_SB_10I 0b00100001

// Reset Register AMG8833_RST      0x01
#define AMG8833_FLAG_RESET 0b00110000
#define AMG8833_SOFTWARE_RESET 0b00111111

//Frame rates for the MG8833_FPSC     0x02 register
#define AMG8833_1FPS 0b00000001
#define AMG8833_10FPS 0b00000000 //default!


class AMG8833 {
	public:
        uint8_t rawData[128];   //raw data array //used to hold array content
    
		AMG8833();
		void initialize(uint8_t mode=AMG8833_NORMAL_MODE, uint8_t fps=AMG8833_10FPS);
		void readGrid(float * tempValues);
		int16_t readThermistor();

	private:
		void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
		uint8_t readByte(uint8_t address, uint8_t subAddress);
		void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);

}
