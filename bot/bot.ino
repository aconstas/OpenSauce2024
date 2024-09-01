#include "esc_controller.h";

void setup() {
  // Serial.begin(115200);
  setupESC();
}

void loop() {
  operateESC();
}