const int photoPin1 = A0; // First photo sensor
const int photoPin2 = A1; // Second photo sensor
const int photoPin3 = A2; // Third photo sensor

void setup()
{
  Serial.begin(115200); // Initialize serial communication

  for (int i = 2; i < 11; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

}

void loop()
{
  // Read values from all three sensors
  int leftSensorValue = analogRead(photoPin1);
  int rightSensorValue = analogRead(photoPin2);
  int frontSensorValue = analogRead(photoPin3);

  // Print the values to serial monitor
  Serial.print("leftSensorValue: ");
  Serial.print(leftSensorValue);
  Serial.print("  rightSensorValue: ");
  Serial.print(rightSensorValue);
  Serial.print("  frontSensorValue: ");
  Serial.println(frontSensorValue);

  delay(1000); // Wait for a second before next reading
}