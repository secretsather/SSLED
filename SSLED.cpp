/*
  SSLED.h - Stupid Simple WS2812b driver for NodeMCU ESP8266
  Created by George Gardner, December 7, 2021.
  Released into the public domain.

  Only GPIO-03 RXD0 supported (this is your data pin to the pixels)
*/

#include "Arduino.h"
#include "SSLED.h"
#include <I2S.h>

SSLED::SSLED(uint16_t numLEDs) : _displayBuffer(new uint32_t[(numLEDs * 3)])// + _latchDelay])
{
  //record number of leds to private variable for use later
  _numLEDs = numLEDs;

  //fill the latch delay with zeros
  for (uint8_t i = (numLEDs * 3) - 1; i < ((numLEDs * 3));i++){// + _latchDelay); i++) {
    _displayBuffer[i] = 0;
  }

  //populate the look up table for color to timing output conversion
  for (uint16_t i = 0; i < 256 ; i++) {
    _timingLUT[i] = 0b10001000100010001000100010001000;
    for (uint8_t j = 0; j < 8; j++) {
      if (i & (1 << j)) {
        _timingLUT[i] |= 0b1110 << (j * 4);
      }
    }
  }

  //fill the display buffer with zeros (i.e. 0b1000) to start
  for (uint16_t i = 0; i < numLEDs; i++) {
    set(i, 0, 0, 0);
  }

  //init I2S @ 3.2MHz (double set_rate if running at 80mhz)
  i2s_set_bits(16);
  i2s_set_rate(100000);
  i2s_rxtxdrive_begin(false, true, false, false);
}

void SSLED::set(uint16_t LEDnumber, uint8_t R, uint8_t G, uint8_t B) {
  _displayBuffer[(LEDnumber * 3) + 0] = _timingLUT[G];
  _displayBuffer[(LEDnumber * 3) + 1] = _timingLUT[R];
  _displayBuffer[(LEDnumber * 3) + 2] = _timingLUT[B];
}

void SSLED::refresh() {
  //for now, padding is needed. From what I can determine, if the buffer is empty, a buffer underrun occurs due to the transmission
  //being faster than the code can provide... this causes the signal to be split up mid-stream
  //if you start sending data with an empty buffer. 
  
  //add padding (this also eliminates the need to have time added to 'latch' but significantly decreases our output speed.
  for (uint16_t i = 0; i < 64; i++){ //100 = ~1mS
    i2s_write_sample(0x0);
  }

  //write the data
  for (uint16_t i = 0; i < (_numLEDs * 3);i++){// + _latchDelay; i++) {
    i2s_write_sample(_displayBuffer[i]);
    //if(i2s_is_empty()) digitalWrite(2,0);
  }
}
