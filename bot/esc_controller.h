#ifndef ESC_CONTROLLER_H
#define ESC_CONTROLLER_H

#include "ESC.h"

// Speed definitions
#define ESC_ARM_VALUE (1500)
#define ESC_SPEED_MIN (1000)  // Set the Minimum Speed in microseconds
#define ESC_SPEED_MAX (2000)  // Set the Maximum Speed in microseconds
#define ESC_MIN_OPERATIONAL_SPEED (90) // A speed below this value will not turn the motor

// Function prototypes
void setupESC();
void setESCSpeeds(int speed, int turnSpeed);
void operateESC();
void operateESCUsingTriangle(int leftSensorValue, int rightSensorValue, int frontSensorValue);
#endif  // ESC_CONTROLLER_H
