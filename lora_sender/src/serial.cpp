#include "serial.h"

void setup_serial()
{
  #ifdef START_SERIAL
    Serial.begin(115200);
    while (!Serial) {
      delay(1);
    }

    Println("setup_serial() complete");
  #endif
}