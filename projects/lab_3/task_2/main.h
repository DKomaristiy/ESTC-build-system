#ifndef MAIN_H__
#define MAIN_H__

#include <stm32f4xx.h>

/* PWM frequency */
#define PWM_FREQUENCY_HZ      50

void configure_buttons_0(void);
void configure_buttons_1(void);
void SetSysClockTo84(void);
void configure_leds(void);
void configure_timers(void);
void configure_interrupts(void);
void configure_pwm(void);
void start_timers(void);



#endif
