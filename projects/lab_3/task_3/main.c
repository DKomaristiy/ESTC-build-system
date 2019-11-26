#include "main.h"
#include "init.c"
#include <math.h>




void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void TIM2_IRQHandler(void);


void delay(uint32_t value)
{
  for (uint32_t i=0; i<value;i++)
  {
    __NOP();
  }

}

int freq_option = 1;
uint32_t pwm_freq_hz = 20;
uint32_t time;

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        time++;
        uint16_t period1    = 2000;
        uint16_t period2    = 1500;
        uint16_t period3    = 2200;

        uint16_t pwm_value1 = (cos(time * 6.28 / period1) + 1) / 2.0f * (10000 / pwm_freq_hz - 1);
        uint16_t pwm_value2 = (cos(time * 6.28 / period2 + 3) + 1) / 2.0f * (10000 / pwm_freq_hz - 1);
        uint16_t pwm_value3 = (cos(time * 6.28 / period3 - 10) + 1) / 2.0f * (10000 / pwm_freq_hz - 1);

        TIM_SetCompare1(TIM1, pwm_value1);
        TIM_SetCompare2(TIM1, pwm_value2);
        TIM_SetCompare3(TIM1, pwm_value3);
    }
}




void EXTI0_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line0);

      switch (freq_option)
      {
      case 1:
         configure_timers(PWM_FREQUENCY_20HZ);
         configure_pwm(PWM_FREQUENCY_20HZ);
         pwm_freq_hz = PWM_FREQUENCY_20HZ;
         start_timers();
         break;
      case 2:
         configure_timers(PWM_FREQUENCY_50HZ);
         configure_pwm(PWM_FREQUENCY_50HZ);
         pwm_freq_hz = PWM_FREQUENCY_50HZ;
         start_timers();
         break;
      case 3:
         configure_timers(PWM_FREQUENCY_100HZ);
         configure_pwm(PWM_FREQUENCY_100HZ);
         pwm_freq_hz = PWM_FREQUENCY_100HZ;
         start_timers();
         break;
      }

      freq_option = freq_option + 1;
      if (freq_option == 4 )
         freq_option = 1;
   }
}

void EXTI1_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line1) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line1);

   }
}

int main(void)
{

   SetSysClockTo84();
   configure_timers(20);
   configure_timer_2();
   configure_buttons_0();
   configure_pwm(20);

   configure_leds();
   start_timers();


   for (;;)
   {

   }
}
