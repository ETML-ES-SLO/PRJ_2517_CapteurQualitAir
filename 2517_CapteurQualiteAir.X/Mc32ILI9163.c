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
// KSA 14.06.2025       Clôture dev. version 1 de la librairie
//
//----------------------------------------------------------------------------//

//------------------------------------------------//
// Inclusions des fichiers header
//------------------------------------------------//

#include "Mc32ILI9163.h"
#include "Mc32ILI9163_font.h"
#include "definitions.h"
#include "../2517_CapteurQualiteAir.X/main.h"

//------------------------------------------------//
// Fonctions locales
//------------------------------------------------//

static void lcd_delay_ms(uint32_t ms)
{
    // Temporisation approximative réalisée par boucle de NOP.
    // À 24 MHz : 1 instruction = 41 ns, donc 1 ms = 24'000 instructions.
    for(uint32_t i = 0; i < (ms * CLK_MUC_MHZ * 1000); i++)
    {
        __asm__ volatile("nop");
    }
}


static void lcd_write8(uint8_t data)
{
    // Fonction reprise telle quelle du code exemple.
    // Envoi d'un octet au LCD via SPI logiciel.
    // Les bits sont transmis du MSB vers le LSB.
    
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if(data & 0x80)
        {
            LCD_MOSI_HIGH;
        }
        else
        {
            LCD_MOSI_LOW;
        }

        LCD_SCK_HIGH;

        // Petite attente pour respecter le timing du contrôleur.
        __asm__ volatile("nop");
        __asm__ volatile("nop");

        LCD_SCK_LOW;

        // Préparation du bit suivant.
        data <<= 1;
    }

}


static void lcd_write_command(uint8_t command)
{
    // Fonction reprise telle quelle du code exemple.
    // Envoie une commande au contrôleur LCD.

    LCD_CS_LOW;
    LCD_DC_COMMAND;
    LCD_SCK_LOW;

    lcd_write8(command);

    LCD_CS_HIGH;
}


static void lcd_write_data(uint8_t data)
{
    // Fonction reprise telle quelle du code exemple.
    // Envoie une donnée 8 bits au contrôleur LCD.

    LCD_CS_LOW;
    LCD_DC_DATA;
    LCD_SCK_LOW;

    lcd_write8(data);

    LCD_CS_HIGH;
}


static void lcd_write_data16(uint16_t data)
{
    // Fonction reprise telle quelle du code fourni.
    // Envoie une donnée 16 bits en deux octets.
    // Utilisé principalement pour les couleurs RGB565.

    lcd_write_data((uint8_t)(data >> 8));
    lcd_write_data((uint8_t)(data & 0xFF));
}


static void lcd_reset(void)
{
    // Fonction reprise telle quelle du code fourni.
    // Réinitialisation matérielle du contrôleur LCD.

    LCD_RESET_HIGH;

    lcd_delay_ms(120);

    LCD_RESET_LOW;

    lcd_delay_ms(80);

    LCD_RESET_HIGH;

    lcd_delay_ms(80);
}


static void lcd_set_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    // Fonction reprise telle quelle du code exemple.
    // Définit la zone mémoire dans laquelle les prochains pixels seront écrits.
    
    // Commande CASET : sélection des colonnes X.
    lcd_write_command(0x2A);
    lcd_write_data(0x00);
    lcd_write_data(x0 + LCD_X_OFFSET);
    lcd_write_data(0x00);
    lcd_write_data(x1 + LCD_X_OFFSET);

    // Commande RASET : sélection des lignes Y.
    lcd_write_command(0x2B);
    lcd_write_data(0x00);
    lcd_write_data(y0);
    lcd_write_data(0x00);
    lcd_write_data(y1);

    // Commande RAMWR : les prochaines données écrivent dans la mémoire graphique.
    lcd_write_command(0x2C);
}


//------------------------------------------------//
// Fonctions publiques
//------------------------------------------------//

