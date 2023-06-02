/*
 * File:   max30100.c
 * Author: Sanja
 *
 * Created on June 1, 2023, 4:34 PM
 */


#include <xc.h>
#include "max30100.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"


// Citanje podatka o ID cipa iz Part ID registra:
uint8_t MAX30100_get_device_ID()
{
    return I2C1_Read1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_PART_ID);
}


void MAX30100_init(MAX30100_MODE_t mode, MAX30100_LED_CURRENT_t red_led_current, MAX30100_LED_CURRENT_t ir_led_current, MAX30100_SAMPLE_RATE_t sample_rate, MAX30100_LED_PULSE_WIDTH_t pulse_width){
    uint8_t i_data;
    uint8_t spo2_data;
    
    // Podesavanje moda rada:
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_MODE_CFG, mode);                    
                                              
    // Podesavanje struje za RED i IR LED: 
    i_data = (uint8_t)((red_led_current<<4)|ir_led_current);
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_LED_CFG, i_data);

    // Podesavanje sirine impulsa i sample rata-a:
    spo2_data = (uint8_t)((sample_rate<<2)|pulse_width);
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_SPO2_CFG, spo2_data);
}

void MAX30100_FIFO_init(){
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_FIFO_WR_PTR, 0x00);
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_FIFO_OVERFLOW_CNT, 0x00);
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_FIFO_RD_PTR, 0x00);
}

void MAX30100_read_led_data(MAX30100_sens_t* sens){
    static uint8_t tmp_reg[4];

    I2C1_ReadDataBlock(MAX30100_SLAVE_ADDR, MAX30100_FIFO_DATA, tmp_reg, 4);
    
    sens->ir_led = (uint16_t)(tmp_reg[0]<<8|tmp_reg[1]);     
    sens->red_led = (uint16_t)(tmp_reg[2]<<8|tmp_reg[3]);
}

void MAX30100_reset(){
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_MODE_CFG, MAX30100_RESET);
}

void MAX30100_enable_temp_read(){
    static uint8_t mode_cfg_reg;
    
    mode_cfg_reg = I2C1_Read1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_MODE_CFG);     
    mode_cfg_reg = mode_cfg_reg|0x08;
    I2C1_Write1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_MODE_CFG, mode_cfg_reg);
}
void MAX30100_read_temp_data(MAX30100_sens_t* sens){
    static uint8_t temp_int1;
    static int8_t temp_int2;
    static uint8_t temp_frac;

    temp_int1 = I2C1_Read1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_TEMP_INTEGER);
    temp_int2 = (int8_t)temp_int1;                                             
    
    temp_frac = I2C1_Read1ByteRegister(MAX30100_SLAVE_ADDR, MAX30100_TEMP_FRACTION);

    sens->temperature = (float)(temp_int2+temp_frac*0.0625);
}
/* *****************************************************************************
 End of File
 */
