//----------------------------------------------------------------------------//
//          Mc32CapteurENS160.c
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
//----------------------------------------------------------------------------//

//------------------------------------------------//
// Inclusions des fichiers header
//------------------------------------------------//

#include "Mc32CapteurENS160.h"
#include "peripheral/i2c/master/plib_i2c3_master.h"

//------------------------------------------------//
// Fonctions
//------------------------------------------------//

void ens160_initial_start_up(void)
{
    
}

void ens160_warm_up(void)
{
    
}

uint8_t ens160_read8(uint8_t addr)
{
    uint8_t data;
    
    // Lécture un octet
    I2C3_WriteRead(ENS160_ADDR_I2C_PIN_LOW, &addr, 1, &data, 1);
    
    // Attend fin transfert
    while (I2C3_IsBusy());
    
    return data;
}

uint16_t ens160_read16(uint8_t addr)
{
    uint8_t buf[2];
    uint16_t data;
    
    // Lécture un octet
    I2C3_WriteRead(ENS160_ADDR_I2C_PIN_LOW, &addr, 1, &buf[0], sizeof(buf));
    
    // Attend fin transfert
    while (I2C3_IsBusy());
    
    // Met les datas dans une variable 16 bits
    data = ((uint16_t)buf[0] << 8) | buf[1];
    return data;
}

ens160_status ens160_read_status(void)
{
    uint8_t rawStatus;
    rawStatus = ens160_read8(DEVICE_STATUS);
    
    // Lécture de status sur des val. de 0 à 3.
    // Décalage de bits 2,3 à bits 0,1
    switch((rawStatus & MASK_DEVICE_STATUS_VALIDITY_FLAG) >> 2)
    {
        case 0: // Operating OK
        {
            return OPERATING_OK;
            break;
        }
        case 1: // Warm-Up
        {
            return WARM_UP;
            break;
        }
        case 2: // Initial Start-Up
        {
            return INITIAL_START_UP;
            break;
        }
        case 3: // No valid output
        {
            return NO_VALID_OUTPUT;
            break;
        }
        default: // Lécture de status inconnue
        {
            return UNKNOWN_STATUS;
            break;
        }
    }
}

ens160_aqi_uba ens160_read_aqi(void)
{   
    uint8_t rawAqi;
    rawAqi = ens160_read8(DATA_AQI);
    
    // Lécture de status sur des val. de 1 à 5.
    switch(rawAqi & MASK_DATA_AQI_UBA)
    {
        case 1: // Excellent air quality
        {
            return EXCELLENT;
            break;
        }
        case 2: // Good air quality
        {
            return GOOD;
            break;
        }
        case 3: // Moderate air quality
        {
            return MODERATE;
            break;
        }
        case 4: // Poor air quality
        {
            return POOR;
            break;
        }
        case 5: // Unhealthy air quality
        {
            return UNHEALTHY;
            break;
        }
        default: // Lécture de qualité d'air inconnue
        {
            return UNKNOWN_AQI;
            break;
        }
    }
}

void ens160_init(void)
{
    switch(ens160_read_status())
    {
        case WARM_UP:
        {
            ens160_warm_up();
            break;
        }
        case INITIAL_START_UP:
        {
            ens160_initial_start_up();
            break;
        }
        default:
        {
            // Si aucun de ces deux status, continue init
            break;
        }
    }
}
