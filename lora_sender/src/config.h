#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>

int const DEEP_SLEEP_SECONDS = 20;
int const BLINK_REPETITIONS = 3;
float const TX_FREQ = 434.0;
int8_t const TX_POWER = 23;

// Comment this line out if running headless.
//#define START_SERIAL

#endif