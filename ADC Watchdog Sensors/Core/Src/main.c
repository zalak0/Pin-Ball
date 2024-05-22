/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "timers.h"
#include "sensors.h"
#include "serial.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
//ADC_HandleTypeDef hadc2;
//__IO uint16_t uhADCxConvertedValue = 0;
//ubAnalogWatchdogStatus = RESET;

//Point Values & Multiplier Durations
uint16_t mult_2_duration = 5000;
uint16_t point_val_1 = 100;
uint8_t multi_trigger = RESET;
//Game Variables
uint8_t end_game = 0;
uint16_t score = 0;
uint16_t game_time = 0;
uint16_t game_state = 0;
uint16_t multiplier = 1;


//Sensor Flags
uint8_t can_score = 1;

/*
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC2_Init(void);
*/

void game_over(void){
	end_game = 1;
}

void valid_input(void){
	can_score = 1;
}

void reset_multiplier(void){
	multiplier = 1;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_1){
		multi_trigger = SET;
	}
}


int main(void) {

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_SETUP();

	START_ADC();

	enable_clocks();
	enable_interrupts();
	//Debugging
	//SerialInitialise(BAUD_115200, &USART1_PORT, 0x00);

	game_state = 1;
	while (game_state == 0){
		//if(HAL_GPIO_ReadPin(GPIO_PIN_1) == SET){
		  //game_state = 1;
		//}
	}

	game_timer(&game_over, 60000); //Duration in milliseconds

	while (game_state == 1){

		if (multi_trigger == SET){

			//Set current multiplier to 5
			multiplier = 5;

			//Set timer to reset multiplier to 1
			multi_timer(&reset_multiplier, 5000);
			multi_trigger = RESET;
		}




		//Point Scoring Logic
		if (ubAnalogWatchdogStatus == SET){

			if(can_score == 1){
				score_timer(&valid_input, 200);
				start_timer();
				can_score = 0;
				score += point_val_1 * multiplier;
			}
		}
		//prevWDS = 0;

		//Clear flag
		ubAnalogWatchdogStatus = RESET;




	    game_time = get_game_time();

		if (end_game == 1){
			game_state = 0;
		}
	}
}


