#ifndef TIMER_HEADER
#define TIMER_HEADER
/**
 * Header file for all timer related code
 */

//Flags
uint_8 end_game;
uint_8 multiplier;


//Enables RCC clocks for timer and LEDs.
void enable_clocks();

//Sets up TIM2 interrupt priority and functionality.
void enable_interrupts();

//Gets pointer to LED control memory and sets LEDs to 0.
void initialise_board();

//Sets prescaler for TIM2. Takes input as integer.
void trigger_prescaler(int prescaler);

//Sets callback function. (Inputs: pointer to function, duration (number of ticks at prescaler value), and prescaler value).
void trigger_callback(void (*func_ptr)(), int duration, int prescaler);

//Pushes an update flag to reset TIM2 before clearing flag.
void start_timer();

//Sets new period (duration) for TIM2.
void set_period(int duration);

//Retrieves current period (duration) for TIM2.
int get_period();

//Runs one time callback function on TIM3. (Inputs: pointer to function, and duration (number of ticks at prescaler value)).
void multi_timer(void (*func_ptr)(), int duration);

//Runs game duration timer on TIM2. (Inputs: pointer to function, game duration in seconds)
void game_timer(void (*func_ptr)(), int duration);

//Runs scoring timer on TIM4 (Inputs: pointer to function, and delay between score updates)
void score_timer(void (*func_ptr)(), int duration);


#endif
