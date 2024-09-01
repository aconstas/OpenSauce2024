#include "esc_controller.h"
#include "photo_meter.h"

void setup() {
  // Serial.begin(115200);
  // Serial.println("Start setup");
  setupESC();
  // Serial.println("ESC Setup");
  delay(1000);
  setupPhotoSensor();
  // Serial.println("Sensors ready");
}

int color = 0;

void loop() {
  // Serial.println("Start loop");
  PhotoValues pValues = readPhotoValues();
  if (color == 0) {
    // setRGBOutput(1, 1, 1);
  // } else if (color == 1) {
  //   setRGBOutput(1, 0, 0);
  } else if (color == 1) {
    setRGBOutput(0, 1, 0);
  // } else if (color == 3) {
  //   setRGBOutput(0, 0, 1);
  }
  color++;
  if (color > 1) {
    color = 0;
  }
  delay(30); // delay after color change to let sensors read
  operateESCUsingTriangle(pValues.left, pValues.right, pValues.front);
  // delay(100); // delay after color change to let sensors read
}