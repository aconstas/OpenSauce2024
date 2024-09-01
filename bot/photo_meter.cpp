#include "arduino.h"
#include "photo_meter.h"
#include "pins.h"

void setupPhotoSensor()
{
  for (int i = 2; i < 9; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

}

void readPhotoValues()
{
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

  delay(1000); // Wait for a second before next reading
}