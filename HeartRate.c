/*
* HeartRate.c
*
*  Created on: April 8th, 2025
*      Author: Georgios Adamopoulos
*/



#include "MAX30102.h"
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "MyTime.h"
#include <stdbool.h>
#include <stdint.h>
#include "HeartRate.h"
#include "AD8232.h"

#define minimumInterval 300

static uint32_t bpmBuffer[SIZE] = {0};
static uint8_t bpmBufferIndex = 0;

static uint32_t lastBeatTime = 0;
static bool beatInProgress = false;

bool checkForBeat(uint32_t ecgValue){
    bool beatDetected = false;

    if(!beatInProgress && (ecgValue >= THRESH)){
    
        beatDetected = true;
        beatInProgress = true;
    
    }
    else if (beatInProgress && (ecgValue < THRESH2)){
        
        beatInProgress = false; 
        
    }
    return beatDetected;

}

void processHeartRate(uint32_t ecgValue){
    if(checkForBeat(ecgValue)){
        int32_t currentTime = GetTimeinMilliseconds();
        if((currentTime - lastBeatTime) < minimumInterval){
            return;
        }
        if(lastBeatTime != 0){
            int32_t changeInTime = currentTime - lastBeatTime;
            if(changeInTime > minimumInterval){
                int32_t bpm = (int32_t)(60000/changeInTime);
                if(bpm > 20 && bpm < 255){
                    bpmBuffer[bpmBufferIndex] = bpm;
                    bpmBufferIndex = (bpmBufferIndex + 1) % SIZE;
                }
            }
        }
        lastBeatTime = currentTime;
    }
}

uint32_t getAverageBPM(void){
    uint32_t total = 0, i;
    for(i = 0; i < SIZE; i++){
        total += bpmBuffer[i];
    }
    return (uint32_t)(total/SIZE);
}
