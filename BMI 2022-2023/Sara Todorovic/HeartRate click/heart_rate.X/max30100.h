/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAX30100_H
#define	MAX30100_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

// Slave adresa MAX30100: 
#define MAX30100_SLAVE_ADDR 0x57

// Adrese registara:
#define MAX30100_INT_STATUS 0x00
#define MAX30100_INT_ENABLE 0x01
#define MAX30100_FIFO_WR_PTR 0x02
#define MAX30100_FIFO_OVERFLOW_CNT 0x03
#define MAX30100_FIFO_RD_PTR 0x04
#define MAX30100_FIFO_DATA 0x05
#define MAX30100_MODE_CFG 0x06
#define MAX30100_SPO2_CFG 0x07
#define MAX30100_LED_CFG 0x09
#define MAX30100_TEMP_INTEGER 0x16
#define MAX30100_TEMP_FRACTION 0x17
#define MAX30100_REVISION_ID 0xFE
#define MAX30100_PART_ID 0xFF

// Vrednost koju je potrebno upisati u Mode Configuration registar kako bi se MAX30100 resetovao:
#define MAX30100_RESET 0x40
    
// Moguce vrednosti koje je potrebno upisati u Mode Configuration na mesta B2:B0 registar kako bi se podesio mod rada:
typedef enum {
    MAX30100_MODE_HR_ONLY                 = 0x02,
    MAX30100_MODE_SPO2_HR                 = 0x03
}MAX30100_MODE_t;

// Moguce vrednosti koje je potrebno upisati u LED Configuration registar kako bi se podesila vrednost struje kroz diode:
typedef enum{
    MAX30100_LED_CURRENT_0mA              = 0x00,
    MAX30100_LED_CURRENT_4_4mA            = 0x01,
    MAX30100_LED_CURRENT_7_6mA            = 0x02,
    MAX30100_LED_CURRENT_11mA             = 0x03,
    MAX30100_LED_CURRENT_14_2mA           = 0x04,
    MAX30100_LED_CURRENT_17_4mA           = 0x05,
    MAX30100_LED_CURRENT_20_8mA           = 0x06,
    MAX30100_LED_CURRENT_24mA             = 0x07,
    MAX30100_LED_CURRENT_27_1mA           = 0x08,
    MAX30100_LED_CURRENT_30_6mA           = 0x09,
    MAX30100_LED_CURRENT_33_8mA           = 0x0A,
    MAX30100_LED_CURRENT_37mA             = 0x0B,
    MAX30100_LED_CURRENT_40_2mA           = 0x0C,
    MAX30100_LED_CURRENT_43_6mA           = 0x0D,
    MAX30100_LED_CURRENT_46_8mA           = 0x0E,
    MAX30100_LED_CURRENT_50mA             = 0x0F
}MAX30100_LED_CURRENT_t;

// Moguce vrednosti koje je potrebno upisati u SpO2 Configuration registar na mesta B4:B2 kako bi se podesila frekvencija odabiranja:
typedef enum{
    MAX30100_SAMPLING_RATE_50Hz           = 0x00,
    MAX30100_SAMPLING_RATE_100Hz          = 0x01,
    MAX30100_SAMPLING_RATE_167Hz          = 0x02,
    MAX30100_SAMPLING_RATE_200Hz          = 0x03,
    MAX30100_SAMPLING_RATE_400Hz          = 0x04,
    MAX30100_SAMPLING_RATE_600Hz          = 0x05,
    MAX30100_SAMPLING_RATE_800Hz          = 0x06,
    MAX30100_SAMPLING_RATE_1000Hz         = 0x07
}MAX30100_SAMPLE_RATE_t;

// Moguce vrednosti koje je potrebno upisati u SpO2 Configuration registar na mesta B1:B0 kako bi se podesila sirina impulsa koji se dovode na diode:
typedef enum{
    MAX30100_PULSE_WIDTH_200uS_ADC_13     = 0x00,
    MAX30100_PULSE_WIDTH_400uS_ADC_14     = 0x01,
    MAX30100_PULSE_WIDTH_800uS_ADC_15     = 0x02,
    MAX30100_PULSE_WIDTH_1600uS_ADC_16    = 0x03,
}MAX30100_LED_PULSE_WIDTH_t;

// Struktura na kojoj se cuvaju podaci ocitani sa MAX30100 senzora:
typedef struct{
    uint16_t ir_led;
    uint16_t red_led;
    
    float temperature;
}MAX30100_sens_t;  

// Funkcije za rad sa MAX30100:
uint8_t MAX30100_get_device_ID();

void MAX30100_init(MAX30100_MODE_t mode, MAX30100_LED_CURRENT_t red_led_current, MAX30100_LED_CURRENT_t ir_led_current, MAX30100_SAMPLE_RATE_t sample_rate, MAX30100_LED_PULSE_WIDTH_t pulse_width);

void MAX30100_FIFO_init();

void MAX30100_read_led_data(MAX30100_sens_t* sens);

void MAX30100_reset();

void MAX30100_enable_temp_read();

void MAX30100_read_temp_data(MAX30100_sens_t* sens);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

