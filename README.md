# AMG8833

Originally inspired by code (and nice breakout module developed <a href="https://github.com/kriswiner/AMG8833" target="_blank">here</a>).  This is a simple i2c library to get images from the module, intended for experimentation purposes.

I can't find an official register map of this device (why would they make this hard get???). Relevant links below:

* Register Map Here: https://www.eewiki.net/display/Motley/Panasonic+Grid+Eye+Memory+Registers
* General Data Sheet Here: https://media.digikey.com/pdf/Data%20Sheets/Panasonic%20Sensors%20PDFs/Grid-EYE_AMG88.pdf

## Methods

```
AMG8833::AMG8833();
```

```
void AMG8833::readGrid(float * tempValues);
```

```
void AMG8833::initialize(uint8_t mode=AMG8833_NORMAL_MODE, uint8_t fps=AMG8833_10FPS);
```

```
int AMG8833::readThermistor();
```


