#ifndef ESC_CONTROLLER_H
#define ESC_CONTROLLER_H

#include "ESC.h"

// Speed definitions
#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Maximum Speed in microseconds

// ESC objects
extern ESC myESC;
extern ESC myESC1;

// Speed variable
extern int oESC;

// Function prototypes
void setupESC();
void operateESC();

#endif // ESC_CONTROLLER_H
