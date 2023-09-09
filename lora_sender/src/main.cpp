#include <Arduino.h>

#include "blink.h"
#include "gauge.h"
#include "ms8607.h"
#include "power.h"
#include "radio.h"
#include "serial.h"
#include "sleep.h"

void setup()
{
    setup_blink();
    setup_serial();
    setup_ms8607();
    setup_rtc();
    setup_radio();
}

char humidity_buffer[GAUGE_BUFFER_SIZE];
char pressure_buffer[GAUGE_BUFFER_SIZE];
char temperature_buffer[GAUGE_BUFFER_SIZE];
char voltage_buffer[GAUGE_BUFFER_SIZE];

char send_buffer[GAUGE_BUFFER_SIZE*4];

void loop()
{
    refresh_ms8607_values();

    float humidity = get_humidity();
    float pressure = get_pressure();
    float temperature = get_temperature();
    float voltage = get_voltage_data();

    Gauge_str(humidity_buffer, "humi", (int)(humidity*100));
    Gauge_str(pressure_buffer, "pres", (int)(pressure*100));
    Gauge_str(temperature_buffer, "temp", (int)(temperature*100));
    Gauge_str(voltage_buffer, "volt", (int)(voltage*100));

    int send_buffer_used = sprintf(
        send_buffer,
        "%s;%s;%s;%s",
        humidity_buffer,
        pressure_buffer,
        temperature_buffer,
        voltage_buffer
    );

    Println(send_buffer);
    Println(send_buffer_used);

    Println("Sending...");
    delay(10);
    rf95.send((uint8_t *)send_buffer, send_buffer_used+1);
  
    Println("Waiting for packet to complete...");
    delay(10);
    rf95.waitPacketSent();
    
    blink_message(2);
    
    //delay(1000); // Wait 1 second between transmits, could also 'sleep' here!
    Println("Going to sleep...");
    deep_sleep(600);
}
