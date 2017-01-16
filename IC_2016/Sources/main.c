/*
 * main.c
 *
 *  Created on: Nov 12, 2016
 *      Author: Benjamin
 */

#include "MPC5645S.h"
#include "init_watchd_pll.h"
#include "IntcInterrupts.h"

#include "can_dictionnary.h"
#include "port.h"
#include "gpio.h"

#include "pit.h"
#include "lcd.h"
#include "dcu.h"
#include "step_motors.h"
#include "spi_can.h"
#include "sbc.h"

/* FUNCTION PROTOTYPES */
void enableIrq(void);
void PIT_CH0_ISR(void);
void PIT_CH1_ISR(void);
void PIT_CH2_ISR(void) ;

/* GLOBAL VARIABLES */
// Step motors structures.
struct StepMotor speedIndicator ;
struct StepMotor rpmIndicator ;
struct StepMotor oilIndicator ;
struct StepMotor temperatureIndicator ;

// Step motors pointers.
struct StepMotor* ptrSpeedIndicator = &speedIndicator ;
struct StepMotor* ptrRpmIndicator = &rpmIndicator ;
struct StepMotor* ptrOilIndicator = &oilIndicator ;
struct StepMotor* ptrTemperatureIndicator = &temperatureIndicator ;

// Indicates if cluster initialisation is done.
int init = 0 ;

// Test code for step motors
int valSpeed = 0 ;
int sensSpeed = 0 ;
int valRPM = 0 ;
int sensRPM = 0 ;
int valOil = 0 ;
int sensOil = 0 ;
int valTemperature = 0 ;
int sensTemperature = 0 ;

// variable autorisation CAN
//int IT_CAN_autorisee = 0;

/* MAIN FUNCTION */

int main(void) {
  
  volatile int i = 0;
  
  DISABLE_WATCHDOG();
  MC_MODE_INIT_PLL();   //mode Run0, utilisation de la PLL principale tournant à 200 MHz, bus systeme 100 Mhz
  enableIrq();
  
  // SMC initialisation.
  initSMC() ;
  
  // Init CAN
  // initialise_SPI_DRIVER();
  // SPI[1].init(SPI_BAUD_62500, SPI_DELAY_DEFAULT);
  // Init_SBC_DBG();
  // initCAN1();
  
   // Step motors creation
  setParameters(ptrSpeedIndicator, PD0, PD1, PD2, PD3, 0, 1,
					MIN_SPEED_INDICATOR, MAX_SPEED_INDICATOR,
					LOGIC_SPEED_INDICATOR, FULL_SCALE_SPEED_INDICATOR, OFFSET_SPEED_INDICATOR) ;
  setParameters(ptrRpmIndicator, PD4, PD5, PD6, PD7, 2, 3,
					MIN_RPM_INDICATOR, MAX_RPM_INDICATOR,
					LOGIC_RPM_INDICATOR, FULL_SCALE_RPM_INDICATOR, OFFSET_RPM_INDICATOR) ;
  setParameters(ptrOilIndicator, PD8, PD9, PD10, PD11, 4, 5,
					MIN_OIL_INDICATOR, MAX_OIL_INDICATOR,
					LOGIC_OIL_INDICATOR, FULL_SCALE_OIL_INDICATOR, OFFSET_OIL_INDICATOR) ;
  setParameters(ptrTemperatureIndicator, PD12, PD13, PD14, PD15, 6, 7,
					MIN_TEMPERATURE_INDICATOR, MAX_TEMPERATURE_INDICATOR,
					LOGIC_TEMPERATURE_INDICATOR, FULL_SCALE_TEMPERATURE_INDICATOR, OFFSET_TEMPERATURE_INDICATOR) ;
		
  // Step motors initialisation
  initStepMotor(ptrSpeedIndicator) ;
  initStepMotor(ptrRpmIndicator) ;
  initStepMotor(ptrOilIndicator) ;
  initStepMotor(ptrTemperatureIndicator) ;
  
  // Microstep timer
  Set_Counter_Value_PIT(TIMER_SMC, MICROSTEP_TIME) ;
  Start_PIT(TIMER_SMC) ;
  Autorize_IT_PIT(TIMER_SMC) ;
  
  // Mode demonstration LCD
  //affichage bienvenu 5s + clignotement image vitres 0.5s
  Set_Counter_Value_PIT(TIMER0,0x1DCD6500); // compte à rebours 5s, cadencé à 200MHz
  Set_Counter_Value_PIT(TIMER2,0x2160EC0); // compte à rebours 0.35s, cadencé à 200MHz
  Start_PIT(TIMER0);
  Start_PIT(TIMER2);
  //le compte à rebours de 5s est lancé à la mise sous contact
  Autorize_IT_PIT(TIMER0);
  //IT TIMER2 autorisee au sein de l'IT TIMER0 pour le mode demo
  //initialisation DCU
  Set_LEDS_Cluster();
  InitLayerMemory();
  InitLayers();
  CONFIG_DCU();
  CONFIG_DCU_IO();
  DCU.DCU_MODE.B.RASTER_EN = 0; //arrêt du balayage de pixel
  activ_DCU_Normal();

  //mode normal LCD
/*affichage bienvenu 5s
  Set_Counter_Value_PIT(TIMER0,0x1DCD6500); // compte à rebours 5s, cadencé à 200MHz
  Start_PIT(TIMER0);
  Autorize_IT_PIT(TIMER0);
  // IT TIMER2 autorisee au sein de l'IT fictive gestion message CAN
  //initialisation voyants
  Config_port_output(PC2);
  Config_port_output(PF5); // temoin d'incident jaune
  Config_port_output(PF3); // temoin probleme batterie
  //initialisation DCU
  InitLayerMemory();
  InitLayers();
  CONFIG_DCU();
  CONFIG_DCU_IO();
  DCU.DCU_MODE.B.RASTER_EN = 0; //arrêt du balayage de pixel
  activ_DCU_Normal();
*/  

  for (;;) {
    i++;    
  }
}

