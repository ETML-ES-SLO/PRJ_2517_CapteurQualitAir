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

//------------------------------------------------//
// Fonctions
//------------------------------------------------//

uint16_t batt_read_voltage(void)
{
    uint32_t adcRawValue;
    uint16_t voltage;       // Tension en [mV]
    
    // Lécture de la valeur sur l'ADC
    adcRawValue = ADC_ResultGet(ADC_RESULT_BUFFER_2);
    
    // Conversion en tension de l'accu
    
    
    return voltage;
}