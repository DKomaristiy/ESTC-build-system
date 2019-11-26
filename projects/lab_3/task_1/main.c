#include "main.h"
#include "init.c"
#include <math.h>



void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);



void delay(uint32_t value)
{
  for (uint32_t i=0; i<value;i++)
  {
    __NOP();
  }

}



void EXTI0_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line0);

      TIM_SetCompare1(TIM1, (uint16_t)(10000 / PWM_FREQUENCY_HZ - 1) * 0.2f);
      TIM_SetCompare2(TIM1, (uint16_t)(10000 / PWM_FREQUENCY_HZ - 1) * 0.2f);
      TIM_SetCompare3(TIM1, (uint16_t)(10000 / PWM_FREQUENCY_HZ - 1) * 0.2f);


      

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
   configure_timers();
   configure_buttons_0();
   configure_pwm();
   configure_leds();
   start_timers();


   for (;;)
   {

   }
}
