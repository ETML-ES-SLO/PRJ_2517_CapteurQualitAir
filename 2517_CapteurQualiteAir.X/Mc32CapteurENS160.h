//----------------------------------------------------------------------------//
//          Mc32CapteurENS160.h
//----------------------------------------------------------------------------//
// Description      :   Librairie pour capteur qualite d'air ENS160
//
// Auteur           :   Karol Stopa
// Date de création :   22.05.2026
// Compilateur      :   XC32 v5.10
//
// MODIFICATIONS    :
// KSA 22.05.2026       Création fichiers Mc32CapteurENS160.c et .h
//
// documetation : 2517_CapteurQualiteAir/doc/datasheets/ENS160-Datasheet.pdf
//----------------------------------------------------------------------------//

#ifndef _MC32CAPTEURENS160_H
#define _MC32CAPTEURENS160_H

//------------------------------------------------//
// Inclusion librairies
//------------------------------------------------//
#include <stdint.h>
#include <stdbool.h>

#define SELECT_2517_CAPTEUR_QUALITE_AIR_PIC32MM

//------------------------------------------------//
// Addresses I2C ENS160 (page 5 datasheet)
//------------------------------------------------//

#define ENS160_ADDR_I2C_PIN_LOW     0x52
#define ENS160_ADDR_I2C_PIN_HIGH    0x53

//------------------------------------------------//
// Addresses ENS160
//------------------------------------------------//

#define PART_ID         0x00
#define OPMODE          0x10
#define CONFIG          0x11
#define COMMAND         0x12
#define TEMP_IN         0x13
#define RH_IN           0x15
#define DEVICE_STATUS   0x20
#define DATA_AQI        0x21
#define DATA_TVOC       0x22
#define DATA_ECO2       0x24
#define DATA_T          0x30
#define DATA_RH         0x32
#define DATA_MISR       0x38
#define GPR_WRITE       0x40
#define GPR_READ        0x48

//------------------------------------------------//
// Mask DEVICE_STATUS (page 30 datasheet)
//------------------------------------------------//

#define MASK_DEVICE_STATUS_STATAS           0b10000000
#define MASK_DEVICE_STATUS_STATER           0b01000000
#define MASK_DEVICE_STATUS_VALIDITY_FLAG    0b00001100
#define MASK_DEVICE_STATUS_NEWDAT           0b00000010
#define MASK_DEVICE_STATUS_NEWGPR           0b00000001

//------------------------------------------------//
// Mask DATA_AQI (page 30 datasheet)
//------------------------------------------------//

#define MASK_DATA_AQI_UBA       0b00000111
#define MASK_DATA_AQI_RESERVED  0b11111000

//------------------------------------------------//
// Macros
//------------------------------------------------//

#ifdef SELECT_2517_CAPTEUR_QUALITE_AIR_PIC32MM 

// Chip select pour SPI
#define CS_LOW          LATAbits.LATA0 = 0
#define CS_HIGH         LATAbits.LATA0 = 1

// Chip graphique
#define PD_LOW          LATAbits.LATA1 = 0  // Désactive chip graph.
#define PD_HIGH         LATAbits.LATA1 = 1  // Active chip graphique

#endif 

//------------------------------------------------//
// Enumerations
//------------------------------------------------//

// Status (mode de fonctionnement) du capteur ENS160
typedef enum {
    OPERATING_OK,
            WARM_UP,
            INITIAL_START_UP,
            NO_VALID_OUTPUT,
            UNKNOWN_STATUS
} ens160_status;

// AQI-UBA (Air Quality Index of the "UBA" German Federal Environmental Agency)
typedef enum
{
    EXCELLENT,
            GOOD,
            MODERATE,
            POOR,
            UNHEALTHY,
            UNKNOWN_AQI
} ens160_aqi_uba;

//------------------------------------------------//
// Définition des prototypes de fonctions
//------------------------------------------------//

//----------------------------------------------------------------------------------//
//-- nom fct : ens160_read_aqi
//-- paramètre entrée : -
//-- paramètre sortie : Index de qualité d'air (enum ens160_aqi_uba)
//-- paramètre référence (IN-OUT) :   - 
//-- description : Lécture de l'index de qualité d'air sur le capteur ENS160
//-- démonstration : - 
//-- aide - référence - lien : ENS160-Datasheet.pdf page.11
//----------------------------------------------------------------------------------//
ens160_status ens160_read_status(void);

//----------------------------------------------------------------------------------//
//-- nom fct : ens160_read_status
//-- paramètre entrée : -
//-- paramètre sortie : status du capteur (enum ens160_status)
//-- paramètre référence (IN-OUT) :   - 
//-- description : Lécture du status du capteur ENS160
//-- démonstration : - 
//-- aide - référence - lien : ENS160-Datasheet.pdf page.16
//----------------------------------------------------------------------------------//
ens160_aqi_uba ens160_read_aqi(void);

//----------------------------------------------------------------------------------//
//-- nom fct : ens160_init
//-- paramètre entrée : -
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) :   - 
//-- description : Initialisation du capteur ENS160 
//-- démonstration : - 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
void ens160_init(void);

#endif