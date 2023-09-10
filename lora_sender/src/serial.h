#include <Arduino.h>

#ifndef _SERIAL_H_
#define _SERIAL_H_ 1

#ifdef START_SERIAL
#define Println(a) (Serial.println(a))
#define Print(a) (Serial.print(a))
#else
#define Println(a)
#define Print(a)
#endif

void setup_serial();

#endif