void lcd_init(void)
{
    // Fonction reprise telle quelle du code exemple.
    // Initialise les lignes de contrôle, réinitialise le LCD,
    // configure le contrôleur ILI9163 puis efface l'écran.

    // Mise dans un état connu des signaux de contrôle.
    LCD_BACKLIGHT_ON;
    LCD_CS_HIGH;
    LCD_SCK_LOW;
    LCD_MOSI_LOW;
    LCD_DC_DATA;

    // Reset matériel du contrôleur.
    lcd_reset();

    // MADCTL : orientation mémoire / ordre RGB.
    lcd_write_command(0x36);
    lcd_write_data(0x08);

    // COLMOD : format couleur RGB565, 16 bits par pixel.
    lcd_write_command(0x3A);
    lcd_write_data(0x55);

    // Définition initiale de la plage de colonnes.
    lcd_write_command(0x2A);
    lcd_write_data(0x00);
    lcd_write_data(0x18);
    lcd_write_data(0x00);
    lcd_write_data(0x67);

    // Définition initiale de la plage de lignes.
    lcd_write_command(0x2B);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x9F);

    // Configuration du frame rate.
    lcd_write_command(0xB1);
    lcd_write_data(0x0A);
    lcd_write_data(0x05);

    // Paramètres d'alimentation interne.
    lcd_write_command(0xC0);
    lcd_write_data(0x08);
    lcd_write_data(0x00);
    lcd_write_command(0xC1);
    lcd_write_data(0x03);
    lcd_write_command(0xC2);
    lcd_write_data(0x05);

    // Réglage VCOM.
    lcd_write_command(0xC5);
    lcd_write_data(0x43);
    lcd_write_data(0x43);

    // Configuration spécifique du contrôleur.
    lcd_write_command(0xEC);
    lcd_write_data(0x0C);

    // Activation / configuration gamma.
    lcd_write_command(0xF2);
    lcd_write_data(0x01);

    // Courbe gamma positive.
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

    // Courbe gamma négative.
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

    // Sortie du mode veille.
    lcd_write_command(0x11);
    lcd_delay_ms(120);

    // Activation de l'affichage.
    lcd_write_command(0x29);
    lcd_delay_ms(20);

    // Nettoyage de l'écran après initialisation.
    lcd_fill(LCD_BLACK);
}


void lcd_fill(uint16_t color)
{
    // Fonction reprise telle quelle du code exemple.
    // Remplit toute la surface de l'écran avec une seule couleur.

    uint32_t i;

    // Sélection de toute la zone visible de l'écran.
    lcd_set_window(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    LCD_CS_LOW;
    LCD_DC_DATA;

    // Écriture de la couleur sur chaque pixel.
    for(i = 0; i < ((uint32_t)LCD_WIDTH * LCD_HEIGHT); i++)
    {
        lcd_write8((uint8_t)(color >> 8));
        lcd_write8((uint8_t)(color & 0xFF));
    }

    LCD_CS_HIGH;
}


static const uint8_t* lcd_get_glyph(char c)
{
    // Retourne le bitmap du caractère demandé dans la table de police.
    // Si le caractère n'est pas imprimable en ASCII standard,
    // il est remplacé par '?'.

    if(c < 32 || c > 126)
    {
        c = '?';
    }

    return lcd_font[c - 32];
}

static void lcd_draw_char(uint8_t x, uint8_t y, char c, uint16_t text_color, uint16_t bg_color)
{
    // Dessine un caractère 5x8 pixels avec une colonne d'espacement.

    const uint8_t* glyph;
    uint8_t row;
    uint8_t col;

    // Récupération du bitmap du caractère.
    glyph = lcd_get_glyph(c);

    // Chaque caractère occupe une zone de 6x8 pixels :
    // 5 colonnes pour le dessin et 1 colonne pour l'espacement.
    lcd_set_window(x, y, x + 5, y + 7);

    LCD_CS_LOW;
    LCD_DC_DATA;

    for(row = 0; row < 8; row++)
    {
        for(col = 0; col < 6; col++)
        {
            uint16_t color = bg_color;

            // La 6ème colonne est laissée en couleur de fond
            // afin de créer un espace entre deux caractères.
            if(col < 5)
            {
                // Chaque bit du glyph indique si le pixel doit être allumé.
                if(glyph[col] & (1 << row))
                {
                    color = text_color;
                }
            }

            // Envoi du pixel au format RGB565.
            lcd_write8((uint8_t)(color >> 8));
            lcd_write8((uint8_t)(color & 0xFF));
        }
    }
    LCD_CS_HIGH;
}


void lcd_print_line(uint8_t line, const char *text, uint16_t text_color, uint16_t bg_color)
{
    // Affiche une chaîne de caractères centrée sur une des lignes prédéfinies.

    uint8_t len;
    uint8_t x;
    uint8_t y;
    uint8_t i;

    // Protection contre un pointeur nul.
    if(text == NULL)
    {
        return;
    }

    // Longueur de la chaîne à afficher.
    len = (uint8_t)strlen(text);

    // Limitation à 13 caractères pour rester dans la largeur de l'écran.
    if(len > 13)
    {
        len = 13;
    }

    // Calcul de la position X pour centrer le texte.
    x = (LCD_WIDTH - (len * 6)) / 2;
    
    // Position verticale selon la ligne demandée.
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

    // Affichage caractère par caractère.
    for(i = 0; i < len; i++)
    {
        lcd_draw_char((uint8_t)(x + (i * 6)), y, text[i], text_color, bg_color);
    }
}


void lcd_print_value(uint8_t line, int32_t value, uint16_t text_color, uint16_t bg_color)
{
    // Convertit une valeur entière en texte puis l'affiche sur le LCD.

    char buffer[20];

    // Conversion de la valeur numérique en chaîne de caractères.
    sprintf(buffer, "%ld", (long)value);

    // Affichage de la chaîne générée.
    lcd_print_line(line, buffer, text_color, bg_color);
}