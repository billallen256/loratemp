#include "rtc.h"

// based on https://github.com/cavemoa/Feather-M0-Adalogger/blob/master/SimpleSleep/SimpleSleep.ino

RTCZero rtc;

void setup_rtc() {
    rtc.begin(true);
}

void alarmMatch() {
    Println("Waking up...");
}

int hms_to_day_seconds(int hour, int minute, int second) {
    return (hour * 60 * 60) + (minute * 60) + second;
}

HMS day_seconds_to_hms(int seconds) {
    HMS hms;
    hms.hour = seconds / (60 * 60);
    int hour_seconds = hms.hour * 60 * 60;
    hms.minute = (seconds - hour_seconds) / 60;
    int minute_seconds = hms.minute * 60;
    hms.second = seconds - hour_seconds - minute_seconds;
    return hms;
}

void deep_sleep(int seconds) {
    int wake_seconds_into_day = (get_elapsed() + seconds) % (60 * 60 * 24);
    HMS wake_hms = day_seconds_to_hms(wake_seconds_into_day);
    
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

int get_elapsed() {
    return hms_to_day_seconds(
        rtc.getHours(),
        rtc.getMinutes(),
        rtc.getSeconds()
    );
}