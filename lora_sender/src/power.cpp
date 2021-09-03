#include "power.h"

// from https://learn.adafruit.com/adafruit-feather-m0-adalogger/power-management
float get_voltage_data() {
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  return measuredvbat;
}