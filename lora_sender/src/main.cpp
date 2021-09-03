#include <Arduino.h>

#include "blink.h"
#include "gauge.h"
#include "power.h"
#include "radio.h"
#include "serial.h"
#include "sleep.h"
#include "temperature.h"

void setup()
{
    setup_blink();
    setup_serial();
    setup_rtc();
    setup_radio();
    setup_temperature();
}
 
void loop()
{
    char temperature_buffer[GAUGE_BUFFER_SIZE];
    float temperature = tempsensor.readTempC();
    Gauge_str(temperature_buffer, "temp", (int)(temperature*100));

    char voltage_buffer[GAUGE_BUFFER_SIZE];
    float voltage = get_voltage_data();
    Gauge_str(voltage_buffer, "volt", (int)(voltage*100));

    char send_buffer[GAUGE_BUFFER_SIZE*2];
    int send_buffer_used = sprintf(send_buffer, "%s;%s", temperature_buffer, voltage_buffer);

    Println(send_buffer);
    Println(send_buffer_used);
    
    Println("Sending...");
    delay(10);
    rf95.send((uint8_t *)send_buffer, send_buffer_used+1);
  
    Println("Waiting for packet to complete...");
    delay(10);
    rf95.waitPacketSent();
    
    blink_message(2);
    
    delay(1000); // Wait 1 second between transmits, could also 'sleep' here!
    //Println("Going to sleep...");
    //deep_sleep(300);
}