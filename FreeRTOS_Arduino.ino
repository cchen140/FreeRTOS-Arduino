#include "Arduino.h"
#include "FreeRTOS_AVR/src/FreeRTOS_AVR.h"
#include "SyntheticTasks.h"

void setup() {

  Serial.begin(57600);
  Serial.println(F("Serial port is ready."));

  pinMode(13, OUTPUT);

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

void myPrintlnU32(uint32_t ulVal) {
	Serial.println(ulVal);
}

void myPrintln(const char str[]) {
	Serial.println(str);
}

void myPrintlnDouble(double ulVal) {
	Serial.println(ulVal);
}

void myPrintlnUchar(unsigned char ucVal) {
	Serial.println(ucVal);
}
