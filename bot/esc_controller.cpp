#include "esc_controller.h"
#include "pins.h"

ESC myESC (ESC_LEFT_PIN, SPEED_MIN, SPEED_MAX, 1500);                 // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC myESC1 (ESC_RIGHT_PIN, SPEED_MIN, SPEED_MAX, 1500);
int oESC;                                                 // Variable for the speed sent to the ESC

void setupESC() {
  myESC.arm(); 
  myESC1.arm();                                           // Send the Arm value so the ESC will be ready to take commands
  delay(5000);                                            // Wait for a while
}

void operateESC() {
  for (oESC = SPEED_MIN; oESC <= SPEED_MAX; oESC += 1) {  // goes from 1000 microseconds to 2000 microseconds
    myESC.speed(oESC);
    myESC1.speed(oESC);                                     // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed
  }
  delay(1000);
  for (oESC = SPEED_MAX; oESC >= SPEED_MIN; oESC -= 1) {  // goes from 2000 microseconds to 1000 microseconds
    myESC.speed(oESC);
    myESC1.speed(oESC);                                     // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed  
   }
  delay(5000);                                            // Wait for a while befor restart
}