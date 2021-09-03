#include "sleep.h"

// from https://github.com/cavemoa/Feather-M0-Adalogger/blob/master/SimpleSleep/SimpleSleep.ino
RTCZero rtc;

void setup_rtc() {
  rtc.begin();
}

void alarmMatch() {
    Println("Waking up...");
}

// from https://github.com/cavemoa/Feather-M0-Adalogger/blob/master/SimpleSleep/SimpleSleep.ino
void deep_sleep(int seconds) {
  seconds = (rtc.getSeconds() + seconds) % 60;
  rtc.setAlarmSeconds(seconds);
  rtc.enableAlarm(rtc.MATCH_SS); // Match seconds only
  rtc.attachInterrupt(alarmMatch); // Attach function to interupt
  rtc.standbyMode();    // Sleep until next alarm match
}