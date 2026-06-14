//----------------------------------------------------------------------------//
//          Mc32BattCtrl.c
//----------------------------------------------------------------------------//
// Description      :   Librairie pour la surveillance de l'accu Li-Po
//                      du projet 2517
//
// Auteur           :   Karol Stopa
// Date de création :   22.05.2026
// Compilateur      :   XC32 v5.10
//
// MODIFICATIONS    :
// KSA 22.05.2026       Création fichiers Mc32BattCtrl.c et .h
//
//----------------------------------------------------------------------------//

//------------------------------------------------//
// Inclusions des fichiers header
//------------------------------------------------//

#include "Mc32BattCtrl.h"
#include "peripheral/adc/plib_adc.h"
#include "../2517_CapteurQualiteAir.X/main.h"

//------------------------------------------------//
// Fonctions
//------------------------------------------------//

static inline void delay_us(uint32_t us)
{
    // À 24 MHz -> 1 instruction -> 41 ns
    // 1 us -> 24 instructions
    for(uint32_t i = 0; i < (us * CLK_MUC_MHZ); i++)
    {
        __asm__ volatile("nop");
    }
}


uint16_t batt_read_voltage(void)
{
    uint16_t adcRawValue;
    uint16_t voltage;       // Tension en [mV]
    
    // Lécture de la valeur sur l'ADC
    ADC_SamplingStart(); 
    delay_us(5);    // Attente obligatoire pour charge condo interne 
    ADC_ConversionStart();
    
    // Attendre la fin de conversion
    while(!ADC_ResultIsReady());
     
    adcRawValue = ADC_ResultGet(ADC_RESULT_BUFFER_0);
    
    // Conversion en tension de l'accu
    voltage = ((adcRawValue * MCU_V_POWER) / ADC_MAX_VALUE) * BAT_DIV_RATION;
    
    return voltage;
}


batt_level batt_check_level(uint16_t voltage)
{
    if (voltage >= BAT_FULL_LIM)
    {
        return BATT_FULL;
    }
    else if (voltage >= BAT_OK_LIM)
    {
        return BATT_OK;
    }
    else if (voltage >= BAT_LOW_LIM)
    {
        return BATT_LOW;
    }
    else if (voltage >= BAT_VAL_MIN)
    {
        return BATT_VERY_LOW;
    }
    else
    {
        return BATT_EMPTY;
    }
}


void batt_init(void)
{
    ADC_Initialize();
    ADC_Enable();
}