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

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "../2517_CapteurQualiteAir.X/main.h"
#include "../2517_CapteurQualiteAir.X/Mc32CapteurENS160.h"
#include "../2517_CapteurQualiteAir.X/Mc32BattCtrl.h"

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
    
    // Test
    uint16_t id;
    uint16_t voltage;
    ens160_status ens160Status;
    
    TMR2_Start();       // Init Timer2 10Hz
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        switch(mainData.state)
        {
            case MAIN_STATE_SERVICE_TASKS:
            {
                //ens160_write8(0x10, 0x02);;
                id = ens160_read16(PART_ID);
                //ens160_read8(DATA_AQI);
                //ns160Status = ens160_read_status();
                //GPIO_TP14_Toggle();
                //voltage = batt_read_voltage();
                
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