// autorisation interruptions
void enableIrq(void) {
  INTC.CPR.B.PRI = 0;          /* Single Core: Lower INTC's current priority */
  asm("wrteei 1");	    	   /* Enable external interrupts */
  //autorisation des interruptions liées aux timers 0 et 2
  INTC_InstallINTCInterruptHandler(PIT_CH0_ISR,59, 10) ; //function, PSR, priority
  INTC_InstallINTCInterruptHandler(PIT_CH1_ISR, 60, 1) ; // Enable TIMER 1 interrupt and set priority
  INTC_InstallINTCInterruptHandler(PIT_CH2_ISR,61, 5);//function, PSR, priority
}

//IT pour maintenir l'image FORD de bienvenu 5s
void PIT_CH0_ISR(void){
	int i;
	Clear_Flag_PIT(TIMER0);//effacement flag pour pouvoir derouler le code de l'IT sans encombre
	Desautorize_IT_PIT(TIMER0); //on le desactive pour ne pas tourner en boucle dans cette IT
	DCU.LAYER[0].CTRLDESCL4.B.EN = 0; //au bout des 5s, disparition image de bienvenu FORD
	//background color: passage au fond de couleur blanc en dehors image de bienvenu
	DCU.BGND.B.BGND_R = 0xFF;
	DCU.BGND.B.BGND_G = 0xFF;
	DCU.BGND.B.BGND_B = 0xFF;
    //apparition image bird view eye
	DCU.LAYER[11].CTRLDESCL4.B.EN = 1;
	//int IT_CAN_autorisee = 1; //ce n'est que maintenant que j'autorise les IT en provenance du CAN
 /*************************************************************************************************/
	//ARRET IT ICI POUR LE MODE NORMAL LCD
	//pour le mode demonstration LCD >>
	//affichage de toutes les images
	DCU.LAYER[2].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[3].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[4].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[5].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[6].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[7].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[8].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[9].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[10].CTRLDESCL4.B.EN = 1;
	
	// Initialisation terminée pour les moteurs
	init = 1 ;
	resetCurrentStep(ptrSpeedIndicator) ;
	resetCurrentStep(ptrRpmIndicator) ;
	resetCurrentStep(ptrOilIndicator) ;
	resetCurrentStep(ptrTemperatureIndicator) ;
	
	//delay
	for(i=0; i<45000000; i++){}
	
	//extinction de toutes les images
	DCU.LAYER[11].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[2].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[3].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[4].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[5].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[6].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[7].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[8].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[9].CTRLDESCL4.B.EN = 0;
	DCU.LAYER[10].CTRLDESCL4.B.EN = 0;
	//apparition des images une a une avec un petit delai entre chaque image
	for(i=0; i<4500000; i++){}
	DCU.LAYER[11].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[2].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[3].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[4].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[7].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[8].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[9].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[10].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[5].CTRLDESCL4.B.EN = 1;
	for(i=0; i<4500000; i++){}
	DCU.LAYER[6].CTRLDESCL4.B.EN = 1;
	for(i=0; i<9000000; i++){}
	
	// clignotement images vitres
	Autorize_IT_PIT(TIMER2); 
}


