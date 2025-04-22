/*
* AD8232.c
*
*  Created on: April 11th, 2025
*      Author: Georgios Adamopoulos
*/


#ifndef AD8232_H
#define AD8232_H

#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "ADC0.h"
#include "../inc/ST7735.h"
#include "AD8232.h"



/* 
   GPIO Connections for Leads Off Detection
   AD8232 will use PA10 for LO+ and PA11 for LO- 
*/
#define LO_PLUS_PIN   20         // LO+ is PA10
#define LO_PLUS_MASK  (1 << LO_PLUS_PIN)
#define LO_MINUS_PIN  21         // LO- is PA11
#define LO_MINUS_MASK  (1 << LO_MINUS_PIN)


/* GPIO Pins for SDN and AC/DC */
#define AD8232_SDN_PIN 18
#define AD8232_SDN_MASK (1 << AD8232_SDN_PIN)
// #define AD8232_ACDC_PIN 19
// #define AD8232_ACDC_MASK (1 << AD8232_ACDC_PIN)

// /* AC/DC Specifics: */

// #define AD8232_ACDC_DC 0 // Force AC/DC Low
// #define AD8232_ACDC_AC 1 // FOrce AC/DC High



static void AD8232_GPIOInit(void) {
    // Configure SDN and AC/DC pins as GPIO (output mode)
    IOMUX->SECCFG.PINCM[AD8232_SDN_PIN] = 0x00000081;   // Mode 0 (GPIO); the hex value here sets the pin as GPIO; adjust if needed.
    // IOMUX->SECCFG.PINCM[AD8232_ACDC_PIN] = 0x00000081;  // Configure as GPIO output.

    // For LO+ and LO–, configure them as GPIO inputs with internal pull-ups enabled.
    IOMUX->SECCFG.PINCM[LO_PLUS_PIN] = 0x00040081;   
    IOMUX->SECCFG.PINCM[LO_MINUS_PIN] = 0x00040081;  

    // // Enable outputs for SDN and AC/DC (on GPIO port A)
    // GPIOA->DOE31_0 |= (1 << AD8232_SDN_PIN);

    // // Set initial output values:
    // // Enable the sensor: set SDN high.
    // GPIOA->DOUTSET31_0 = (1 << AD8232_SDN_PIN);
    // Select DC leads-off mode: set AC/DC low.
    // GPIOA->DOUTCLR31_0 = (1 << AD8232_ACDC_PIN);
    // (LO+ and LO– are configured as inputs; no output enable is required.)
}



//Initialize pins for Leads Detection
void AD8232_Init(void){
    // Initialize the sensor’s GPIO pins.
    AD8232_GPIOInit();
    // Initialize ADC0 for the sensor.
    // (In our configuration, we assume the ECG output from AD8232 is connected to ADC0 channel 6, e.g., on PB20.)
    ADC0init();
}


/*
 * Checks if ECG leads are connected.
 * Returns 1 if disconnected, 0 if connected.
 */
bool AD8232_LeadsOff(void) {
     // Read the LO⁺ and LO⁻ digital inputs.
   // If both pins are high then assume that the electrodes are disconnected.
   uint32_t loPlus  = GPIOA->DIN31_0 & (1 << LO_PLUS_PIN);
   uint32_t loMinus = GPIOA->DIN31_0 & (1 << LO_MINUS_PIN);
  if ((loPlus != 0) && (loMinus != 0)) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Reads ECG voltage from ADC.
 * Returns a 12-bit ADC value (0–4095).
 */
uint16_t AD8232_ReadECG(void) {
    return ADC0in();
}

//  displays ECG data or "LEADS OFF" on the ST7735 display.
void AD8232_DisplayECG(void){
    if (AD8232_LeadsOff()) {
        ST7735_SetCursor(0, 0);
        ST7735_OutString("LEADS OFF!");
    } else {
        uint16_t ecgValue = AD8232_ReadECG();
        ST7735_SetCursor(0, 0);
        ST7735_OutString("ECG: ");
        ST7735_OutUDec(ecgValue);
    }
}

#endif /* AD8232_H */