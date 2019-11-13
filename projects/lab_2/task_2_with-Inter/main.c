#include "main.h"
#include "init.c"



void TIM2_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
   {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

      GPIO_ToggleBits(GPIOA, GPIO_Pin_8);
   }
}

int main(void)
{
   SetSysClockTo84();
   configure_leds();
   configure_timers();

   for (;;)
   {
   }
}
