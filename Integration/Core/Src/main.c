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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "timers.h"
#include "sensors.h"

//Point Values & Multiplier Durations
uint16_t mult_2_duration = 5000;
uint16_t point_val_1 = 100;
uint16_t point_val_2 = 200;
uint16_t point_val_3 = 500;

//Game Variables
uint8_t end_game = 0;
uint16_t score = 0;
uint16_t game_time = 0;
uint16_t game_state = 0;
uint16_t multiplier = 1;

//Sensor Flags
uint8_t sensor1_flag = 0;
uint8_t sensor2_flag = 0;
uint8_t sensor3_flag = 0;
uint8_t sensor4_flag = 0;
uint8_t sensor8_flag = 0;
uint8_t sensor9_flag = 0;
uint8_t sensor10_flag = 0;

void chase_led(){
	uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;

	*led_register <<= 1;
	if (*led_register == 0) {
		*led_register = 1;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == sensor1_Pin){
		sensor1_flag = 1;
	} else if (GPIO_Pin == sensor2_Pin){
		sensor2_flag = 1;
	} else if(GPIO_Pin == sensor3_Pin){
		sensor3_flag = 1;
	} else if(GPIO_Pin == sensor4_Pin){
		sensor4_flag = 1;
	} else if(GPIO_Pin == sensor8_Pin){
		sensor8_flag = 1;
	} else if(GPIO_Pin == sensor9_Pin){
		sensor9_flag = 1;
	} else if(GPIO_Pin == sensor10_Pin){
		sensor10_flag = 1;
	}
}

void multiplier_reset(void){
	multiplier = 1;
}

void game_over(void){
	end_game = 1;
}


int main(void)
{
	//Run required setup functions.
	HAL_setup();
	enable_clocks();
	enable_interrupts();
	initialise_board();

	//Pre-game Loop.
	while (game_state == 0){
		if (sensor2_flag == 1){
			game_state = 1;
			//chase_led();
			//multi_timer(&chase_led, 10000);


			game_timer(&game_over, 10000); //Set in seconds.
			sensor2_flag = 0;
		}
	}

	//Game Loop
	/*
		Sensor flags can quite easily be swapped around if pins are needed free for other functions.
			Currently used pins:
			-PA1	- Multiplier
			-PA2	- Start Game Button
			-PA8	- Points
			-PA9	- Points
			-PA10	- Points

			Unused pins but activated pins:
			-PA3
			-PA4
	*/
	while (game_state == 1){

		//Multipliers
		if (sensor1_flag == 1){
			multiplier = 2;
			multi_timer(&multiplier_reset, mult_2_duration);
			sensor1_flag = 0;
		}


		//Score Handling
		//Sensor8 (PA8) handles sensors that score 100 points.
		if (sensor8_flag == 1){
			score += point_val_1 * multiplier;
			sensor8_flag = 0;
		}
		//Sensor9 (PA9) handles sensors that score 200 points.
		if (sensor9_flag == 1){
			score += point_val_2 * multiplier;
			sensor9_flag = 0;
		}
		//Sensor10 (PA10) handles sensors that score 500 points.
		if (sensor10_flag == 1){
			score += point_val_3 * multiplier;
			sensor10_flag = 0;
		}


		//Transmit Score (& Game time? & Current multiplier?)
		game_time = get_game_time();

		/*
		UART Implementation
		Variables that could be sent:
		- current score: 		(uint16_t) score
		- current multiplier:   (uint16_t) multiplier
		- current game time:    (uint16_t) game_time
		*/


		//Game ends via time out
		if (end_game == 1){
			chase_led();
			game_state = 0;
		}

	}



}



