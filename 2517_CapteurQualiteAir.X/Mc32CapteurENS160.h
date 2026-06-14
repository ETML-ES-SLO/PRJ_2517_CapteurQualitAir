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
// KSA 14.06.2025       Clôture dev. version 1 de la librairie
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

//------------------------------------------------//
// Configuration de la librairie
//------------------------------------------------//

#define SELECT_2517_ENS160_ADDR_HIGH

//------------------------------------------------//
// Addresses I2C ENS160 (page 5 datasheet)
//------------------------------------------------//

#define ENS160_ADDR_I2C_PIN_LOW     0x52 // Addr. sur PCB 2517 
#define ENS160_ADDR_I2C_PIN_HIGH    0x53 // Addr. sur ENS160 DFROBOT

#ifdef SELECT_2517_ENS160_ADDR_LOW
#define ENS160_ADDR_I2C ENS160_ADDR_I2C_PIN_LOW
#endif 

#ifdef SELECT_2517_ENS160_ADDR_HIGH
#define ENS160_ADDR_I2C ENS160_ADDR_I2C_PIN_HIGH
#endif 

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
// OPMODE states
//------------------------------------------------//

#define OPMODE_DEEP_SLEEP   0x00
#define OPMODE_IDLE         0x01
#define OPMODE_OPERATIONAL  0x02

//------------------------------------------------//
// Retour ENS160 standard
//------------------------------------------------//
#define PART_ID_RET     0x0160

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
    ERROR_NO_AQI,
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
//-- nom fct : delay_ms 
//-- paramètre entrée : ms (temp d'attente en ms)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) :   - 
//-- description : Fonction de delais en us 
//-- démonstration : À 24 MHz, 1 instruction = 41 ns, 1 ms = 24'000 instructions 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
static inline void delay_ms(uint32_t ms);

//----------------------------------------------------------------------------------//
//-- nom fct : ens160_read8
//-- paramètre entrée : Adresse mémoire à lire sur ens160
//-- paramètre sortie : valeur lue à l'adresse
//-- paramètre référence (IN-OUT) :   - 
//-- description : Lécture d'un registe 8 bits sur ens160
//-- démonstration : - 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
uint8_t ens160_read8(uint8_t addr);

//----------------------------------------------------------------------------------//
//-- nom fct : ens160_read16
//-- paramètre entrée : Adresse mémoire à lire sur ens160
//-- paramètre sortie : valeur lue à l'adresse
//-- paramètre référence (IN-OUT) :   - 
//-- description : Lécture d'un registe 16 bits sur ens160
//-- démonstration : - 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
uint16_t ens160_read16(uint8_t addr);

//----------------------------------------------------------------------------------//
//-- nom fct : ens160_write8
//-- paramètre entrée : addr (adresse du registre ens160) | data (valeur à écrire)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) :   - 
//-- description : Ecriture d'un registe 8 bits sur ens160
//-- démonstration : - 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
void ens160_write8(uint8_t addr, uint8_t data);

//----------------------------------------------------------------------------------//
//-- nom fct : ens160_write16
//-- paramètre entrée : addr (adresse du registre ens160) | data (valeur à écrire)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) :   - 
//-- description : Ecriture d'un registe 16 bits sur ens160
//-- démonstration : - 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
void ens160_write16(uint8_t addr, uint16_t data);

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
bool ens160_init(void);

#endif