#ifndef MTIMER_H
#define MTIMER_H

/// how much we must beat by second (BPS)
#define BPS_OF_TIMER_MANAGER 60

extern volatile int time_counter; ///< first timer counter, counts in range from 0..BPS_OF_TIMER_MANAGER
extern volatile unsigned long int big_timer_counter; ///< second timer, counts in range from 0..maximun int
extern volatile int speed_counter; ///< this speed counter is to keep the rate of drawing at constant fps
/// this is for counting FPS, will reset each second ; you SHOULD increase "fps_counter" on each redraw, to be able to count frames per second
extern volatile int fps_counter, fps_real; 

void _start_global_timer(); ///< starts global timer
void _stop_global_timer();  ///< stops global timer

#endif
