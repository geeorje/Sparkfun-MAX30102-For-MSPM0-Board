/*
 * HeartRate.h
 *
 *  Created on: April 11th, 2025
 *      Author: Georgios Adamopoulos
 */
    
#ifndef AD8232_H
#define AD8232_H


#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"


/* 
   GPIO Connections for Leads Off Detection
   AD8232 will use PA10 for LO+ and PA11 for LO- 
*/
#define LO_PLUS_PIN   20         // LO+ is PA10
#define LO_PLUS_MASK  (1 << LO_PLUS_PIN)
#define LO_MINUS_PIN  21         // LO- is PA11
#define LO_MINUS_MASK  (1 << LO_MINUS_PIN)


// Use Channel 6 PB20 for ADC0 
// Use #define in case we need to change it
#define AD8232_ADC_CHANNEL   6



/* GPIO Pins for SDN and AC/DC */
#define AD8232_SDN_PIN 18
#define AD8232_SDN_MASK (1 << AD8232_SDN_PIN)
// #define AD8232_ACDC_PIN 19
// #define AD8232_ACDC_MASK (1 << AD8232_ACDC_PIN)

/* AC/DC Specifics: */

// #define AD8232_ACDC_DC 0 // Force AC/DC Low
// #define AD8232_ACDC_AC 1 // FOrce AC/DC High



/*
  Initialize the AD8232 Analog Heart Rate Monitor Front-End sensor
 

  ADC0 Used with Channel 6 (PB20)
   
 
  INPUTS: No Inputs, void function
  OUTPUTS: No outputs, void function
  
*/
void AD8232_Init(void);

/*
  Read the ECG signal from the AD8232.
 
 
  INPUTS: No Inputs, Void Function
  OUTPUTS: A 12-bit ADC value (0–4095) representing the ECG signal.

*/
uint16_t AD8232_ReadECG(void);


/*
  Checks if the ECG Leads are off
  Reads the Leads Off detection signals (LO+ and LO-) 

  INPUTS: None, void function
  OUTPUTS: Returns True if BOTH leads are OFF, and FALSE if they are attached

*/
bool AD8232_LeadsOff(void);




/*
  Displays the ECG or Leads Off message in the ST7735

  Function should be called periodically from the main loop so as to make sure the leads are attached   

  INPUTS: None, void function
  OUTPUTS: None; however, it displays a warning message on the ST7735 or Plots the data on there
*/
void AD8232_DisplayECG(void);






#endif /* AD8232_H */