/*
 * SyntheticTasks.h
 *
 *  Created on: Mar 11, 2015
 *      Author: CY
 */

#ifndef _SYTHETICTASKS_H_
#define _SYTHETICTASKS_H_

#include "FreeRTOS_AVR/src/FreeRTOS_AVR.h"	// for uint32_t type
#include <Arduino.h>	// for some general definition (like true/false)

void createSyntheticTasks(void);
void prvGeneralSyntheticTask(void *pvParameters);

/* Define for application task. */
#define APP_TASK_LOWEST_PRIORITY	tskIDLE_PRIORITY + 2
#define APP_TASK_STACK_SIZE			100

typedef struct TaskParam {
	uint32_t periodUs;
	uint32_t priority;
	uint32_t computationTimeUs;
	uint32_t computeSize;	// reserved, for synthesizing memory usage.
}TaskParam;

#endif /* _SYTHETICTASKS_H_ */
