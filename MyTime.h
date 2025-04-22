/*
 * MyTime.h
 *
 *  Created on: April 7th, 2025
 *      Author: Georgios Adamopoulos
 */

#ifndef MyTime_H
#define MyTime_H

#include <stdint.h>

// initialize timerG8 for interrupts 
void MillisecTimer_Init(void);



uint32_t GetTimeinMilliseconds(void);



#endif /* MyTime_H */