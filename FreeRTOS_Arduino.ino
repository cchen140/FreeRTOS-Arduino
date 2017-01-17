#include "Arduino.h"
#include "FreeRTOS_AVR/src/FreeRTOS_AVR.h"
#include "SyntheticTasks.h"

void setup() {

  Serial.begin(57600);

  createSyntheticTasks();

  // start scheduler
  vTaskStartScheduler();

  Serial.println(F("Scheduler stopped."));
  while(1);
}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}
