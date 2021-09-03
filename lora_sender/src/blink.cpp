#include "blink.h"

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(150);
  digitalWrite(LED_BUILTIN, LOW);
}

void blink_n(int n) {
  for (int i=0; i<n; i++) {
    blink();
    delay(200);
  }
}

void blink_message(int message_number) {
  for (int i=0; i<3; i++) {
    blink_n(message_number);
    delay(1000);
  }
}

void setup_blink() {
  pinMode(LED_BUILTIN, OUTPUT);
}