#ifndef ADC0_H
#define ADC0_H

#include <stdint.h>
#include "ADC0.h"
#include "../inc/Clock.h"
#include "../inc/ADC.h"
#include "../inc/LaunchPad.h"

void ADC0init(void){
// write code to initialize ADC0 channel 6, PB20
// Your measurement will be connected to PB20
// 12-bit mode, 0 to 3.3V, right justified
// software trigger, no averaging
  ADC0->ULLMEM.GPRCM.RSTCTL = 0xB1000003; // 1) reset
  ADC0->ULLMEM.GPRCM.PWREN = 0x26000001;  // 2) activate
  Clock_Delay(24);                        // 3) wait
  ADC0->ULLMEM.GPRCM.CLKCFG = 0xA9000000; // 4) ULPCLK
  ADC0->ULLMEM.CLKFREQ = 7;               // 5) 40-48 MHz
  ADC0->ULLMEM.CTL0 = 0x03010000;         // 6) divide by 8
  ADC0->ULLMEM.CTL1 = 0x00000000;         // 7) mode
  ADC0->ULLMEM.CTL2 = 0x00000000;         // 8) MEMRES
  ADC0->ULLMEM.MEMCTL[0] = 6;             // 9) channel 6 is PB20
  ADC0->ULLMEM.SCOMP0 = 0;                // 10) 8 sample clocks
  ADC0->ULLMEM.CPU_INT.IMASK = 0;         // 11) no interrupt
}
uint16_t ADC0in(void){
  // write code to sample ADC0 channel 6, PB20 once
  // return digital result (0 to 4095)

  ADC0->ULLMEM.CTL0 |= 0x00000001;             // 1) enable conversions
  ADC0->ULLMEM.CTL1 |= 0x00000100;             // 2) start ADC
  uint32_t volatile delay = ADC0->ULLMEM.STATUS; // 3) time to let ADC start
  while((ADC0->ULLMEM.STATUS&0x01)==0x01){}    // 4) wait for completion
  
  
  return (uint16_t)ADC0->ULLMEM.MEMRES[0];               // 5) 12-bit result
  
}


#endif /* ADC0_H */