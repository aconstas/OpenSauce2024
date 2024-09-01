#include "esc_controller.h"
#include "pins.h"
#include "Server.h"

// a constant representing the detection of the dark color tapeline
const int DARK_RANGE = 30;
// ESC leftMotor(ESC_LEFT_PIN, ESC_SPEED_MIN, ESC_SPEED_MAX, ESC_ARM_VALUE);  // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
// ESC rightMotor(ESC_RIGHT_PIN, ESC_SPEED_MIN, ESC_SPEED_MAX, ESC_ARM_VALUE);
Servo leftHBridge;
Servo rightHBridge;

void setupESC() {
  //leftMotor.calib();
  //rightMotor.calib();
  // leftHBridge.attach(ESC_LEFT_PIN);
  // rightHBridge.attach(ESC_RIGHT_PIN);
  pinMode(ESC_LEFT_PIN, OUTPUT);
  pinMode(ESC_RIGHT_PIN, OUTPUT);
  pinMode(ESC_LEFT_REV_PIN, OUTPUT);
  pinMode(ESC_RIGHT_REV_PIN, OUTPUT);

  // leftMotor.arm();
  // rightMotor.arm();  // Send the Arm value so the ESC will be ready to take commands
}

void stop(int delayAmount) {
  delay(delayAmount);
  analogWrite(ESC_LEFT_PIN, 0);
  analogWrite(ESC_RIGHT_PIN, 0);
  digitalWrite(ESC_LEFT_REV_PIN, 0);
  digitalWrite(ESC_RIGHT_REV_PIN, 0);
}

struct Speeds {
  int left;
  int right;
};

/*
  Speed should be between 0 and 500
  -2 will go left fast
  -1 turnspeed will go left
  0 turnspeed will go straight
  1 will go right
  2 will go right fast
  the left and right speeds will be calculated based on the speed and turnSpeed
*/
Speeds speedCalc(int speed, int turnSpeed) {
  if (turnSpeed == 1) {
    return {
      speed, 0
    };
  } else if (turnSpeed == -1) {
    return {
      0, speed
    };
  } else {
    return {
      speed, speed
    };
  }

  // int offset = turnSpeed * speed;
  // int absOffset = abs(offset);
  // int maxSpeed = speed + absOffset;

  // if (maxSpeed > 500) {
  //   speed = speed - absOffset;
  // } else if (speed < ESC_MIN_OPERATIONAL_SPEED) {
  //   speed = ESC_MIN_OPERATIONAL_SPEED;
  // }
  // if (turnSpeed > 2) {
  //   turnSpeed = 2;
  // } else if (turnSpeed < 0) {
  //   turnSpeed = 0;
  // }

  // int leftSpeed = speed;
  // int rightSpeed = speed;

  // // positive offset will turn right, so left motor should be faster and right motor should be slower
  // leftSpeed += offset;
  // rightSpeed -= offset;

  // // It looks like values 0-ESC_MIN_OPERATIONAL_SPEED are still trying to move. but esc does not move below ESC_MIN_OPERATIONAL_SPEED. Let's make all values below ESC_MIN_OPERATIONAL_SPEED round up to ESC_MIN_OPERATIONAL_SPEED
  // if (leftSpeed < ESC_MIN_OPERATIONAL_SPEED && leftSpeed > 0) {
  //   leftSpeed = ESC_MIN_OPERATIONAL_SPEED;
  // }
  // if (rightSpeed < ESC_MIN_OPERATIONAL_SPEED && rightSpeed > 0) {
  //   rightSpeed = ESC_MIN_OPERATIONAL_SPEED;
  // }

  // return { leftSpeed, rightSpeed };
}

