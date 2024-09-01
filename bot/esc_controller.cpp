#include "esc_controller.h"
#include "pins.h"

ESC leftMotor(ESC_LEFT_PIN, ESC_SPEED_MIN, ESC_SPEED_MAX, ESC_ARM_VALUE);  // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC rightMotor(ESC_RIGHT_PIN, ESC_SPEED_MIN, ESC_SPEED_MAX, ESC_ARM_VALUE);

int oESC;  // Variable for the speed sent to the ESC

void setupESC() {
  leftMotor.arm();
  rightMotor.arm();  // Send the Arm value so the ESC will be ready to take commands
}

void stop() {
  leftMotor.speed(ESC_ARM_VALUE);
  rightMotor.speed(ESC_ARM_VALUE);
}

struct Speeds {
  int left;
  int right;
};

/*
  Speed should be between 0 and 500
  -1 turnspeed will go left
  0 turnspeed will go straight
  1 will go right
  the left and right speeds will be calculated based on the speed and turnSpeed
*/
Speeds speedCalc(int speed, float turnSpeed) {
  int offset = turnSpeed * speed;
  int maxSpeed = speed + abs(turnSpeed * speed);

  if (speed > maxSpeed) {
    speed = maxSpeed;
  } else if (speed < 0) {
    speed = 0;
  }
  if (turnSpeed > 2) {
    turnSpeed = 2;
  } else if (turnSpeed < 0) {
    turnSpeed = 0;
  }

  int leftSpeed = speed;
  int rightSpeed = speed;

  // positive offset will turn right, so left motor should be faster and right motor should be slower
  leftSpeed += offset;
  rightSpeed -= offset;

  return { leftSpeed, rightSpeed };
}

// A positive turnSpeed will turn right
// A negative turnSpeed will turn left
void setESCSpeeds(int speed, float turnSpeed) {
  Speeds speeds = speedCalc(speed, turnSpeed);
  leftMotor.speed(ESC_ARM_VALUE - speeds.left);
  rightMotor.speed(ESC_ARM_VALUE + speeds.right);
}

void operateESC() {
  setESCSpeeds(100, 0);     // Move forward
  delay(1000);              // for 1 second
  setESCSpeeds(100, 0.5);   // Turn right
  delay(1000);              // for 1 second
  setESCSpeeds(100, -0.5);  // Turn left
  delay(1000);              // for 1 second

  stop();       // Stop the motors
  delay(5000);  // Wait for a while befor restart
}

void operateESCUsingTriangle(int frontSensorValue, int leftSesnsorValue, int rightSensorValue) {
  // TODO: implement after we get code from photo_meter.cpp that gives us sensor values
}