#include <stdint.h>
#include "stm32f303xc.h"
#include "timers.h"

//Flags

void enable_clocks(){

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

}

void initialise_board(){

	// get a pointer to the second half word of the MODER register (for outputs pe8-15)
	uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
	*led_output_registers = 0x5555;
}

void enable_interrupts(){
	//disable interrupts while setting interrupts
	__disable_irq();

	TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
	TIM2->EGR = TIM_EGR_UG;
	TIM2->SR &= ~TIM_SR_UIF;
	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM2_IRQn, 2);
	NVIC_ClearPendingIRQ(TIM2_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn);

	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
	TIM3->EGR = TIM_EGR_UG;
	TIM3->SR &= ~TIM_SR_UIF;
	TIM3->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM3_IRQn, 1);
	NVIC_ClearPendingIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);


	//re-enable interrupts.
	__enable_irq();

}

void start_timer(){

	TIM2->EGR = TIM_EGR_UG;
	TIM2->SR &= ~TIM_SR_UIF;

}

void (*on_TIM2_reset)() = 0x00;

void (*on_TIM3_reset)() = 0x00;

void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;

	if (on_TIM2_reset != 0x00){
		on_TIM2_reset();
		TIM2->CNT = 0x00;
		TIM2->CR1 = 0;
	}
}

void TIM3_IRQHandler(void){
	TIM3->SR &= ~TIM_SR_UIF;

	if (on_TIM3_reset != 0x00){
		on_TIM3_reset();
		TIM3->CNT = 0x00;
		TIM3->CR1 = 0;
	}
}

int get_game_time(){
	return TIM2->CNT;
}

/*
void game_timer(void (*func_ptr)(), int duration){
	TIM3->ARR = duration;
	TIM3->CR1 |= TIM_CR1_CEN;

	TIM2->PSC = 0x1F40 - 1;
	//TIM3->PSC = 8000000;
	TIM3->EGR = TIM_EGR_UG;

	on_TIM3_reset = func_ptr;
	//TIM3->EGR = TIM_EGR_UG;
	//TIM3->SR &= ~TIM_SR_UIF;
	TIM3->CNT = 0x00;

}
*/

void game_timer(void (*func_ptr)(), int duration){
	TIM2->ARR = duration;
	TIM2->CR1 |= TIM_CR1_CEN;

	TIM2->PSC = 0x1F40 - 1;
	TIM2->EGR = TIM_EGR_UG;

	on_TIM2_reset = func_ptr;
	TIM2->CNT = 0x00;
}



/*
void trigger_prescaler(int prescaler){

	TIM2->PSC = prescaler;
	TIM2->EGR = TIM_EGR_UG;

}

void set_period(int duration){
	TIM2->ARR = duration;
	TIM2->EGR = TIM_EGR_UG;
}

int get_period(){
	return TIM2->ARR;
}

void trigger_callback(void (*func_ptr)(), int duration, int prescaler){
	TIM2->ARR = duration;
	TIM2->CR1 |= TIM_CR1_CEN;

	trigger_prescaler(prescaler - 1);

	on_TIM2_reset = func_ptr;
	TIM2->CNT = 0x00;
}
*/
