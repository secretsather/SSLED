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
