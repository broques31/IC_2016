/*
 * dcu.h
 *
 *  Created on: Nov 14, 2016
 *      Author: Benjamin
 */

#ifndef DCU_H_
#define DCU_H_

#include "MPC5645S.h"

void CONFIG_DCU_IO(void);
void CONFIG_DCU(void);
void activ_DCU_Test(void);
void activ_DCU_Normal(void);
void InitLayers(void);

#endif /* DCU_H_ */
