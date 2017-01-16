/*
 * pit.h
 *
 *  Created on: Nov 25, 2016
 *      Author: Benjamin
 */

#ifndef PIT_H_
#define PIT_H_

#include "MPC5645S.h"

#define TIMER0	0
#define TIMER1  1
#define TIMER2  2

void Init_PIT(void);
void Set_Counter_Value_PIT(uint8_t timer, uint32_t TimeOut);
void Start_PIT(uint8_t timer);
void Disable_PIT(uint8_t timer);
void Autorize_IT_PIT(uint8_t timer);
void Desautorize_IT_PIT(uint8_t timer);
void Clear_Flag_PIT(uint8_t timer);

#endif /* PIT_H_ */
