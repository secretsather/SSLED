# SSLED
Stupid Simple WS2812b Driver for NodeMCU ESP8266

Only supported for GPIO-03, which is the RX/D0 Pin on the NodeMCU. This should work for other ESP8266 variants so as long as you're using the I2S data out pin (i.e. I2SO_DATA) 

Example usage in Arduino IDE:
```
#include "SSLED.h"

SSLED testDisplay(24); //number of LEDs

void setup()
{
}

void loop()
{
  //fill the buffer
  for(uint8_t index = 0; index < 24; index++){
    testDisplay.set(index, 0xFF, 0x00, 0x00); //(LEDtoSet, R, G, B)
  }

  //write the buffer to pixels
  testDisplay.refresh();
}
```