/** 
 * TIMER 1 HANDLER. USED TO CONTROL ALL THE STEP MOTORS.
 *
 * @param 	None.	
 * @return	None.
 */
void PIT_CH1_ISR(void) {
	
	Clear_Flag_PIT(TIMER_SMC) ;
	
	if (init == 0) {
		// During initialisation, the 4 needles are reseted.
		calibrate(ptrSpeedIndicator) ;
		calibrate(ptrRpmIndicator) ;
		calibrate(ptrOilIndicator) ;
		calibrate(ptrTemperatureIndicator) ;
	}
	else {
		// After initialisation, all step motors are continuously updated.
		update(ptrSpeedIndicator) ;
		update(ptrRpmIndicator) ;
		update(ptrOilIndicator) ;
		update(ptrTemperatureIndicator) ;
		
		/*** TEST CODE ***/
		
		// Update test values
		if (sensSpeed == 1) {
			valSpeed++ ;
		}
		else {
			valSpeed-- ;
		}
		
		if (sensRPM == 1) {
			valRPM = valRPM + 100 ;
		}
		else {
			valRPM = valRPM - 100 ;
		}
		
		if (sensOil == 1) {
			valOil++ ;
		}
		else {
			valOil-- ;
		}
		
		if (sensTemperature == 1) {
			valTemperature++ ;
		}
		else {
			valTemperature-- ;
		}
		
		// Update direction
		if (isAtMinimum(ptrSpeedIndicator)) {
			sensSpeed = 1 ;
		}
		if (isAtMaximum(ptrSpeedIndicator)) {
			sensSpeed = 0 ;
		}
		
		if (isAtMinimum(ptrRpmIndicator)) {
			sensRPM = 1 ;
		}
		if (isAtMaximum(ptrRpmIndicator)) {
			sensRPM = 0 ;
		}
		
		if (isAtMinimum(ptrOilIndicator)) {
			sensOil = 1 ;
		}
		if (isAtMaximum(ptrOilIndicator)) {
			sensOil = 0 ;
		}
		
		if (isAtMinimum(ptrTemperatureIndicator)) {
			sensTemperature = 1 ;
		}
		if (isAtMaximum(ptrTemperatureIndicator)) {
			sensTemperature = 0 ;
		}
		
		setOrder(ptrSpeedIndicator, valSpeed) ;
		setOrder(ptrRpmIndicator, valRPM) ;
		setOrder(ptrOilIndicator, valOil) ;
		setOrder(ptrTemperatureIndicator, valTemperature) ;
	}
}

//IT pour faire clignoter les images vitre lorsqu'elles sont en fermeture
void PIT_CH2_ISR(void){
	
	Clear_Flag_PIT(TIMER2); //effacement flag pour pouvoir derouler le code de l'IT sans encombre
	
	//clignotement images vitres toutes les 0.35s
	DCU.LAYER[5].CTRLDESCL4.B.EN = ~DCU.LAYER[5].CTRLDESCL4.B.EN;
	DCU.LAYER[6].CTRLDESCL4.B.EN = ~DCU.LAYER[6].CTRLDESCL4.B.EN;
}

