#include "SSLED.h"

SSLED testDisplay(24); //number of LEDs

void setup()
{
}

void loop()
{
  //put data into the buffer
  for(uint8_t index = 0; index < 24; index++){
    testDisplay.set(index, 0xFF, 0, 0); //(LEDtoSet, R, G, B)
  }

  //write the buffer to pixels
  testDisplay.refresh();
}
