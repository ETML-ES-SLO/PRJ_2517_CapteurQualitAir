//----------------------------------------------------------------------------//
//          Mc32ILI9163.c
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
//----------------------------------------------------------------------------//

//------------------------------------------------//
// Inclusions des fichiers header
//------------------------------------------------//

#include "Mc32ILI9163.h"
#include "Mc32ILI9163_font.h"
#include "definitions.h"
//#include "peripheral/spi/spi_master/plib_spi1_master.h"
#include "../2517_CapteurQualiteAir.X/main.h"

//------------------------------------------------//
// Fonctions
//------------------------------------------------//
 
/******************************************************************************
* Configuration écran
******************************************************************************/
#define LCD_WIDTH      80
#define LCD_HEIGHT     160
 
/*
* Offset obligatoire pour ce modèle Displaytech.
*/

#define LCD_X_OFFSET   24
 
/******************************************************************************
* Macros GPIO MCC
******************************************************************************/
 
#define LCD_CS_LOW        TFT_CS_Clear()
#define LCD_CS_HIGH       TFT_CS_Set()

#define LCD_DC_COMMAND    TFT_COMMAND_DATA_SELECT_Clear()
#define LCD_DC_DATA       TFT_COMMAND_DATA_SELECT_Set()

#define LCD_RESET_LOW     TFT_RESET_Clear()
#define LCD_RESET_HIGH    TFT_RESET_Set()

#define LCD_BACKLIGHT_OFF TFT_BACKLIGHT_Clear()
#define LCD_BACKLIGHT_ON  TFT_BACKLIGHT_Set()
 
/******************************************************************************
* Delay
******************************************************************************/
 
static void lcd_delay_ms(uint32_t ms)

{
    // À 24 MHz -> 1 instruction -> 41 ns
    // 1 ms -> 24'000 instructions
    for(uint32_t i = 0; i < (ms * CLK_MUC_MHZ * 1000); i++)
    {
        __asm__ volatile("nop");
    }
}
 
/******************************************************************************

* Envoi d'un octet SPI

******************************************************************************/
 /*
static void lcd_write8(uint8_t data)
{

    while(SPI1_IsTransmitterBusy());

    while(SPI1_Write(&data, 1) == false);

    while(SPI1_IsTransmitterBusy());

}*/

#define LCD_SCK_HIGH()   TFT_SCK_Set()
#define LCD_SCK_LOW()    TFT_SCK_Clear()
#define LCD_MOSI_HIGH()  TFT_MOSI_Set()
#define LCD_MOSI_LOW()   TFT_MOSI_Clear()

static void lcd_write8(uint8_t data)

{
    for(uint8_t i = 0; i < 8; i++)
    {
        if(data & 0x80)
        {
            LCD_MOSI_HIGH();
        }
        else
        {
            LCD_MOSI_LOW();
        }
        LCD_SCK_HIGH();
        __asm__ volatile("nop");
        __asm__ volatile("nop");
        LCD_SCK_LOW();
        data <<= 1;
    }
}
 
 
 
/******************************************************************************

* Commande LCD

******************************************************************************/
 
static void lcd_write_command(uint8_t command)

{

    LCD_CS_LOW;
 
    LCD_DC_COMMAND;
 
    lcd_write8(command);
 
    LCD_CS_HIGH;

}
 
/******************************************************************************

* Donnée LCD

******************************************************************************/
 
static void lcd_write_data(uint8_t data)

{

    LCD_CS_LOW;
 
    LCD_DC_DATA;
 
    lcd_write8(data);
 
    LCD_CS_HIGH;

}
 
/******************************************************************************

* Donnée 16 bits

******************************************************************************/
 
static void lcd_write_data16(uint16_t data)

{

    lcd_write_data((uint8_t)(data >> 8));

    lcd_write_data((uint8_t)data);

}
 
/******************************************************************************

* Reset matériel écran

******************************************************************************/
 
static void lcd_reset(void)

{

    LCD_RESET_HIGH;

    lcd_delay_ms(120);
 
    LCD_RESET_LOW;

    lcd_delay_ms(80);
 
    LCD_RESET_HIGH;

    lcd_delay_ms(80);

}
 
/******************************************************************************

* Zone mémoire d'écriture

******************************************************************************/
 
static void lcd_set_window(uint8_t x0,

                           uint8_t y0,

                           uint8_t x1,

                           uint8_t y1)

{

    lcd_write_command(0x2A);
 
    lcd_write_data(0x00);

    lcd_write_data(x0 + LCD_X_OFFSET);
 
    lcd_write_data(0x00);

    lcd_write_data(x1 + LCD_X_OFFSET);
 
    lcd_write_command(0x2B);
 
    lcd_write_data(0x00);

    lcd_write_data(y0);
 
    lcd_write_data(0x00);

    lcd_write_data(y1);
 
    lcd_write_command(0x2C);

}
 
/******************************************************************************

* Initialisation ILI9163

******************************************************************************/
 
void lcd_init(void)

