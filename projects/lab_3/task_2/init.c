#include "main.h"


void configure_leds(void)
{
    GPIO_InitTypeDef gpio_init;
    GPIO_StructInit(&gpio_init);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);

    /* Initialize GPIOs for an alternative function (TIM1 PWM output) */
    gpio_init.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &gpio_init);
}

void configure_timers(void)
{
    /* Timer */
    TIM_TimeBaseInitTypeDef tim_init;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseStructInit(&tim_init);
    tim_init.TIM_Prescaler         = 840;
    tim_init.TIM_CounterMode       = TIM_CounterMode_Up;
    tim_init.TIM_Period            = (uint16_t)(100000 / PWM_FREQUENCY_HZ - 1); // if set only 10000 will turn 1 second
    tim_init.TIM_ClockDivision     = TIM_CKD_DIV1;
    tim_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &tim_init);


}


void configure_pwm(void)
{
    TIM_OCInitTypeDef tim_oc_init;

    TIM_OCStructInit(&tim_oc_init);

    tim_oc_init.TIM_OCMode      = TIM_OCMode_PWM1;
    tim_oc_init.TIM_Pulse       = (uint16_t)(100000 / PWM_FREQUENCY_HZ - 1) ;
    tim_oc_init.TIM_OutputState = TIM_OutputState_Enable;
    tim_oc_init.TIM_OCPolarity  = TIM_OCPolarity_Low;

    TIM_OC1Init(TIM1, &tim_oc_init);
    TIM_OC2Init(TIM1, &tim_oc_init);
    TIM_OC3Init(TIM1, &tim_oc_init);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void start_timers(void)
{
    TIM_Cmd(TIM1, ENABLE);
}

void configure_buttons_0()
{
   GPIO_InitTypeDef buttons_init_structure;
   NVIC_InitTypeDef buttons_nvic_init_structure = { 0x0 };
   EXTI_InitTypeDef buttons_exti_init_structure;

   /* Enable clocking for Buttons */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
   /* Init pins */
   buttons_init_structure.GPIO_Pin   = GPIO_Pin_0 ;
   /* Set mode to input */
   GPIO_StructInit(&buttons_init_structure);
   buttons_init_structure.GPIO_Mode  = GPIO_Mode_IN;
   buttons_init_structure.GPIO_Speed = GPIO_Speed_2MHz;
   buttons_init_structure.GPIO_OType = GPIO_OType_PP;
   buttons_init_structure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_Init(GPIOE, &buttons_init_structure);

   /* Configure button interrupts (only left button)*/
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
   /* Connect EXTI Line0 to PE0 pin */
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);

   /* Configure EXTI Line0 */
   EXTI_StructInit(&buttons_exti_init_structure);
   buttons_exti_init_structure.EXTI_Line    = EXTI_Line0;
   buttons_exti_init_structure.EXTI_Mode    = EXTI_Mode_Interrupt;
   buttons_exti_init_structure.EXTI_Trigger = EXTI_Trigger_Rising;
   buttons_exti_init_structure.EXTI_LineCmd = ENABLE;
   EXTI_Init(&buttons_exti_init_structure);

   /* Set interrupts to NVIC */
   buttons_nvic_init_structure.NVIC_IRQChannel = EXTI0_IRQn;
   buttons_nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 0x01;
   buttons_nvic_init_structure.NVIC_IRQChannelSubPriority = 0x01;
   buttons_nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&buttons_nvic_init_structure);
}

void configure_buttons_1(void)
{
   GPIO_InitTypeDef buttons_init_structure;
   NVIC_InitTypeDef buttons_nvic_init_structure = { 0x0 };
   EXTI_InitTypeDef buttons_exti_init_structure;

   /* Enable clocking for Buttons */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
   /* Init pins */
   buttons_init_structure.GPIO_Pin   =  GPIO_Pin_1;
   /* Set mode to input */
   GPIO_StructInit(&buttons_init_structure);
   buttons_init_structure.GPIO_Mode  = GPIO_Mode_IN;
   buttons_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
   buttons_init_structure.GPIO_OType = GPIO_OType_PP;
   buttons_init_structure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_Init(GPIOE, &buttons_init_structure);

   /* Configure button interrupts */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* Connect EXTI Line1 to PE1 pin */
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);

   /* Configure EXTI Line0 and  Line1  */
   EXTI_StructInit(&buttons_exti_init_structure);
   buttons_exti_init_structure.EXTI_Line    = EXTI_Line1;
   buttons_exti_init_structure.EXTI_Mode    = EXTI_Mode_Interrupt;
   buttons_exti_init_structure.EXTI_Trigger = EXTI_Trigger_Rising;
   buttons_exti_init_structure.EXTI_LineCmd = ENABLE;
   EXTI_Init(&buttons_exti_init_structure);


   /* Set interrupts to NVIC */
   buttons_nvic_init_structure.NVIC_IRQChannel = EXTI1_IRQn;
   buttons_nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 0x01;
   buttons_nvic_init_structure.NVIC_IRQChannelSubPriority = 0x01;
   buttons_nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&buttons_nvic_init_structure);
}

void SetSysClockTo84(void)
{
  int HSEStartUpStatus;
  RCC_DeInit();
  /* Enable HSE */
  RCC_HSEConfig( RCC_HSE_ON);


  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {

     RCC_PLLConfig(RCC_PLLSource_HSE,8,336,4,4);

     RCC_PLLCmd( ENABLE);

        /* Wait till PLL is ready */
     while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
     {
     }

     /* Select PLL as system clock source */
     RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);

     /* Wait till PLL is used as system clock source */
     while (RCC_GetSYSCLKSource() != 0x08)
     {
     }

  }
}

