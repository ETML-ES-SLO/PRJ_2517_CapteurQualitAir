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
// Param écran
//------------------------------------------------//


//------------------------------------------------//
// Macros
//------------------------------------------------//


//------------------------------------------------//
// Définition des prototypes de fonctions
//------------------------------------------------//

//----------------------------------------------------------------------------------//
//-- nom fct : ft812_memory_write8 
//-- paramètre entrée : command => Commande host
//--                    commandParam => Paramètre de la commande
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) :   - 
//-- description : Envoie de 24 bits par SPI pour envoie de commande sur FT812 
//-- démonstration : [0x40 + commande][param][0x00] 
//-- aide - référence - lien : Page.16 du datasheet DS_FT81x.pdf
//----------------------------------------------------------------------------------//



#endif

