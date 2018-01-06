#include "humidity_sensor.h"
#include "i2c.h"
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "string.h"
#define HUMI_SENSOR_ADDR  0x4E
uint8_t i2c_dma_ready=0;
///
/// \brief Humidity_Start_Conv
/// Call it 37ms before gathering data
///
void humidity_start_conv(){
    I2C_humidity_measurement_request();
}

uint16_t get_humidity(){

    uint16_t humidity = 0;
    uint8_t intg = 0;
    uint8_t frac = 0;
    uint8_t humi_buff[2];

    humidity_start_conv();

    //Delay 37 ms
    TIM_SetCounter(TIM3,0);
    TIM_Cmd(TIM3, ENABLE);
    while(TIM_GetCounter(TIM3)<370);

    I2C_DMA_Read(HUMI_SENSOR_ADDR);
    while(i2c_dma_ready==0);
    i2c_dma_ready=0;
    memcpy(humi_buff, I2C_Rx_Buffer, 2);
    uint16_t humi_raw = ((humi_buff[0] & 0x3f)<<8) + humi_buff[1];

    float humi = ((float)humi_raw)/16382 * 100;

    intg = (uint8_t)humi;
    frac = (uint8_t)((humi-(float)intg)*100);
    humidity = intg<<8 | frac;
    return humidity;
}

