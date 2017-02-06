#include "SyntheticTasks.h"

TaskParam appTaskParamArray[] = {
//  period (us), priority, computation time (us), computing size
		{ 1000000, APP_TASK_LOWEST_PRIORITY, 	500000, 0 },
		{ 200000, APP_TASK_LOWEST_PRIORITY + 1, 43000, 0 },
//		{ 10000, APP_TASK_LOWEST_PRIORITY + 2, 1900, 0 }
//		,
//		{20000, APP_TASK_LOWEST_PRIORITY+3, 100, 0},
//		{18000, APP_TASK_LOWEST_PRIORITY+4, 100, 0},
//		{18000, APP_TASK_LOWEST_PRIORITY+5, 100, 0},
//		{18000, APP_TASK_LOWEST_PRIORITY+6, 100, 0},
//		{20000, APP_TASK_LOWEST_PRIORITY+7, 100, 0},
//		{20000, APP_TASK_LOWEST_PRIORITY+8, 100, 0},
//		{32000, APP_TASK_LOWEST_PRIORITY+9, 100, 0}
////		,
//		{32000, APP_TASK_LOWEST_PRIORITY+10, 100, 0}
//		,
//		{32000, APP_TASK_LOWEST_PRIORITY+11, 100, 0}
//		,
//		{10000, APP_TASK_LOWEST_PRIORITY+12, 100, 0}
////		,
//		{10000, APP_TASK_LOWEST_PRIORITY+13, 100, 0}
//		,
//		{10000, APP_TASK_LOWEST_PRIORITY+14, 100, 0}

//		{200/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY, SIZE_OF_APP_ARRAY/64},
//		{150/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+1, SIZE_OF_APP_ARRAY/32},
//		{66/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+2, SIZE_OF_APP_ARRAY/4},
//		{33/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+3, SIZE_OF_APP_ARRAY},
//		{20/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+4, SIZE_OF_APP_ARRAY/64},
//		{20/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+4, SIZE_OF_APP_ARRAY/8},
//		{20/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+4, SIZE_OF_APP_ARRAY/16},
//		{13/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+5, SIZE_OF_APP_ARRAY/64},
//		{10/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+6, SIZE_OF_APP_ARRAY/2},
//		{7/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+7, SIZE_OF_APP_ARRAY/32},
//		{5/portTICK_RATE_MS, APP_TASK_LOWEST_PRIORITY+8, SIZE_OF_APP_ARRAY/64}
		};

void createSyntheticTasks(void) {
	int numberOfAppTask = sizeof(appTaskParamArray) / sizeof(TaskParam);
	char taskName[10];	// Format is APP-1, APP-2, and so on.
	int loop;

	for (loop = 0; loop < numberOfAppTask; loop++) {
		// Build the string of task name.
		sprintf(taskName, "APP-%d", loop + 1);

		xTaskCreateForTaskShuffler(prvGeneralSyntheticTask, /* The function that implements the task. */
		taskName, /* The text name assigned to the task - for debug only as it is not used by the kernel. */
		APP_TASK_STACK_SIZE,/* The size of the stack to allocate to the task. */
		&(appTaskParamArray[loop]), /* The parameter passed to the task. */
		appTaskParamArray[loop].priority, /* The priority assigned to the task. */
		NULL,	/* The task handle is not required, so NULL is passed. */
		appTaskParamArray[loop].periodUs,
		appTaskParamArray[loop].computationTimeUs);
	}
}

TickType_t firstTickCount = 0; // A variable for aligning start times across all tasks.
void prvGeneralSyntheticTask(void *pvParameters) {
	TaskParam *pvTaskParam = pvParameters;

	// Compute period in ticks.
	const TickType_t xPeriodInTicks = (pvTaskParam->periodUs) / (1000000L/configTICK_RATE_HZ);

	// Initialize the xLastWakeTime variable with the current time.
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	// To align the start point of every application task.
	if (firstTickCount == 0) {
		firstTickCount = xLastWakeTime;
	} else {
		xLastWakeTime = firstTickCount;
	}

	while (true) {
		// Use delay function to synthesize computation load.

		/* Since delayMicroseconds() is not precise when delaying more than
		 * 1000 microseconds (1ms), we use delay() for delays above 1ms. */
		delay(pvTaskParam->computationTimeUs/1000);
		delayMicroseconds(pvTaskParam->computationTimeUs%1000);

		// Yield
		vTaskDelayUntil(&xLastWakeTime, xPeriodInTicks);
	}
}
