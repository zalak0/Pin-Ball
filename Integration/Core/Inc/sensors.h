#ifndef SENSOR_HEADER
#define SENSOR_HEADER
/*
	Header file for all sensor/HAL related code
*/

//Runs required setup functions for HAL interrupts.
void HAL_setup(void);

//Configure system clock
void SystemClock_Config(void);

//Initialise GPIO
void MX_GPIO_Init(void);

#endif