{

    LCD_BACKLIGHT_ON;

    LCD_CS_HIGH;

    lcd_reset();

    lcd_write_command(0x36);

    lcd_write_data(0x08);

    lcd_write_command(0x3A);

    lcd_write_data(0x55);

    lcd_write_command(0x2A);

    lcd_write_data(0x00);

    lcd_write_data(0x18);

    lcd_write_data(0x00);

    lcd_write_data(0x67);

    lcd_write_command(0x2B);

    lcd_write_data(0x00);

    lcd_write_data(0x00);

    lcd_write_data(0x00);

    lcd_write_data(0x9F);

    lcd_write_command(0xB1);

    lcd_write_data(0x0A);

    lcd_write_data(0x05);

    lcd_write_command(0xC0);

    lcd_write_data(0x08);

    lcd_write_data(0x00);

    lcd_write_command(0xC1);

    lcd_write_data(0x03);

    lcd_write_command(0xC2);

    lcd_write_data(0x05);

    lcd_write_command(0xC5);

    lcd_write_data(0x43);

    lcd_write_data(0x43);

    lcd_write_command(0xEC);

    lcd_write_data(0x0C);

    lcd_write_command(0xF2);

    lcd_write_data(0x01);

    lcd_write_command(0xE0);

    lcd_write_data(0x3B);

    lcd_write_data(0x2B);

    lcd_write_data(0x2A);

    lcd_write_data(0x2D);

    lcd_write_data(0x28);

    lcd_write_data(0x0C);

    lcd_write_data(0x57);

    lcd_write_data(0xF0);

    lcd_write_data(0x41);

    lcd_write_data(0x12);

    lcd_write_data(0x15);

    lcd_write_data(0x12);

    lcd_write_data(0x11);

    lcd_write_data(0x10);

    lcd_write_data(0x04);

    lcd_write_command(0xE1);

    lcd_write_data(0x04);

    lcd_write_data(0x14);

    lcd_write_data(0x15);

    lcd_write_data(0x12);

    lcd_write_data(0x17);

    lcd_write_data(0x13);

    lcd_write_data(0x28);

    lcd_write_data(0x60);

    lcd_write_data(0x3E);

    lcd_write_data(0x0D);

    lcd_write_data(0x2A);

    lcd_write_data(0x2D);

    lcd_write_data(0x2E);

    lcd_write_data(0x2F);

    lcd_write_data(0x3B);

    lcd_write_command(0x11);

    lcd_delay_ms(120);

    lcd_write_command(0x29);

    lcd_delay_ms(20);

    lcd_fill(LCD_BLACK);

}
 
 
/******************************************************************************

* Remplissage écran

******************************************************************************/
 
void lcd_fill(uint16_t color)

{

    uint32_t i;
 
    lcd_set_window(0,

                   0,

                   LCD_WIDTH - 1,

                   LCD_HEIGHT - 1);
 
    LCD_CS_LOW;
 
    LCD_DC_DATA;
 
    for(i = 0; i < ((uint32_t)LCD_WIDTH * LCD_HEIGHT); i++)

    {

        lcd_write8((uint8_t)(color >> 8));

        lcd_write8((uint8_t)color);

    }
 
    LCD_CS_HIGH;

}
 
/******************************************************************************

* Retourne le glyph ASCII

******************************************************************************/
 
static const uint8_t* lcd_get_glyph(char c)

{

    if(c < 32 || c > 126)

    {

        c = '?';

    }
 
    return lcd_font[c - 32];

}
 
/******************************************************************************

* Dessin d'un caractère

******************************************************************************/
 
static void lcd_draw_char(uint8_t x,

                          uint8_t y,

                          char c,

                          uint16_t text_color,

                          uint16_t bg_color)

{

    const uint8_t* glyph;
 
    glyph = lcd_get_glyph(c);
 
    lcd_set_window(x,

                   y,

                   x + 5,

                   y + 7);
 
    LCD_CS_LOW;
 
    LCD_DC_DATA;
 
    for(uint8_t row = 0; row < 8; row++)

    {

        for(uint8_t col = 0; col < 6; col++)

        {

            uint16_t color = bg_color;
 
            if(col < 5)

            {

                if(glyph[col] & (1 << row))

                {

                    color = text_color;

                }

            }
 
            lcd_write8(color >> 8);

            lcd_write8(color);

        }

    }
 
    LCD_CS_HIGH;

}
 
/******************************************************************************

* Affichage texte centré

******************************************************************************/
 
void lcd_print_line(uint8_t line,

                    const char *text,

                    uint16_t text_color,

                    uint16_t bg_color)

{

    uint8_t len;

    uint8_t x;

    uint8_t y;
 
    len = strlen(text);
 
    x = (LCD_WIDTH - (len * 6)) / 2;
 
    switch(line)

    {

        case 0:

            y = 35;

            break;
 
        case 1:

            y = 75;

            break;
 
        default:

            y = 115;

            break;

    }
 
    for(uint8_t i = 0; i < len; i++)

    {

        lcd_draw_char(x + (i * 6),

                      y,

                      text[i],

                      text_color,

                      bg_color);

    }

}
 
/******************************************************************************

* Affichage valeur numérique

******************************************************************************/
 
void lcd_print_value(uint8_t line,

                     int32_t value,

                     uint16_t text_color,

                     uint16_t bg_color)

{

    char buffer[20];
 
    sprintf(buffer, "%ld", (long)value);
 
    lcd_print_line(line,

                   buffer,

                   text_color,

                   bg_color);

}
 