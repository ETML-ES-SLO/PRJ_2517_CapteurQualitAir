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
 
/******************************************************************************
* Couleurs RGB565
******************************************************************************/
 
#define LCD_BLACK      0x0000
#define LCD_WHITE      0xFFFF
#define LCD_RED        0xF800
#define LCD_GREEN      0x07E0
#define LCD_BLUE       0x001F
#define LCD_YELLOW     0xFFE0
#define LCD_CYAN       0x07FF
#define LCD_MAGENTA    0xF81F 
#define LCD_ORANGE     0xFD20
 
/*****************************************************************************
* API publique
******************************************************************************/
 
void lcd_init(void);
 
void lcd_fill(uint16_t color);
 
void lcd_print_line(uint8_t line,

                    const char *text,

                    uint16_t text_color,

                    uint16_t bg_color);
 
void lcd_print_value(uint8_t line,

                     int32_t value,

                     uint16_t text_color,

                     uint16_t bg_color);
 
#endif
 