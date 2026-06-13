/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for AIR_INT pin ***/
#define AIR_INT_Get()               ((PORTA >> 0) & 0x1)
#define AIR_INT_GetLatch()          ((LATA >> 0) & 0x1)
#define AIR_INT_PIN                  GPIO_PIN_RA0

/*** Macros for ADC_BAT pin ***/
#define ADC_BAT_Get()               ((PORTB >> 0) & 0x1)
#define ADC_BAT_GetLatch()          ((LATB >> 0) & 0x1)
#define ADC_BAT_PIN                  GPIO_PIN_RB0

/*** Macros for STAT_PMIC pin ***/
#define STAT_PMIC_Set()               (LATBSET = (1<<1))
#define STAT_PMIC_Clear()             (LATBCLR = (1<<1))
#define STAT_PMIC_Toggle()            (LATBINV= (1<<1))
#define STAT_PMIC_OutputEnable()      (TRISBCLR = (1<<1))
#define STAT_PMIC_InputEnable()       (TRISBSET = (1<<1))
#define STAT_PMIC_Get()               ((PORTB >> 1) & 0x1)
#define STAT_PMIC_GetLatch()          ((LATB >> 1) & 0x1)
#define STAT_PMIC_PIN                  GPIO_PIN_RB1

/*** Macros for TFT_BACKLIGHT pin ***/
#define TFT_BACKLIGHT_Set()               (LATASET = (1<<2))
#define TFT_BACKLIGHT_Clear()             (LATACLR = (1<<2))
#define TFT_BACKLIGHT_Toggle()            (LATAINV= (1<<2))
#define TFT_BACKLIGHT_OutputEnable()      (TRISACLR = (1<<2))
#define TFT_BACKLIGHT_InputEnable()       (TRISASET = (1<<2))
#define TFT_BACKLIGHT_Get()               ((PORTA >> 2) & 0x1)
#define TFT_BACKLIGHT_GetLatch()          ((LATA >> 2) & 0x1)
#define TFT_BACKLIGHT_PIN                  GPIO_PIN_RA2

/*** Macros for TFT_RESET pin ***/
#define TFT_RESET_Set()               (LATASET = (1<<3))
#define TFT_RESET_Clear()             (LATACLR = (1<<3))
#define TFT_RESET_Toggle()            (LATAINV= (1<<3))
#define TFT_RESET_OutputEnable()      (TRISACLR = (1<<3))
#define TFT_RESET_InputEnable()       (TRISASET = (1<<3))
#define TFT_RESET_Get()               ((PORTA >> 3) & 0x1)
#define TFT_RESET_GetLatch()          ((LATA >> 3) & 0x1)
#define TFT_RESET_PIN                  GPIO_PIN_RA3

/*** Macros for TFT_COMMAND_DATA_SELECT pin ***/
#define TFT_COMMAND_DATA_SELECT_Set()               (LATBSET = (1<<4))
#define TFT_COMMAND_DATA_SELECT_Clear()             (LATBCLR = (1<<4))
#define TFT_COMMAND_DATA_SELECT_Toggle()            (LATBINV= (1<<4))
#define TFT_COMMAND_DATA_SELECT_OutputEnable()      (TRISBCLR = (1<<4))
#define TFT_COMMAND_DATA_SELECT_InputEnable()       (TRISBSET = (1<<4))
#define TFT_COMMAND_DATA_SELECT_Get()               ((PORTB >> 4) & 0x1)
#define TFT_COMMAND_DATA_SELECT_GetLatch()          ((LATB >> 4) & 0x1)
#define TFT_COMMAND_DATA_SELECT_PIN                  GPIO_PIN_RB4

/*** Macros for TFT_CS pin ***/
#define TFT_CS_Set()               (LATBSET = (1<<6))
#define TFT_CS_Clear()             (LATBCLR = (1<<6))
#define TFT_CS_Toggle()            (LATBINV= (1<<6))
#define TFT_CS_OutputEnable()      (TRISBCLR = (1<<6))
#define TFT_CS_InputEnable()       (TRISBSET = (1<<6))
#define TFT_CS_Get()               ((PORTB >> 6) & 0x1)
#define TFT_CS_GetLatch()          ((LATB >> 6) & 0x1)
#define TFT_CS_PIN                  GPIO_PIN_RB6

/*** Macros for AIR_SDA pin ***/
#define AIR_SDA_Get()               ((PORTB >> 7) & 0x1)
#define AIR_SDA_GetLatch()          ((LATB >> 7) & 0x1)
#define AIR_SDA_PIN                  GPIO_PIN_RB7

