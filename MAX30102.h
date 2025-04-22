/*
 * MAX30102.h
 *
 *  Created on: April 7th, 2025
 *      Author: Georgios Adamopoulos
 */



#ifndef MAX30102_H
#define MAX30102_H

#include <stdint.h>


#define MAX30102_ADDRESS 0x57 // right shift address from data sheet bc I2C.c shifts it by 1
// Actual address is Write is 0xAE and Read is 0xAF, so i can just add one when i shift left

#define MAX30102_FIFO_DATA_REG 0x07 // the FIFO data register vals' address is at 0x07 according to data sheet

// Initialize the MAX30102 High Sensitivity Pulse Oximeter and Heart-Rate sensor for wearable health
void MAX30102_Init(void);




/*
    Reads Data sample from the Device's FIFO Data Register
    Reads 3 bytes from the sensor which becomes one 32 bit value, hence uint32_t

    INPUTS: No inputs, void function
    OUTPUTS: unsigned 32 bit value containing two bytes of data from sensor, but is actually 18 bits of info
            
    Note: this is just raw data, to analyze further, you need to do some extra steps
*/
uint32_t MAX30102_ReadFIFO(void);


/*
    Clears the FIFO Pointers as specified by the Datasheet

    INPUTS: No inputs, void function
    OUTPUTS: No Outputs, void function

*/  
void MAX30102_ClearFIFO(void);


#endif /* MAX30102_H */