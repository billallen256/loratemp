#include <Arduino.h>

#include "blink.h"
#include "config.h"
#include "metric.h"
#include "ms8607.h"
#include "power.h"
#include "radio.h"
#include "rtc.h"
#include "serial.h"

void setup()
{
    setup_blink();
    setup_serial();
    setup_ms8607();
    setup_rtc();
    setup_radio(TX_FREQ, TX_POWER);
}

char humidity_buffer[METRIC_BUFFER_SIZE];
char pressure_buffer[METRIC_BUFFER_SIZE];
char temperature_buffer[METRIC_BUFFER_SIZE];
char voltage_buffer[METRIC_BUFFER_SIZE];

char send_buffer[METRIC_BUFFER_SIZE*5];

void loop() {
    refresh_ms8607_values();

    float humidity = get_humidity();
    float pressure = get_pressure();
    float temperature = get_temperature();
    float voltage = get_voltage_data();

    Metric_str(humidity_buffer, "humi", (int)(humidity*100), "g");
    Metric_str(pressure_buffer, "pres", (int)(pressure*100), "g");
    Metric_str(temperature_buffer, "temp", (int)(temperature*100), "g");
    Metric_str(voltage_buffer, "volt", (int)(voltage*100), "g");

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

    Println("rf95.send()...");
    delay(100);
    
    if (rf95.send((uint8_t *)send_buffer, send_buffer_used+1)) {
        Println("waitPacketSent()...");
        delay(100);
        
        if (rf95.waitPacketSent(WAIT_PACKET_SENT_MS)) {
            Println("waitPacketSent() returned true");
            blink_message(1);
        } else {
            Println("waitPacketSent() returned false");
            blink_message_forever(3);
        }
    } else {
        Println("send() returned false");
        blink_message_forever(2);
    }

    Println("Going to sleep...");
    deep_sleep(DEEP_SLEEP_SECONDS);
}
