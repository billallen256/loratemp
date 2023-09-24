#include<Arduino.h>

#include "config.h"

int const BLINK_OFF_MS = 200;
int const BLINK_ON_MS = 150;
int const BLINK_SEPARATION_MS = 1000;

void blink_message(int);
void blink_message_forever(int);
void setup_blink();