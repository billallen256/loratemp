#include "sleep.h"

// based on https://github.com/cavemoa/Feather-M0-Adalogger/blob/master/SimpleSleep/SimpleSleep.ino

RTCZero rtc;

void setup_rtc() {
    rtc.begin();
}

void alarmMatch() {
    Println("Waking up...");
}

int hms_to_seconds(int hour, int minute, int second) {
    return (hour * 60 * 60) + (minute * 60) + second;
}

HMS seconds_to_hms(int seconds) {
    HMS hms;
    hms.hour = seconds / (60 * 60);
    int hour_seconds = hms.hour * 60 * 60;
    hms.minute = (seconds - hour_seconds) / 60;
    int minute_seconds = hms.minute * 60;
    hms.second = seconds - hour_seconds - minute_seconds;
    return hms;
}

void deep_sleep(int seconds) {
    int now_hour = rtc.getHours();
    int now_minute = rtc.getMinutes();
    int now_second = rtc.getSeconds();

    int wake_epoch = hms_to_seconds(now_hour, now_minute, now_second) + seconds;
    HMS wake_hms = seconds_to_hms(wake_epoch);
    
    Println("Now:");
    Println(now_hour);
    Println(now_minute);
    Println(now_second);
    
    Println("Waking:");
    Println(wake_hms.hour);
    Println(wake_hms.minute);
    Println(wake_hms.second);

    rtc.setAlarmHours(wake_hms.hour);
    rtc.setAlarmMinutes(wake_hms.minute);
    rtc.setAlarmSeconds(wake_hms.second);
    rtc.enableAlarm(rtc.MATCH_HHMMSS);
    rtc.attachInterrupt(alarmMatch); // Attach function to interupt
    rtc.standbyMode();    // Sleep until next alarm match
}