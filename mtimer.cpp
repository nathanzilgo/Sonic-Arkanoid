#include <allegro.h>
#include <limits.h> // need this to know the max size of the counter...

#include "gerror.h" // error reporting
#include "mtimer.h"


// Globals, available for everybody that may need them
volatile int time_counter = 0; // first timer counter, counts in range from 0..BPS_OF_TIMER_MANAGER
volatile unsigned long int big_timer_counter = 0; // second timer, counts in range from 0..maximun int, and then auto resets
volatile int speed_counter = 0; // this speed counter is to keep the rate of drawing at constant fps
volatile int fps_counter = 0, fps_real = 0; // this is for counting FPS, will reset each second ; you SHOULD increase "fps_counter" on each redraw, to be able to count frames per second ; fps_real has the real FPS

// how many times we have installed / erased the timer handler?
// really, the timer gets installed only once, this only counts how many calls are made
// when reaches <= 0, the timer is uninstalled and the 2 counter resets to zero
// you should never touch this, is internal, and may mess stuff :P
static int timers_installed = 0;

// --------------------------------------------------------
// The timer routine
// --------------------------------------------------------
static void _timer_handler()
{
	time_counter++;
	big_timer_counter++;
	speed_counter++;

	if (time_counter > BPS_OF_TIMER_MANAGER)
	{
		time_counter = 0;
		fps_real = fps_counter; // take the real value
		fps_counter = 0; // a second passed, reset FPS count
	}

	if (big_timer_counter > ULONG_MAX - 2 )
		big_timer_counter = 0;
}
END_OF_FUNCTION(_timer_handler);

// --------------------------------------------------------
// This starts the global timer
// --------------------------------------------------------
void _start_global_timer()
{
	if (timers_installed == 0)
	{
		// Install timer
		LOCK_VARIABLE(time_counter);
		LOCK_VARIABLE(big_timer_counter);
		LOCK_VARIABLE(speed_counter);
		LOCK_VARIABLE(fps_counter);
		LOCK_VARIABLE(fps_real);
		LOCK_FUNCTION((void *)_timer_handler);

		if (install_int_ex(_timer_handler, BPS_TO_TIMER(BPS_OF_TIMER_MANAGER)))
			raise_error("_start_global_timer():\nERROR: Can't install timer at %d bps\n", BPS_OF_TIMER_MANAGER);
	}

	timers_installed++;	 // this counts how many calls to this function were made
}


// --------------------------------------------------------
// This ends the global timer
// --------------------------------------------------------
void _stop_global_timer()
{
	if (timers_installed == 0)
		return ; // no timer installed

	timers_installed--;

	if (timers_installed <= 0)
	{
		// remove and reset the timer
		remove_int(_timer_handler);
		time_counter = 0;
		speed_counter = 0;
		big_timer_counter = 0;
		timers_installed = 0;
		fps_counter = 0;
		fps_real = 0;
	}
}
