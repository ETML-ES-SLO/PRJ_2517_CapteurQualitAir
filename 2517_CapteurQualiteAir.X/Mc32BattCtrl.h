//----------------------------------------------------------------------------//
//          Mc32BattCtrl.h
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
// documetation : lien datasheet 
//----------------------------------------------------------------------------//

#ifndef _MC32BATTCTRL_H
#define _MC32BATTCTRL_H

//------------------------------------------------//
// Inclusion librairies
//------------------------------------------------//
#include <stdint.h>
#include <stdbool.h>

//------------------------------------------------//
// Sélection modèle de MCP73831 monté sur la carte
//------------------------------------------------//
#define SELECT_2517_MCP73831_2AD

//------------------------------------------------//
// Param MCU pour délais
//------------------------------------------------//
#define CLK_MUC_MHZ 24

//------------------------------------------------//
// Pour calcul tension accu
//------------------------------------------------//
#define ADC_MAX_VALUE   4095 // Valeur max de l'ADC
#define MCU_V_POWER     3000 // Tension d'alim MCU en [mV]
#define BAT_DIV_RATION  2    // Ratio de division de la tension de l'accu avant mesure ADC
        
//------------------------------------------------//
// Limites accu lookup table
//------------------------------------------------//
#define BAT_VAL_MAX         4200
#define BAT_VAL_MIN         3500

#ifdef SELECT_2517_MCP73831_2AD 
// MCP73831 version D (96.5%)
#define BAT_THRESHOLD_VAL   (BAT_VAL_MAX * 0.965)
#endif 

#ifdef SELECT_2517_MCP73831_2AC 
// MCP73831 version C (94%)
#define BAT_THRESHOLD_VAL   (BAT_VAL_MAX * 0.94)
#endif 

//------------------------------------------------//
// Macros
//------------------------------------------------//


//------------------------------------------------//
// Définition des prototypes de fonctions
//------------------------------------------------//

//----------------------------------------------------------------------------------//
//-- nom fct : delay_us 
//-- paramètre entrée : us (temp d'attente en us)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) :   - 
//-- description : Fonction de delais en us 
//-- démonstration : À 24 MHz ? 1 instruction ? 41 ns, 1 µs ? 24 instructions 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
static inline void delay_us(uint32_t us);

//----------------------------------------------------------------------------------//
//-- nom fct : batt_read_voltage 
//-- paramètre entrée : -
//-- paramètre sortie : valeur de tension de l'accu en mV
//-- paramètre référence (IN-OUT) :   - 
//-- description : Lecture de la tension de l'accu.
//-- démonstration : Ex. ADC = 2000 | ((2000 * 3000) / 4095) * 2 = 2.93V sur l'accu
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
uint16_t batt_read_voltage(void);
        
#endif

