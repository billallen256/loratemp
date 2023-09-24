#include "blink.h"

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(BLINK_ON_MS);
  digitalWrite(LED_BUILTIN, LOW);
}

void blink_n(int n) {
  for (int i = 0; i < n; ++i) {
    blink();
    delay(BLINK_OFF_MS);
  }
}

void blink_message(int message_number) {
  for (int i = 0; i < BLINK_REPETITIONS; ++i) {
    blink_n(message_number);
    delay(BLINK_SEPARATION_MS);
  }
}

void blink_message_forever(int message_number) {
  while (true) {
    blink_message(message_number);
  }
}

void setup_blink() {
  pinMode(LED_BUILTIN, OUTPUT);
}