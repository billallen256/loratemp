#include "ms8607.h"

Adafruit_MS8607 ms8607 = Adafruit_MS8607();

sensors_event_t humidity;
sensors_event_t pressure;
sensors_event_t temperature;

void setup_ms8607() {
    if (!ms8607.begin()) {
        Serial.println("Failed to find MS8607 chip");
        while (1) { delay(10); }
    }
    
    Serial.println("MS8607 Found!");

    ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);
    Serial.print("Humidity resolution set to ");
    switch (ms8607.getHumidityResolution()){
        case MS8607_HUMIDITY_RESOLUTION_OSR_12b: Serial.println("12-bit"); break;
        case MS8607_HUMIDITY_RESOLUTION_OSR_11b: Serial.println("11-bit"); break;
        case MS8607_HUMIDITY_RESOLUTION_OSR_10b: Serial.println("10-bit"); break;
        case MS8607_HUMIDITY_RESOLUTION_OSR_8b: Serial.println("8-bit"); break;
    }

    // ms8607.setPressureResolution(MS8607_PRESSURE_RESOLUTION_OSR_4096);
    Serial.print("Pressure and Temperature resolution set to ");
    switch (ms8607.getPressureResolution()){
        case MS8607_PRESSURE_RESOLUTION_OSR_256: Serial.println("256"); break;
        case MS8607_PRESSURE_RESOLUTION_OSR_512: Serial.println("512"); break;
        case MS8607_PRESSURE_RESOLUTION_OSR_1024: Serial.println("1024"); break;
        case MS8607_PRESSURE_RESOLUTION_OSR_2048: Serial.println("2048"); break;
        case MS8607_PRESSURE_RESOLUTION_OSR_4096: Serial.println("4096"); break;
        case MS8607_PRESSURE_RESOLUTION_OSR_8192: Serial.println("8192"); break;
    }
    Serial.println("");
}

void refresh_ms8607_values() {
    ms8607.getEvent(&pressure, &temperature, &humidity);
}

float get_humidity() {
    return humidity.relative_humidity;  // rH
}

float get_pressure() {
    return pressure.pressure;  // hPa
}

float get_temperature() {
    return temperature.temperature;  // C
}