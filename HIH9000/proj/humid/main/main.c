#include "i2c.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"
#include "string.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "humidity_sensor.h"
#include "misc.h"

int main(void)
{
    config_I2C();

    //Delay timer config
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_TimeBaseStructInit(&TIM_InitStructure);

    TIM_InitStructure.TIM_Prescaler = 16800;
    TIM_InitStructure.TIM_Period = 0xFFFFF;
    TIM_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);



    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
    //TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    uint16_t humidity=0;
    while(1){

       humidity = get_humidity();
       //delay
       for(int i=0; i<100000;i++);
    }

}

