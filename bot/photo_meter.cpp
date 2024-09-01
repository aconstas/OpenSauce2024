#include "arduino.h"
#include "photo_meter.h"
#include "pins.h"

void setRGBOutput(int r, int g, int b) {
  digitalWrite(LED_R_PIN, r);
  digitalWrite(LED_G_PIN, g);
  digitalWrite(LED_B_PIN, b);
}

void setupPhotoSensor() {
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  setRGBOutput(1, 1, 1);
}

PhotoValues readPhotoValues() {
  // Read values from all three sensors
  int leftSensorValue = analogRead(PHOTO_PIN_1);
  int rightSensorValue = analogRead(PHOTO_PIN_2);
  int frontSensorValue = analogRead(PHOTO_PIN_3);

  // Print the values to serial monitor
  Serial.print("leftSensorValue: ");
  Serial.print(leftSensorValue);
  Serial.print("  rightSensorValue: ");
  Serial.print(rightSensorValue);
  Serial.print("  frontSensorValue: ");
  Serial.println(frontSensorValue);

  return {
    leftSensorValue,
    rightSensorValue,
    frontSensorValue
  };
}