/*
 * gpio.h
 *
 *  Created on: Nov 12, 2016
 *      Author: Benjamin
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "MPC5645S.h"

//global naming

//macro declaration

//functions prototypes
int Config_port_input(unsigned int port);
int Config_port_output(unsigned int port);
int Config_port_output_logical_inverted(unsigned int port);
int Set_GPIO(unsigned int port);
int Reset_GPIO(unsigned int port);
int Invert_GPIO(unsigned int port);
int Config_port_AF(unsigned int port, unsigned int AF_num);
uint8_t Read_GPIO(unsigned int port);
void Set_LEDS_Cluster(void);

#endif /* GPIO_H_ */
