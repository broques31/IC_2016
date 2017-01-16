/*
 * pit.c
 *
 *  Created on: Nov 25, 2016
 *      Author: Benjamin
 */

#include "MPC5645S.h"
#include "pit.h"

void Init_PIT(void)
{
	PIT.MCR.R = 0x00000001;	/* Enable PIT and configure to stop in debug mode */
	PIT.MCR.B.MDIS = 1; 	/*disable PIT module */
}

void Set_Counter_Value_PIT(uint8_t timer, uint32_t TimeOut) //count down and generate interrupt
{
	PIT.CH[timer].LDVAL.R = TimeOut; 	
}

void Start_PIT(uint8_t timer) 
{ 	
	PIT.CH[timer].TCTRL.B.TEN = 1;
	PIT.MCR.B.MDIS = 0; /*enable PIT module */
}

void Disable_PIT(uint8_t timer) 
{ 	
	PIT.CH[timer].TCTRL.B.TEN = 0;
}

void Autorize_IT_PIT(uint8_t timer) 
{ 	
	PIT.CH[timer].TCTRL.B.TIE = 1;
}

void Desautorize_IT_PIT(uint8_t timer) 
{ 	
	PIT.CH[timer].TCTRL.B.TIE = 0;
}

void Clear_Flag_PIT(uint8_t timer)
{
	//raz du flag interruption PITx
	PIT.CH[timer].TFLG.B.TIF = 1;
}
