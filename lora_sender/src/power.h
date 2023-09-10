#ifndef _POWER_H_
#define _POWER_H_

#include<Arduino.h>

// Define the battery voltage pin
// from https://learn.adafruit.com/adafruit-feather-m0-adalogger/power-management
#define VBATPIN A7

float get_voltage_data();

#endif