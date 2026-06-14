#ifndef _MAIN_H
#define _MAIN_H

//------------------------------------------------//
// Inclusion librairies
//------------------------------------------------//
#include <stdint.h>
#include <stdbool.h>

//------------------------------------------------//
// Param MCU pour délais
//------------------------------------------------//
#define CLK_MUC_MHZ 24

//------------------------------------------------//
// Enumerations
//------------------------------------------------//

// State machine du main
typedef enum {
	MAIN_STATE_SERVICE_TASKS,
    MAIN_STATE_WAIT,
} MAIN_STATES;

//------------------------------------------------//
// Structures
//------------------------------------------------//

typedef struct {
    MAIN_STATES state;
} MAIN_DATA;

//------------------------------------------------//
// define
//------------------------------------------------//


//------------------------------------------------//
// Macros
//------------------------------------------------//


//------------------------------------------------//
// Définition des prototypes de fonctions
//------------------------------------------------//

//----------------------------------------------------------------------------------//
//-- nom fct : main_update_state 
//-- paramètre entrée : us (temp d'attente en us)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) :   - 
//-- description : Fonction de delais en us 
//-- démonstration : À 24 MHz ? 1 instruction ? 41 ns, 1 µs ? 24 instructions 
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
void main_update_state(MAIN_STATES newState);
        
#endif

