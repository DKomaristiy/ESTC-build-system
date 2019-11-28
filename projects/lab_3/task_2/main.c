#include "main.h"
#include "init.c"
#include <math.h>


int set_color(uint8_t red, uint8_t green, uint8_t blue);
//int set_color(float red, float green, float blue);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);


void delay(uint32_t value)
{
  for (uint32_t i=0; i<value;i++)
  {
    __NOP();
  }

}


int set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t pulse = (uint16_t)(10000 / PWM_FREQUENCY_HZ-1) /255 ;

    TIM_SetCompare1(TIM1, pulse * red);
    TIM_SetCompare2(TIM1, pulse * green);
    TIM_SetCompare3(TIM1, pulse * blue);

    return 0;
}

/*
int set_color(float red, float green, float blue)
{
    uint32_t pulse = (uint16_t)(10000 / PWM_FREQUENCY_HZ-1) ;

    TIM_SetCompare1(TIM1, pulse * red);
    TIM_SetCompare2(TIM1, pulse * green);
    TIM_SetCompare3(TIM1, pulse * blue);

    return 0;
}*/

int led = 1;
int counter = 0;
int state;

void EXTI0_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line0);
      

      state = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);

      if (state)
         counter++;

      if (counter > 2)
      {
         switch (led)
         {
         case 1:
            set_color(198,5,248);
            break;
         case 2:
            set_color(255,245,0);
            break;
         case 3:
            set_color(141,174,240);
            break;
         }
         /* switch (led)
      {
      case 1:
        set_color(0.9f,0,0.9f);
         break;
      case 2:
         set_color(0.9f,0.9f,0);
         break;
      case 3:
         set_color(0,0.9f,0.9f);
         break;
      }
 */
         led = led + 1;
         if (led == 4 )
            led = 1;

         counter = 0;
      }
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
