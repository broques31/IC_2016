/*
 * gpio.c
 *
 *  Created on: Nov 12, 2016
 *      Author: Benjamin
 */

#include "gpio.h"
#include "MPC5645S.h"
#include "port.h"

//functions

//Configuration of PORT as an intput GPIO (no alternate function)
int Config_port_input(unsigned int port) 
{
	int error=-1;
	SIU.PCR[port].B.WPE = 0;
	SIU.PCR[port].B.WPS = 0;
	SIU.PCR[port].B.ODE= 0;
	SIU.PCR[port].B.PA = 0;
	SIU.PCR[port].B.OBE = 0;
	SIU.PCR[port].B.IBE = 1;
	error = 0;
	return error;
}

//Configuration of PORT as an output GPIO (no alternate function)
int Config_port_output(unsigned int port) 
{
    int error =-1;
    SIU.PCR[port].B.WPE = 1;
	SIU.PCR[port].B.WPS = 0;
	SIU.PCR[port].B.ODE= 0;
    SIU.PCR[port].B.SRC = 1;  //1.8 V low-power DDR full speed
	SIU.PCR[port].B.PA = 0;
	SIU.PCR[port].B.OBE = 1;
	SIU.PCR[port].B.IBE = 0;
	error = 0;
	return error;
}

//Configuration of PORT as an output GPIO, with inverted logic (no alternate function)
int Config_port_output_logical_inverted(unsigned int port)
{
	int error=-1;
	SIU.PCR[port].B.WPE = 1;
	SIU.PCR[port].B.WPS = 0;
	SIU.PCR[port].B.ODE= 1; 
	SIU.PCR[port].B.SRC = 1;  //1.8 V low-power DDR full speed
	SIU.PCR[port].B.PA = 0;
	SIU.PCR[port].B.OBE = 0;
	SIU.PCR[port].B.IBE = 0;
	error = 0;
	return error;
}

//Configuration of PORT in alternate function number AF_num
int Config_port_AF(unsigned int port, unsigned int AF_num) 
{
    int error =-1;
	if (1 <= AF_num && 3 >= AF_num)
	{
		SIU.PCR[port].B.PA = AF_num;
		error = 0;
	}
	else
	{
		error = 1;
	}
	return error;
}

// Set an output PORT
int Set_GPIO(unsigned int port)
{
	int error=-1;
	SIU.GPDO[port].B.PDO = 1;
	error = 0;
	return error;
}

// Reset an output PORT
int Reset_GPIO(unsigned int port)
{
	int error=-1;
	SIU.GPDO[port].B.PDO = 0;
	error = 0;
	return error;
}

// Invert the state of an output PORT
int Invert_GPIO(unsigned int port)
{
	int error=-1;
	SIU.GPDO[port].B.PDO = ~SIU.GPDO[port].B.PDO;
	error = 0;
	return error;
}

// Read the content of an input PORT
uint8_t Read_GPIO(unsigned int port)
{
	return SIU.GPDI[port].B.PDI;	
}

void Set_LEDS_Cluster()
{
	  //config des sorties voyants + rétroéclairage tableaude bord et aiguilles
	  
	  Config_port_output(PC1);
	  Config_port_output(PC2);
	  Config_port_output(PC3);
	  Config_port_output(PK11);  
	  Config_port_output(PK4);
	  Config_port_output(PK5);
	  Config_port_output(PK2);
	  Config_port_output(PK3);
	  Config_port_output(PK6);
	  Config_port_output(PK10);
	  Config_port_output(PF5);
	  Config_port_output(PF1);
	  Config_port_output(PF3);
	  Config_port_output(PF4);
	  Config_port_output(PF5);
	  Config_port_output(PF6);
	  Config_port_output(PM7);
	  Config_port_output(PB7);
	  //Pour PJ3 et PJ7
	  Config_port_output_logical_inverted(PJ3);
	  Config_port_output_logical_inverted(PJ7); 
	  
	  //allumage voyants 
	  //voyant airbag (PC1 et PB7)
	  Set_GPIO(PC1);
	  Set_GPIO(PB7);
	  
	  //voyant feu de route (PK11)
	  Set_GPIO(PK11);
	  
	  //voyants cligno droite et gauche (PK6 + PC2 et PC3)
	  Set_GPIO(PK6);
	  Set_GPIO(PC2);
	  Set_GPIO(PC3);
	  
	  //voyants ESP (PK4 + PC3)
	  Set_GPIO(PK4);
	  
	  //voyants défaillance des freins (PK3 + PC3) et voyants ceintures non bouclées (PK3 + PC2)
	  Set_GPIO(PK3);
	  
	  //voyants autodiagnostic (PK5 + PC2)
	  Set_GPIO(PK5);
	  
	  //voyants feu de position (PM7 + PC3)
	  Set_GPIO(PM7);
	  
	  //voyants insuffisance batterie (PF3 + PC2)
	  Set_GPIO(PF3);
	  
	  
	  //Allumage retroéclairage tableau de bord
	  Set_GPIO(PJ3);
	  //Allumage retroéclairage des aiguilles
	  Set_GPIO(PJ7);
}
