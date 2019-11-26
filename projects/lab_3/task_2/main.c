#include "main.h"
#include "init.c"
#include <math.h>



int set_color(float red, float green, float blue);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);


void delay(uint32_t value)
{
  for (uint32_t i=0; i<value;i++)
  {
    __NOP();
  }

}

int set_color(float red, float green, float blue)
{
    uint32_t pulse = (uint16_t)(10000 / PWM_FREQUENCY_HZ-1) ;

    TIM_SetCompare1(TIM1, pulse * red);
    TIM_SetCompare2(TIM1, pulse * green);
    TIM_SetCompare3(TIM1, pulse * blue);

    return 0;
}

int led = 1;

void EXTI0_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line0);

      switch (led)
      {
      case 1:
        set_color(0.2f,0,0);
         break;
      case 2:
         set_color(0,0.2f,0);
         break;
      case 3:
         set_color(0,0,0.2f);
         break;
      }       
 	
      led = led + 1;
      if (led == 4 )
         led = 1;
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
