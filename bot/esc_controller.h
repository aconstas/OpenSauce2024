#ifndef ESC_CONTROLLER_H
#define ESC_CONTROLLER_H

#include "ESC.h"

// Speed definitions
#define ESC_ARM_VALUE (1500)
#define ESC_SPEED_MIN (1000)  // Set the Minimum Speed in microseconds
#define ESC_SPEED_MAX (2000)  // Set the Maximum Speed in microseconds

// Function prototypes
void setupESC();
void setESCSpeeds(int speed, float turnSpeed);
void operateESC();

#endif  // ESC_CONTROLLER_H
