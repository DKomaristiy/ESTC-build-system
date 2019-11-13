#include "main.h"
#include "init.c"

void TIM2_IRQHandler(void);
static int8_t leds_counter;
static int8_t leds_direction;



void TIM2_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
   {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

      GPIO_SetBits(GPIOA, GPIO_Pin_8 << leds_counter);
      leds_counter = (3 + (leds_counter - leds_direction) % 3) % 3;
      GPIO_ResetBits(GPIOA, GPIO_Pin_8 << leds_counter);
   }
}

int main(void)
{
   //__enable_irq;
   //NVIC_EnableIRQ(TIM2_IRQn);
   leds_counter = 0;
   leds_direction = 1;

   SetSysClockTo84();
   configure_leds();
   configure_timers();

   for (;;)
   {
   }
}
