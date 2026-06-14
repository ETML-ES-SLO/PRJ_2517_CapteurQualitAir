/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include "../2517_CapteurQualiteAir.X/main.h"
#include "../2517_CapteurQualiteAir.X/Mc32CapteurENS160.h"
#include "../2517_CapteurQualiteAir.X/Mc32BattCtrl.h"
#include "../2517_CapteurQualiteAir.X/Mc32ILI9163.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

// Structue de data gloables
MAIN_DATA mainData;

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    ens160_init();
    lcd_init();
    batt_init();
    
    // Variables
    uint16_t id;
    uint16_t voltage;
    ens160_status ens160Status;
    ens160_aqi_uba aqi;
    
    lcd_fill(LCD_BLACK); // Fond LCD noir
    
    TMR2_Start();       // Start Timer2 10Hz
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        switch(mainData.state)
        {
            case MAIN_STATE_SERVICE_TASKS:
            {
                // Lécture Id du capteur
                id = ens160_read16(PART_ID);
                
                // Execute le reste uniquement si ID ok
                if(id == PART_ID_RET)
                {
                    // Lécture valeur de AQI sur capteur ens160
                    aqi = ens160_read_aqi();
                    
                    // Lécture du status du capteur ens160
                    ens160Status = ens160_read_status();
                    
                    // Lécture de la tension de l'accu
                    voltage = batt_read_voltage();
                            
                    // Affiche text
                    lcd_print_line(0, "AQI / Batt. [mV]", LCD_BLUE, LCD_BLACK);
                
                    // Affiche indice qualité d'air
                    lcd_print_value(1, aqi, LCD_GREEN, LCD_BLACK);   
                
                    // Affiche tension de l'accu
                    lcd_print_value(1, voltage, LCD_RED, LCD_BLACK);
                }
                
                // GoTo -> Wait
                mainData.state = MAIN_STATE_WAIT;
                break;
            }
            case MAIN_STATE_WAIT:
            {
                // Do nothing
                break;
            }
            default:
            {
                // GoTo -> Wait
                mainData.state = MAIN_STATE_WAIT;
                break;
            }   
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

void main_update_state(MAIN_STATES newState)
{
    mainData.state = newState;
}


/*******************************************************************************
 End of File
*/

