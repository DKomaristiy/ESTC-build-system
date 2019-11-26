#ifndef MAIN_H__
#define MAIN_H__

#include <stm32f4xx.h>

/* PWM frequency */
#define PWM_FREQUENCY_50HZ      50
#define PWM_FREQUENCY_100HZ     100
#define PWM_FREQUENCY_20HZ      20

void configure_buttons_0(void);
void configure_buttons_1(void);
void SetSysClockTo84(void);
void configure_leds(void);
void configure_timers(uint16_t pwm_frequency);
void configure_timer_2(void);
void configure_interrupts(void);
void configure_pwm(uint16_t pwm_frequency);
void start_timers(void);



#endif
