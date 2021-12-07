/*
  SSLED.h - Stupid Simple WS2812b driver for NodeMCU ESP8266
  Created by George Gardner, December 7, 2021.
  Released into the public domain.

  Only GPIO-03 RXD0 supported (this is your data pin to the pixels)
*/
#ifndef SSLED_h
#define SSLED_h

#include "Arduino.h"
#include <I2S.h>

class SSLED
{
  public:
    SSLED(uint16_t numLEDs);
    void set(uint16_t LEDnumber, uint8_t R, uint8_t G, uint8_t B);
    void refresh();

  private:
    uint32_t _timingLUT[256];
    uint8_t _latchDelay = 5;
    uint32_t* _displayBuffer;//[(numLEDs * 3) + latchDelay] = {0};
    uint32_t _numLEDs;    
};

#endif
