#include "sleep.h"

// based on https://github.com/cavemoa/Feather-M0-Adalogger/blob/master/SimpleSleep/SimpleSleep.ino

RTCZero rtc;

void setup_rtc() {
    rtc.begin();
}

void alarmMatch() {
    Println("Waking up...");
}

void deep_sleep(int seconds) {
    int sleep_hours = seconds / (60 * 60);
    int sleep_minutes = seconds / 60;
    int sleep_seconds = seconds - (sleep_hours * 60 * 60) - (sleep_minutes * 60);
    
    int now_hour = rtc.getHours();
    int now_minute = rtc.getMinutes();
    int now_second = rtc.getSeconds();
    
    int wake_hour = (now_hour + sleep_hours) % 24;
    int wake_minute = (now_minute + sleep_minutes) % 60;
    int wake_second = (now_second + sleep_seconds) % 60;
    
    Println("Now:");
    Println(now_hour);
    Println(now_minute);
    Println(now_second);
    
    Println("Waking:");
    Println(wake_hour);
    Println(wake_minute);
    Println(wake_second);

    rtc.setAlarmHours(wake_hour);
    rtc.setAlarmMinutes(wake_minute);
    rtc.setAlarmSeconds(wake_second);
    rtc.enableAlarm(rtc.MATCH_HHMMSS);
    rtc.attachInterrupt(alarmMatch); // Attach function to interupt
    rtc.standbyMode();    // Sleep until next alarm match
}