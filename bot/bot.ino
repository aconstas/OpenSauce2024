#include "esc_controller.h"
#include "photo_meter.h"

void setup() {
  Serial.begin(115200);
  setupESC();
  setupPhotoSensor();
}

void loop() {
  readPhotoValues();
  // operateESC();
}