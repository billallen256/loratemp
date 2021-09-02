#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "serial.h"

#ifndef _RADIO_H_
#define _RADIO_H_ 1

// Feather m0 w/wing 
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     6    // "D"

#define RF95_FREQ 434.0

extern RH_RF95 rf95;

void setup_radio();

#endif