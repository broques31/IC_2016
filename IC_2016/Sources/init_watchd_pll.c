/*
 * init_watchd_pll.c
 *
 *  Created on: Nov 14, 2016
 *      Author: Benjamin
 */

#include "MPC5645S.h"
#include "init_watchd_pll.h"

//désactivation du watchdog du microcontrôleur
void DISABLE_WATCHDOG()
{
	SWT.SR.R = 0x0000c520; /* Write keys to clear soft lock bit */ 
	SWT.SR.R = 0x0000d928; 
	SWT.CR.R = 0x8000010A; /* disable WEN */
}
//on configure l'entrée en mode RUN0, utilisation de la PLL0 (division par 2 pour générer l'horloge système, pas de division de l'horloge système vers les périph
//on utilise PLL0 comme auxiliary clock 0 = clock source du DCU. On ne divise pas cette clock auxiliaire.
void MC_MODE_INIT_PLL()
{
	ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
	//config de la PLL
	//NDIV = 50, IDF = '0000'--> 1, 0DF = '00' --> 2, clk_in = 8 MHz
	//PLL freq = clk_in*NDIV/(IDF*ODF) = 200 MHz, Fvco = clk_in*NDIV/IDF = 400 MHz (la fréquence du VCO doit rester entre 256 et 512 MHz)
	CGM.FMPLL[0].CR.B.IDF = 0;
	CGM.FMPLL[0].CR.B.ODF = 0;
	CGM.FMPLL[0].CR.B.NDIV = 50;
 	CGM.FMPLL[0].CR.B.EN_PLL_SW = 1; //activation PLL
   	CGM.OCDS_SC.B.SELCTL=2; //sélection de la PLL principale divisée par 2 comme horloge système
	/* Enbable all peripheral clocks */
	//registres SC_DC (p 218) : On active les diviseurs de sysclk pour les 4 sets de periph mais division  = 1. 
	//voir p 2013 - table 8.1 pour les 4 sets de périph.
	CGM.SC_DC[0].R = 0x80808080;
	CGM.SC_DC[1].R = 0x80808080;
	CGM.SC_DC[2].R = 0x80808080;
	CGM.SC_DC[3].R = 0x80808080;
	//Auxiliary clock 0 --> pour le DCU3.
	CGM.AC0_SC.B.SELCTL = 0x03; //PLL0 comme source d'horloge.
	CGM.AC0_DC.B.DE0 = 1; //activation du diviseur
	CGM.AC0_DC.B.DIV0 = 0; //Division par 1;
	//remarque : pour savoir si le DCU3 est actif, regardez le bit S_DCU3 du registre ME.ME_PS1.
	ME.RUN[0].R = 0x001F0064;     /* enable fxosc and FMPLL0, FMPLL0 est l'horloge système */ 
	/* Peri. Cfg. 1 settings: only run in RUN0 mode
	  Only RUNPC[0] mode configuration is defined. Only this configuration will be used.*/ 
	ME.RUNPC[0].R = 0x00000010;  //les périph fonctionnent uniquement en mode RUN0
    //Voir Table 29.2 p 1067 datasheet MPC5645S pour obtenir les numéros associés à chaque périphérique (à priori, les mêmes que MPC5604B).
    ME.PCTL[68].R = 0x00;  //SIUL use the configuration of RunPC[0]  
    ME.PCTL[92].R = 0x00;  //PIT0 use the configuration of RunPC[0]
    ME.PCTL[55].R = 0x00;  //DCU3 use the configuration of RunPC[0]
    ME.PCTL[63].R = 0x00;  //TCON use the configuration of RunPC[0]
	ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
	ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
	//la transition de mode exige ces 2 instructions avec la clé la 1e fois, puis la clé inversée. 									
	while (ME.GS.B.S_MTRANS) {}      
	while(ME.GS.B.S_CURRENTMODE != 4) {}  
}
