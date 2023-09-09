#ifndef _SLEEP_H_
#define _SLEEP_H_

#include <time.h>      // to convert to epoch time
#include <RTCZero.h>   // for built-in real-time-clock

#include "serial.h"

void setup_rtc();
void deep_sleep(int seconds);

struct HMS {
    int hour;
    int minute;
    int second;
};

#endif