// A positive turnSpeed will turn right
// A negative turnSpeed will turn left
void setESCSpeeds(int speed, int turnSpeed) {
  Speeds speeds = speedCalc(speed, turnSpeed);
  // Serial.print("speed: ");
  // Serial.print(speed);
  // Serial.print(" turnSpeed: ");
  // Serial.print(turnSpeed);
  // Serial.print(" left speed: ");
  // Serial.print(speeds.left);
  // Serial.print(" right speed: ");
  // Serial.print(speeds.right);
  // Serial.print("\n");
  // if (speeds.left > 0 && speeds.right > 0) {
  //   analogWrite(ESC_LEFT_PIN, 200);
  //   analogWrite(ESC_RIGHT_PIN, 200);
  //   delay(5);
  // }
  analogWrite(ESC_LEFT_PIN, speeds.left);
  analogWrite(ESC_RIGHT_PIN, speeds.right);
  // stop(40);

  // leftHBridge.write(speeds.left);
  // rightHBridge.write(speeds.right);
  if (speeds.left == 0) {  // this means reverse
    analogWrite(ESC_RIGHT_PIN, 0);
    analogWrite(ESC_LEFT_PIN, 160);
    digitalWrite(ESC_LEFT_REV_PIN, 1);
    stop(100);
  } else {
    digitalWrite(ESC_LEFT_REV_PIN, 0);
  }

  if (speeds.right == 0) {  // this means reverse
    analogWrite(ESC_LEFT_PIN, 0);
    analogWrite(ESC_RIGHT_PIN, 160);
    digitalWrite(ESC_RIGHT_REV_PIN, 1);
    stop(100);
  } else {
    digitalWrite(ESC_RIGHT_REV_PIN, 0);
  }
}

void operateESC() {
  setESCSpeeds(100, 0);   // Move forward
  delay(1000);            // for 1 second
  setESCSpeeds(100, 1);   // Turn right
  delay(1000);            // for 1 second
  setESCSpeeds(100, -1);  // Turn left
  delay(1000);            // for 1 second

  delay(5000);  // Wait for a while befor restart
}

int prevDirection = 0;
void operateESCUsingTriangle(int leftSensorValue, int rightSensorValue, int frontSensorValue) {
  // get the max between two sensors then get the max of those two and the third sensor.
  // This is how we get our max value
  int max_sensor_value = max(max(frontSensorValue, leftSensorValue), rightSensorValue) + 1;

  // min value
  int min_sensor_value = max_sensor_value - DARK_RANGE;

  // This is how we know if we are detecting the dark color tapeline
  bool leftIsDark = (leftSensorValue >= min_sensor_value) && (leftSensorValue <= max_sensor_value);
  bool rightIsDark = (rightSensorValue >= min_sensor_value) && (rightSensorValue <= max_sensor_value);
  bool frontIsDark = (frontSensorValue >= min_sensor_value) && (frontSensorValue <= max_sensor_value);

  // Serial.write("LD: ");
  // Serial.write(leftIsDark ? "true" : "false");
  // Serial.write(" RD: ");
  // Serial.write(rightIsDark ? "true" : "false");
  // Serial.write(" FD: ");
  // Serial.write(frontIsDark ? "true" : "false");
  // Serial.write("\n");

  // // I go forward when ... (frontisDark or (frontisdark and LeftisDark and rightisDark))
  if (frontIsDark) {
    // if (frontIsDark && leftIsDark && rightIsDark) {
    //   if (prevDirection == -1) {
    //     setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, -1);
    //   } else if (prevDirection == 1) {
    //     setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, 1);
    //   }
    // } else {
    setESCSpeeds(30, 0);  // Move forward
    prevDirection = 0;
    // }
  } else if (!leftIsDark) {
    // I go right when ... right is dark, front is not dark, and left is not dark
    setESCSpeeds(30, 1);
    prevDirection = 1;
  } else if (!rightIsDark) {  // I go left when right is not detecting dark tapeline
    // go left
    setESCSpeeds(30, -1);
    prevDirection = -1;
  }

  // // If left and right are dark, keep going. (also will trigger if all are dark.)
  // if (leftIsDark && rightIsDark) {
  //   setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, 0);  // Move forward
  // } else if (leftIsDark && frontIsDark) {
  //   // I go left when left and front are on the line
  //   setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, -1);
  // } else if (leftIsDark) {
  //   // I go left faster when left is on the line
  //   setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, -2);
  // } else if (rightIsDark && frontIsDark) {
  //   // I go right when right and front are on the line
  //   setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, 1);
  // } else if (rightIsDark) {
  //   // I go right faster when left is on the line
  //   setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, 2);
  // } else {
  //   setESCSpeeds(ESC_MIN_OPERATIONAL_SPEED, 0);  // Move forward
  // }
}