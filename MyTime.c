/*
* MyTime.c
*
*  Created on: April 8th, 2025
*      Author: Georgios Adamopoulos
*/



#include "MyTime.h"
#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"  
#include "../inc/Timer.h"


// Global millisecond counter
uint32_t volatile  millisecondCounter = 0;

void TIMG8_IRQHandler(void){
    uint32_t dummy = TIMG8->CPU_INT.IIDX; // read to clear the flag
    if (dummy != 0) {
        millisecondCounter++;
    }
}


void MillisecTimer_Init(void){
    TimerG8_IntArm(500, 80, 2);
}

uint32_t GetTimeinMilliseconds(void) {
    return millisecondCounter;
}