/*** Macros for TFT_SCK pin ***/
#define TFT_SCK_Set()               (LATBSET = (1<<8))
#define TFT_SCK_Clear()             (LATBCLR = (1<<8))
#define TFT_SCK_Toggle()            (LATBINV= (1<<8))
#define TFT_SCK_OutputEnable()      (TRISBCLR = (1<<8))
#define TFT_SCK_InputEnable()       (TRISBSET = (1<<8))
#define TFT_SCK_Get()               ((PORTB >> 8) & 0x1)
#define TFT_SCK_GetLatch()          ((LATB >> 8) & 0x1)
#define TFT_SCK_PIN                  GPIO_PIN_RB8

/*** Macros for TFT_MOSI pin ***/
#define TFT_MOSI_Set()               (LATBSET = (1<<9))
#define TFT_MOSI_Clear()             (LATBCLR = (1<<9))
#define TFT_MOSI_Toggle()            (LATBINV= (1<<9))
#define TFT_MOSI_OutputEnable()      (TRISBCLR = (1<<9))
#define TFT_MOSI_InputEnable()       (TRISBSET = (1<<9))
#define TFT_MOSI_Get()               ((PORTB >> 9) & 0x1)
#define TFT_MOSI_GetLatch()          ((LATB >> 9) & 0x1)
#define TFT_MOSI_PIN                  GPIO_PIN_RB9

/*** Macros for GPIO_TP14 pin ***/
#define GPIO_TP14_Set()               (LATBSET = (1<<10))
#define GPIO_TP14_Clear()             (LATBCLR = (1<<10))
#define GPIO_TP14_Toggle()            (LATBINV= (1<<10))
#define GPIO_TP14_OutputEnable()      (TRISBCLR = (1<<10))
#define GPIO_TP14_InputEnable()       (TRISBSET = (1<<10))
#define GPIO_TP14_Get()               ((PORTB >> 10) & 0x1)
#define GPIO_TP14_GetLatch()          ((LATB >> 10) & 0x1)
#define GPIO_TP14_PIN                  GPIO_PIN_RB10

/*** Macros for GPIO_TP13 pin ***/
#define GPIO_TP13_Set()               (LATBSET = (1<<11))
#define GPIO_TP13_Clear()             (LATBCLR = (1<<11))
#define GPIO_TP13_Toggle()            (LATBINV= (1<<11))
#define GPIO_TP13_OutputEnable()      (TRISBCLR = (1<<11))
#define GPIO_TP13_InputEnable()       (TRISBSET = (1<<11))
#define GPIO_TP13_Get()               ((PORTB >> 11) & 0x1)
#define GPIO_TP13_GetLatch()          ((LATB >> 11) & 0x1)
#define GPIO_TP13_PIN                  GPIO_PIN_RB11

/*** Macros for AIR_SCL pin ***/
#define AIR_SCL_Get()               ((PORTB >> 13) & 0x1)
#define AIR_SCL_GetLatch()          ((LATB >> 13) & 0x1)
#define AIR_SCL_PIN                  GPIO_PIN_RB13

/*** Macros for BTN pin ***/
#define BTN_Get()               ((PORTB >> 14) & 0x1)
#define BTN_GetLatch()          ((LATB >> 14) & 0x1)
#define BTN_PIN                  GPIO_PIN_RB14


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/
#define    GPIO_PORT_A   (0U)
#define    GPIO_PORT_B   (1U)
#define    GPIO_PORT_C   (2U)
typedef uint32_t GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/
#define    GPIO_PIN_RA0   (0U)
#define    GPIO_PIN_RA1   (1U)
#define    GPIO_PIN_RA2   (2U)
#define    GPIO_PIN_RA3   (3U)
#define    GPIO_PIN_RA4   (4U)
#define    GPIO_PIN_RB0   (16U)
#define    GPIO_PIN_RB1   (17U)
#define    GPIO_PIN_RB2   (18U)
#define    GPIO_PIN_RB3   (19U)
#define    GPIO_PIN_RB4   (20U)
#define    GPIO_PIN_RB5   (21U)
#define    GPIO_PIN_RB6   (22U)
#define    GPIO_PIN_RB7   (23U)
#define    GPIO_PIN_RB8   (24U)
#define    GPIO_PIN_RB9   (25U)
#define    GPIO_PIN_RB10   (26U)
#define    GPIO_PIN_RB11   (27U)
#define    GPIO_PIN_RB13   (29U)
#define    GPIO_PIN_RB14   (30U)
#define    GPIO_PIN_RB15   (31U)
#define    GPIO_PIN_RC9   (41U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE   (-1)

typedef uint32_t GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xFU), (uint32_t)(value) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xFU)) & 0x1U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xFU)) & 0x1U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
