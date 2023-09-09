#ifndef _MS8607_H_
#define _MS8607_H_

#include <Adafruit_MS8607.h>

void setup_ms8607();
void refresh_ms8607_values();
float get_humidity();
float get_pressure();
float get_temperature();

#endif