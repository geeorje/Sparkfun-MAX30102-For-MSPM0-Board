/*
 * HeartRate.h
 *
 *  Created on: April 7th, 2025
 *      Author: Georgios Adamopoulos
 */
    
#ifndef HeartRate_H
#define HeartRate_H


#include <stdint.h>
#include <stdbool.h>
#include "AD8232.h"

#define SIZE 50
#define THRESH 500
#define THRESH2 450
/*
    Process the infared sample from the IR LED on the sensor

    checkForBeat checks if the sample is a rising edge
    based on a threshold. keeps a static previous sample 
    for edge detection

    input: raw IR sample from the sensor
    output: return a TRUE if beat is detected, False otherwise

*/ 
bool checkForBeat(uint32_t ecgValue);



/*
    After detecting a beat (above function), processHeartRate calculates the 
    time difference between the last detected beat, computes Beats per Minute
    and stores it in a FIFO buffer (circular array)

    input: raw IR data sample
    output: nothing

*/
void processHeartRate(uint32_t ecgValue);
    


/*
    basically just calculates the average beats per minute
    after processing the heart rate and BPM

    inputs: nothing
    output: average BPM (beats per minute)

*/   
uint16_t getAverageBPM(void);


#endif /* HeartRate_H */