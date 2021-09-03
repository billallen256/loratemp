#include <Arduino.h>

#include "blink.h"
#include "gauge.h"
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
  //delay(1000); // Wait 1 second between transmits, could also 'sleep' here!

  char temp_buffer[GAUGE_BUFFER_SIZE];
  float temperature = tempsensor.readTempC();
  Println(temperature);
  int temp_buffer_used = Gauge_str(temp_buffer, "temp", (int)(temperature*100));
  Println(temp_buffer_used);

  Println("Transmitting..."); // Send a message to rf95_server
  Println(temp_buffer);
  
  Println("Sending...");
  delay(10);
  rf95.send((uint8_t *)temp_buffer, temp_buffer_used+1);
 
  Println("Waiting for packet to complete...");
  delay(10);
  rf95.waitPacketSent();
  message(2);
  Println("Going to sleep...");
  deep_sleep(50);
}