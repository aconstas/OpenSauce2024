#include "esc_controller.h"
#include "photo_meter.h"

void setup() {
  Serial.begin(115200);
  setupESC();
  delay(1000);
  setupPhotoSensor();
}

void loop() {
  PhotoValues pValues = readPhotoValues();
  operateESCUsingTriangle(pValues.left, pValues.right, pValues.front);
}