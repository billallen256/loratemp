#ifndef _RADIO_H_
#define _RADIO_H_

#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "serial.h"

// Find various configurations at
// https://learn.adafruit.com/adafruit-feather-32u4-radio-with-lora-radio-module/using-the-rfm-9x-radio

// Feather m0 w/wing 
//#define RFM95_RST     11   // "A"
//#define RFM95_CS      10   // "B"
//#define RFM95_INT     6    // "D"

// Feather M0 RFM9x (m0 with built-in radio)
#define RFM95_CS   8
#define RFM95_RST  4
#define RFM95_INT  3

extern RH_RF95 rf95;

void setup_radio(float const freq, int8_t const power);

#endif