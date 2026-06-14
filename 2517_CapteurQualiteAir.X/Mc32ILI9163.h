//----------------------------------------------------------------------------//
//          Mc32ILI9163.h
//----------------------------------------------------------------------------//
// Description      :   Librairie pour le driver graphique ili9163
//
// Auteur           :   Karol Stopa
// Date de création :   05.06.2026
// Compilateur      :   XC32 v5.10
//
// MODIFICATIONS    :
// KSA 05.06.2026       Création fichiers Mc32ILI9163.c et .h
// KSA 14.06.2025       Clôture dev. version 1 de la librairie
//
// documetation : Inspiration lib. pour TFT
// ...\PROJ\2517_CapteurQualiteAir\soft\Inspi_TFT
// \Displaytech-DT010TFT-sample-code-file-package
// \Displaytech-DT010TFT-sample-code-file-package\Test.X\main.c
//----------------------------------------------------------------------------//

#ifndef _MC32ILI9163_H
#define _MC32ILI9163_H

//------------------------------------------------//
// Inclusion librairies
//------------------------------------------------//
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------------//
// Param. dimensions écran DT010
//------------------------------------------------//

#define LCD_WIDTH      80
#define LCD_HEIGHT     160
#define LCD_X_OFFSET   24

//------------------------------------------------//
// Couleurs RGB565
//------------------------------------------------//
#define LCD_BLACK      0x0000
#define LCD_WHITE      0xFFFF
#define LCD_RED        0xF800
#define LCD_GREEN      0x07E0
#define LCD_BLUE       0x001F
#define LCD_YELLOW     0xFFE0
#define LCD_CYAN       0x07FF
#define LCD_MAGENTA    0xF81F
#define LCD_ORANGE     0xFD20

//------------------------------------------------//
// Macros
//------------------------------------------------//

#define LCD_CS_LOW          TFT_CS_Clear()
#define LCD_CS_HIGH         TFT_CS_Set()

#define LCD_DC_COMMAND      TFT_COMMAND_DATA_SELECT_Clear()
#define LCD_DC_DATA         TFT_COMMAND_DATA_SELECT_Set()

#define LCD_RESET_LOW       TFT_RESET_Clear()
#define LCD_RESET_HIGH      TFT_RESET_Set()

#define LCD_BACKLIGHT_OFF   TFT_BACKLIGHT_Clear()
#define LCD_BACKLIGHT_ON    TFT_BACKLIGHT_Set()

#define LCD_SCK_HIGH        TFT_SCK_Set()
#define LCD_SCK_LOW         TFT_SCK_Clear()

#define LCD_MOSI_HIGH       TFT_MOSI_Set()
#define LCD_MOSI_LOW        TFT_MOSI_Clear()

//------------------------------------------------//
// Définition des prototypes de fonctions
//------------------------------------------------//

//----------------------------------------------------------------------------------//
//-- nom fct : lcd_init
//-- paramètre entrée : -
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) : -
//-- description : Initialise l'écran LCD et configure ses paramètres de fonctionnement.
//-- démonstration : Appeler cette fonction une seule fois au démarrage avant toute
//--                 utilisation des fonctions d'affichage.
//-- aide - référence - lien : Documentation du contrôleur LCD utilisé.
//----------------------------------------------------------------------------------//
void lcd_init(void);

//----------------------------------------------------------------------------------//
//-- nom fct : lcd_fill
//-- paramètre entrée : color (couleur de remplissage au format RGB565)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) : -
//-- description : Remplit entièrement l'écran LCD avec la couleur spécifiée.
//-- démonstration : lcd_fill(0xFFFF);   // Remplit l'écran en blanc
//-- aide - référence - lien : Format de couleur RGB565.
//----------------------------------------------------------------------------------//
void lcd_fill(uint16_t color);

//----------------------------------------------------------------------------------//
//-- nom fct : lcd_print_line
//-- paramètre entrée : line       (numéro de ligne à afficher)
//--                    text       (chaîne de caractères à afficher)
//--                    text_color (couleur du texte)
//--                    bg_color   (couleur de fond)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) : -
//-- description : Affiche une chaîne de caractères sur une ligne de l'écran LCD.
//-- démonstration : lcd_print_line(0, "Bonjour", WHITE, BLACK);
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
void lcd_print_line(uint8_t line,
                    const char *text,
                    uint16_t text_color,
                    uint16_t bg_color);

//----------------------------------------------------------------------------------//
//-- nom fct : lcd_print_value
//-- paramètre entrée : line       (numéro de ligne à afficher)
//--                    value      (valeur entière à afficher)
//--                    text_color (couleur du texte)
//--                    bg_color   (couleur de fond)
//-- paramètre sortie : -
//-- paramètre référence (IN-OUT) : -
//-- description : Affiche une valeur numérique sur une ligne de l'écran LCD.
//-- démonstration : lcd_print_value(1, 1234, WHITE, BLACK);
//-- aide - référence - lien : -
//----------------------------------------------------------------------------------//
void lcd_print_value(uint8_t line,
                     int32_t value,
                     uint16_t text_color,
                     uint16_t bg_color);

#endif
 