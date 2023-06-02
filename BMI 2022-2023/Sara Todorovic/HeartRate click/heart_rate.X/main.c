/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F87K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "max30100.h"
#include <math.h>

/*
                         Main application
 */
uint16_t srednja_vrednost(uint16_t *niz, uint8_t indeks)
{
    static uint32_t suma=0;
    uint8_t najstariji_indeks;

    if(indeks == 63)
        najstariji_indeks = 0;
    else
        najstariji_indeks = indeks+1;
    
    suma += niz[indeks];
    suma -= niz[najstariji_indeks];
    
    return (uint16_t)(suma>>6);
}

void main(void)
{
    uint8_t i=0;
    MAX30100_sens_t senzor;
    uint16_t red_niz[64]={0};
    uint16_t ir_niz[64]={0};
    uint16_t red_srednje=0;
    uint16_t ir_srednje=0;

    // Initialize the device
    SYSTEM_Initialize();
    
    MAX30100_init(MAX30100_MODE_SPO2_HR, MAX30100_LED_CURRENT_27_1mA, MAX30100_LED_CURRENT_50mA, MAX30100_SAMPLING_RATE_100Hz, MAX30100_PULSE_WIDTH_1600uS_ADC_16);
    MAX30100_FIFO_init();

    while (1)
    {
        MAX30100_read_led_data(&senzor); 
        red_niz[i] = senzor.red_led;
        ir_niz[i] = senzor.ir_led;
        
        red_srednje = srednja_vrednost(red_niz, i);
        ir_srednje = srednja_vrednost(ir_niz, i);
        
        EUSART1_Write(0x03);
        EUSART1_Write((uint8_t)senzor.ir_led);
        EUSART1_Write((uint8_t)(senzor.ir_led>>8));
        EUSART1_Write((uint8_t)senzor.red_led);
        EUSART1_Write((uint8_t)(senzor.red_led>>8));
        EUSART1_Write(0xFC);
        
        
        __delay_ms(10);
        i++;
        i = (i==64) ? 0:i;
    }
}
/**
 End of File
*/