/*IT gestion message CAN pour le mode normal LCD
 * sur reception des messages CAN, on affiche les 
 * icones en conséquence sur le LCD et on allume
 * les bons voyants
 * voir "can_dictionnary.h"
*/
/*
void Interrupt_Rx_CAN1 (){
	 uint8_t message_recu;
	 if (IT_CAN_autorisee){
	 	 message_recu = ReceiveMsg();
		 switch (message_recu){
			 case(porte_G_verrouillee):
				 DCU.LAYER[2].CTRLDESCL4.B.EN = 1;
				 break;
			 case(porte_G_deverouille):
				 DCU.LAYER[2].CTRLDESCL4.B.EN = 0;
				 break;
			 case(porte_D_verrouillee):
				 DCU.LAYER[3].CTRLDESCL4.B.EN = 1;
				 break;
			 case(porte_D_deverouille):
				 DCU.LAYER[3].CTRLDESCL4.B.EN = 0;
				 break;
			 case(antihijacking_active):
				 DCU.LAYER[4].CTRLDESCL4.B.EN = 1;
				 break;
			 case(antihijacking_desactive):
				 DCU.LAYER[4].CTRLDESCL4.B.EN = 0;
				 break;	
			 case(vitre_G_fermee):
				 Desautorize_IT_PIT(TIMER2);
				 DCU.LAYER[5].CTRLDESCL4.B.EN = 0;
				 break;
			 case(vitre_G_ouverte):
				 Desautorize_IT_PIT(TIMER2);
				 DCU.LAYER[5].CTRLDESCL4.B.EN = 1;
				 break;
			 case(vitre_D_fermee):
				 Desautorize_IT_PIT(TIMER2);
				 DCU.LAYER[6].CTRLDESCL4.B.EN = 0;
				 break;
			 case(vitre_D_ouverte):
				 Desautorize_IT_PIT(TIMER2);
				 DCU.LAYER[6].CTRLDESCL4.B.EN = 1;
				 break;
			 case(vitres_en_fermeture):
				 Autorize_IT_PIT(TIMER2);
				 break;
			 case(probleme_porte_G):
				 DCU.LAYER[9].CTRLDESCL4.B.EN = 1;
				 Set_GPIO(PF5);
				 break;
			 case(pas_probleme_porte_G):
				 DCU.LAYER[9].CTRLDESCL4.B.EN = 0;
				 Reset_GPIO(PF5);
				 break;
			 case(probleme_porte_D):
				 DCU.LAYER[10].CTRLDESCL4.B.EN = 1;
				 Set_GPIO(PF5);
				 break;
			 case(pas_probleme_porte_D):
				 DCU.LAYER[10].CTRLDESCL4.B.EN = 0;
				 Reset_GPIO(PF5);
				 break;
				 Reset_GPIO(PF5);
			 case(probleme_vitre_G):
				 DCU.LAYER[5].CTRLDESCL4.B.EN = 1;
				 DCU.LAYER[9].CTRLDESCL4.B.EN = 1;
				 Set_GPIO(PF5);
				 break;
			 case(pas_probleme_vitre_G):
				 DCU.LAYER[5].CTRLDESCL4.B.EN = 0;
				 DCU.LAYER[9].CTRLDESCL4.B.EN = 0;
				 Reset_GPIO(PF5);
				 break;
			 case(probleme_vitre_D):
				 DCU.LAYER[6].CTRLDESCL4.B.EN = 1;
				 DCU.LAYER[10].CTRLDESCL4.B.EN = 1;
				 Set_GPIO(PF5);
				 break;
			 case(pas_probleme_vitre_D):
				 DCU.LAYER[6].CTRLDESCL4.B.EN = 0;
				 DCU.LAYER[10].CTRLDESCL4.B.EN = 0;
				 Reset_GPIO(PF5);
				 break;
			 case(pincement_vitre_G):
				 DCU.LAYER[7].CTRLDESCL4.B.EN = 1;
				 break;
			 case(pas_pincement_vitre_G):
				 DCU.LAYER[7].CTRLDESCL4.B.EN = 0;
				 break;
			 case(pincement_vitre_D):
				 DCU.LAYER[8].CTRLDESCL4.B.EN = 1;
				 break;
			 case(pas_pincement_vitre_D):
				 DCU.LAYER[8].CTRLDESCL4.B.EN = 0;
				 break;
			 case(probleme_batterie):
				 Set_GPIO(PF3);
				 break;
			 case(pas_probleme_batterie):
				 Reset_GPIO(PF3);
				 break;
			 default :
				 Set_GPIO(PK10);
				 break;
		 }
	 }
}
*/
