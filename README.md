# AMG8833

Originally inspired by code (and nice breakout module developed <a href="https://github.com/kriswiner/AMG8833" target="_blank">here</a>).  This is a simple i2c library to get images from the module, intended for experimentation purposes.

I can't find an official register map of this device (why would they make this hard get???). Relevant links below:

* Register Map Here: https://www.eewiki.net/display/Motley/Panasonic+Grid+Eye+Memory+Registers
* General Data Sheet Here: https://media.digikey.com/pdf/Data%20Sheets/Panasonic%20Sensors%20PDFs/Grid-EYE_AMG88.pdf

This library **should** be general enough to work with most devices. It uses the `Wire` library for its i2c, which works perfectly well/has been optimized for the Teensy3.2 which I developed/tested this on...the shortcomings of this library are known and I've tried to overcome/avoid them for use in this library, notably the 32-byte read limit.

## Class Functions:

### Public:

* `AMG8833::AMG8833()`:  Initializes object. Also zeros out the one real useful class variable `rawData`, a 128-long `uint8_t` array for holding the most recent grid of data.

* `void AMG8833::readGrid(float * tempValues)`

* `void initialize(uint8_t address= AMG8833_ADDRESS, uint8_t mode=AMG8833_NORMAL_MODE, uint8_t fps=AMG8833_10FPS)`:  Initialize. You can give it the address (based on pull-up or pull down of a pin (module noted above is hardwired to `0x68`). There are four imaging modes.  This defaults to normal.  Then there is frame rate...this defaults to 10FPS, but you can do 1FPS 

* `int AMG8833::readThermistor()`: Read's onboard thermistor

* `

### Private:

These interface directly with the chip/handle the i2c using the `Wire` library that is default with Arduino/Teensy.  

* `void writeByte(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data)`: Write a byte to the device. Should probably return some sort of success indicator, but for now it is void
* `uint8_t readByte(uint8_t deviceAddress, uint8_t registerAddress)`: Read a single byte (returns it)
* `uint8_t readBytes(uint8_t deviceAddress, uint8_t registerAddress, uint8_t count, uint8_t * dest)`: Read a bunch of bytes in series...tell it how many...normally the multi-read of `Wire` is limited to 32 bytes, so this adds some support on-top to get an arbitrarily long sequential read, which is needed for all 128 bytes of the full-grid.


##Exampe Sketch `AMG8833_example.ino`

Real simple sketch using the library.  Again the code  <a href="https://github.com/kriswiner/AMG8833" target="_blank">here</a> gives a more functional example with a TFT, but was a bit too specific for my needs. This sketch simply draws out an "image" over Serial (Serial Monitor) using an aribtrarily-designted threshold to decide what is a `*` and what is a ` ` character. So you end up with images like this (when I was putting my finger over half the sensor's field of view:

```
          * *   
    * * * * * * 
      * * * * * 
      * * * * * 
      * * * * * 
        * * * * 
        * * * * 
```

Obviously this demo loses a lot of information through the inherent discretization, and doesn't show the chip's full potential, but this is more of a self-contained "is-it-working" demo than the one in the link above.



