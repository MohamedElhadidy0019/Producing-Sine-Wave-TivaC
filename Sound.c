// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "Piano.h"
#include "delay.h"
#include "..//tm4c123gh6pm.h"

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
int Index;
void Sound_Init(void){
	DAC_Init();
	Index=0;
	//Setup Systick
	NVIC_ST_CTRL_R=0;
  NVIC_ST_RELOAD_R=1;
  NVIC_ST_CURRENT_R=0;
	//Setting Systick interrupt
  
  NVIC_SYS_PRI3_R= (NVIC_SYS_PRI3_R&0x0FFFFFFF) | 0x20000000;  //setting priority to 1
	NVIC_ST_CTRL_R=0x07; //changed it to enable interrupt
	
  
}
const unsigned short wave[32] = {	
  8,9,11,12,13,14,14,15,15,15,14,	
  14,13,12,11,9,8,7,5,4,3,2,	
  2,1,1,1,2,2,3,4,5,7};	


// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
	unsigned long theReload;
	theReload=0;
	NVIC_ST_CURRENT_R=0;
	
	theReload=Piano_In();
	if(theReload==0)
	{
		Sound_Off();
		
		return;
	}
	EnableInterrupts();
	NVIC_ST_RELOAD_R=theReload;
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	DisableInterrupts();
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	
	Index = (Index+1)&0x0FF;     
  DAC_Out(wave[Index]);    // output one value each interrupt
   
}
