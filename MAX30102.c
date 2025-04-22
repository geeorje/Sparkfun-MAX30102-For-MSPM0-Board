/*
* MAX30102.c
*
*  Created on: April 7th, 2025
*      Author: Georgios Adamopoulos
*/



#include "MAX30102.h"
#include "I2C.h"
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"


// From Datasheet:
//      Register Names       Register Addresses    Use
#define FIFO_Data_Register   0x07                  // FIFO Data Register
#define FIFO_Config_Register 0x08                  // FIFO Configuration Register
#define Mode_Config_Register 0x09                  // Mode Configuration Register
#define SP02_Config_Register 0x0A                  // SP02 Configuration Register
#define LED1_Register        0x0C                  // LED1 Pulse Amplitude (Red led)
#define LED2_Register        0x0D                  // LED2 Pulse Amplitude (IR LED)
#define Temp_Int_Reg         0x1F                  // Die Temperature Integer Register
#define Temp_Frac_Reg        0x20                  // Die Temperature Fraction Register
// change the pins for the I2C


// initilize the senspr
void MAX30102_Init(void){

    


    // reset sensor by writing to the mode configure register
    // write a 0x40 because that is where the register's reset bit is   
    // if it returns an error, just repeat the process
    while(I2C_Send2(MAX30102_ADDRESS, Mode_Config_Register, 0x40) != 0){}
    
    //delay
    Clock_Delay(24); // time for this to finish (taken from I2C.c)
    
    // Clear FIFO Pointers  
    MAX30102_ClearFIFO();


    // Configure SP02 settings
    // Bits 6 and 5 are the ADC Range Control (18-bit Resolution)
    // Bits 2, 3 and 4 are Sample Control
    // Bits 0 and 1 are Pulse Width Control for LEDs
    // In this case, I use 00 for ADC Full Scale Range, 001 for Sample Rate, and 01 for Pulse Width 
    while(I2C_Send2(MAX30102_ADDRESS, SP02_Config_Register, 0x05)){}

    // Set the LED Amplitudes 
    // RED LED
    while(I2C_Send2(MAX30102_ADDRESS, LED1_Register, 0x32)){}
    
    // Infared LED
    while(I2C_Send2(MAX30102_ADDRESS, LED2_Register, 0x32)){}

    // Configure FIFO Settings
    // use 0x0F for the FIFO Averaging and the Sample Count, etc
    // Evreything is stated in the data sheet
    // i hope its right...
    while(I2C_Send2(MAX30102_ADDRESS, FIFO_Config_Register, 0x0F)){}

}

// recieve the three bytes from the FIFO register 
// then mask and use only 18 bits
// Dont w   orry about adjusting to get read register bc its in the code for I2C
uint32_t MAX30102_ReadFIFO(void){

    uint8_t byte1, byte2, byte3;

    // read three bytes
    // bytes are left justified so:
    // Byte 1 will have only the first two bits (FIFO_DATA[17] and FIFO_DATA[16])
    // Byte 2 will have FIFO_DATA[8] through FIFO_DATA[15]
    // Byte 3 will have FIFO_DATA[0] through FIFO_DATA[7]
    byte1 = I2C_Recv1(MAX30102_ADDRESS);
    byte2 = I2C_Recv1(MAX30102_ADDRESS);
    byte3 = I2C_Recv1(MAX30102_ADDRESS);


    // shift it all into one variable and mask to get good shifts
    uint32_t data = (((uint32_t)byte1<<16)  | ((uint32_t)byte2<<8) | byte3);


    // mask to get only 18 bits
    data &= 0x3FFFF;


    // return the value
    return data;

}


void MAX30102_ClearFIFO(void){
    // Write 0x00 to FIFO_WR_PTR register (address 0x04)
    while(I2C_Send2(MAX30102_ADDRESS, 0x04, 0x00) != 0) {}
    
    // Write 0x00 to OVF_COUNTER register (address 0x05)
    while(I2C_Send2(MAX30102_ADDRESS, 0x05, 0x00) != 0) {}
    
    // Write 0x00 to FIFO_RD_PTR register (address 0x06)
    while(I2C_Send2(MAX30102_ADDRESS, 0x06, 0x00) != 0) {}
}
