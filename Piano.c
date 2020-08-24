// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "delay.h"
#include "..//tm4c123gh6pm.h"

#define G    3189   // 784 Hz		
#define E   3792   // 659.3 Hz		
#define D   4259   // 587.3 Hz		
#define C    4780   // 1046.5 Hz		



// **************Piano_Init*********************
// Initialize piano key inputs
// Input: PE0-3
// Output: none

void Piano_Init(void){ 
	unsigned long volatile Edelay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;  //giving clock to portE
	Edelay= SYSCTL_RCGC2_R;
	GPIO_PORTE_DIR_R&=~(0x0F);   //making them input
	GPIO_PORTE_DEN_R|=0x0F;     //digital enable them
	
  
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  
  unsigned long Reading=GPIO_PORTE_DATA_R&0x0F;
	delay(10);
	
	if(Reading==1)
		return C;
	if(Reading==2)
		return D;
	if(Reading==4)
		return E;
	if(Reading==8)
			return G;
			
	
	
	
	
	return 0;
}
