/*
 * step_motors.c
 *
 * Created on: Nov 4, 2016
 * Author: Ludovic Lesur
 */

#include "step_motors.h"
#include "MPC5645S.h"
#include "port.h"

/** 
 * CONFIGURE A PIN FOR USING SMC MODULE.
 *
 * @param pin	Pin of the MPC5645S to configure.
 * @return		None.
 */
void configurePin(int pin) {
	SIU.PCR[pin].R = 0x600 ;
}

/** 
 * SET PARAMETERS OF A STEP MOTOR STRUCTURE.
 *
 * @param motor			Pointer to the step motor structure to configure.
 * @param pC0M			Pin 1 controlling the step motor.
 * @param pC0M			Pin 2 controlling the step motor.
 * @param pC0M			Pin 3 controlling the step motor.
 * @param pC0M			Pin 4 controlling the step motor.
 * @param pChannelA		Channel A driving pins 1 and 2.
 * @param pChannelB		Channel B driving pins 3 and 4.
 * @param pValueMin		Minimum value indicated by the associated needle.
 * @param pValueMax		Maximum value indicated by the associated needle.
 * @return				None.
 */
void setParameters(struct StepMotor* motor,
			int pC0M,
			int pC0P,
			int pC1M,
			int pC1P,
			int pChannelA,
			int pChannelB,
			int pValueMin,
			int pValueMax,
			int pLogic,
			unsigned int pStepsToMax,
			unsigned int pOffset) {
	(*motor).C0M = pC0M ;
	(*motor).C0P = pC0P ;
	(*motor).C1M = pC1M ;
	(*motor).C1P = pC1P ;
	(*motor).channelA = pChannelA ;
	(*motor).channelB = pChannelB ;
	(*motor).valueMin = pValueMin ;
	(*motor).valueMax = pValueMax ;
	(*motor).logic = pLogic ;
	(*motor).stepsToMax = pStepsToMax ;
	(*motor).offset = pOffset ;
}

/** 
 * INITIALISATION OF SMC MODULE FOR ALL STEP MOTORS.
 *
 * @param	None.
 * @return	None.
 */
void initSMC() {
	// SMC general configuration
	SMC.CTL0.B.MCPRE = 2 ; // Motor controller prescaler = fBus/4
	SMC.CTL0.B.DITH = 0 ; // Dither function disabled
	SMC.CTL1.B.RECIRC = 1 ; // PWM output logic low
	SMC.CTL1.B.MCTOIE = 1 ; // Overflow interrupt enabled
	SMC.PER.R = 0x400 ; // Counter for PWM frequency
}

/** 
 * INITIALISATION OF A STEP MOTOR STRUCTURE AND THE CORRESPONDING SMC CHANNELS.
 *
 * @param motor		Pointer to the step motor structure to initialise.		
 * @return			None.
 */
void initStepMotor(struct StepMotor* motor) {
	// Structure members
	(*motor).bottomCalib = 0 ;
	(*motor).topCalib = 0 ;
	(*motor).ready = 0 ;
	if ((*motor).logic == 0) {
		(*motor).currentStep = 0 ;
		(*motor).stepOrder = 0 ;
	}
	else {
		(*motor).currentStep = (*motor).stepsToMax ;
		(*motor).stepOrder = (*motor).stepsToMax ;
	}
	// Pin configuration
	configurePin((*motor).C0M) ;
	configurePin((*motor).C0P) ;
	configurePin((*motor).C1M) ;
	configurePin((*motor).C1P) ;
	// SMC channel 1
	SMC.CC[(*motor).channelA].B.MCOM = 3 ; // Dual full H-bridge mode
	SMC.CC[(*motor).channelA].B.MCAM = 1 ; // PWM alignement mode = left
	SMC.CC[(*motor).channelA].B.CD = 0 ; // No delay
	// SMC channel 2
	SMC.CC[(*motor).channelB].B.MCOM = 3 ; // Dual full H-bridge mode
	SMC.CC[(*motor).channelB].B.MCAM = 1 ; // PWM alignement mode = left
	SMC.CC[(*motor).channelB].B.CD = 0 ; // No delay
}

/** 
 * CALIBRATES A STEP MOTOR USING STALL DETECTION.
 *
 * @param motor		Pointer to the step motor structure to calibrate.		
 * @return			None.
 */
int calibrate(struct StepMotor* motor) {
	
	/* Version requiring the Stall Detection

	// Find bottom position
	if ((*motor).bottomCalib == 0) {
		decrease(motor) ;
		//if () { // Stall detection
			(*motor).bottomCalib = 1 ;
		//}
	}
	else {
		// Find top position and calculate stepsToTop
		if ((*motor).topCalib == 0) {
			increase(motor) ;
			// Save the number of steps to attain maximum height
			(*motor).stepsToMax ++ ;
			//if () { // Stall detection
			(*motor).topCalib = 1 ;
			//}
		}
		else {
			// Return to bottom position
			if ((*motor).ready == 0) {
				decrease(motor) ;
				//if () { // Stall detection
					(*motor).ready = 1 ;
					(*motor).currentStep = 0 ;
				//}
			}
		}
	} 
	// The boolean 'ready' can be used in the main function to wait for calibration end. */
	
	
	/* Version without calibration */
	
	decrease(motor) ;
	
	return (*motor).ready ;
}

/** 
 * RESETS CURRENT STEP NUMBER (CALLED AT THE END OF CALIBRATION).
 *
 * @param motor		Pointer to the step motor structure to calibrate.		
 * @return			None.
 */
void resetCurrentStep(struct StepMotor* motor) {
	if ((*motor).logic == 0) {
		(*motor).currentStep = 0 ;
	}
	else {
		(*motor).currentStep = (*motor).stepsToMax ;
	}
}

/** 
 * CALCULATES THE STEP TO ATTAIN ACCORDING TO A GIVEN PHYSICAL VALUE.
 *
 * @param motor				Pointer to the step motor structure to configure.
 * @param physicalValue		Value to be indicated by the needle.
 * @return					None.
 */
void setOrder(struct StepMotor* motor, float physicalValue) {
	float v = physicalValue ;
	float min = (float) (*motor).valueMin ;
	float max = (float) (*motor).valueMax ;
	float offset = (float) (*motor).offset ;
	float stepMax = (float) (*motor).stepsToMax ;
	float stepNumber = 0.0 ;
	
	// Protects the function against an incorrect value
	if (physicalValue <= min) {
		v = min ;
	}
	if (physicalValue >= max) {
		v = max ;
	}
	
	if ((*motor).logic == 0) {
		stepNumber = ((stepMax*(v-min))/(max-min))+offset ;
	}
	else {
		stepNumber = ((stepMax*(v-max))/(min-max))-offset ;
	}
	(*motor).stepOrder = (unsigned int) stepNumber ;
}

/** 
 * INCREASES NEEDLE POSITION USING A MICROSTEP. 
 *
 * @param motor		Pointer to the step motor structure to make move.		
 * @return			None.
 */
void increase(struct StepMotor* motor) {
	if ((*motor).logic == 0) {
		(*motor).currentStep ++ ;
	}
	else {
		(*motor).currentStep -- ;
	}
	microstep(motor) ;
}

/** 
 * DECREASES NEEDLE POSITION USING A MICROSTEP. 
 *
 * @param motor		Pointer to the step motor structure to make move.	
 * @return			None.
 */
void decrease(struct StepMotor* motor) {
	if ((*motor).logic == 0) {
		(*motor).currentStep -- ;
	}
	else {
		(*motor).currentStep ++ ;
	}
	microstep(motor) ;
}

/** 
 * CALCULATES THE PWM SIGNAL SENT TO THE STEP MOTOR.
 *
 * @param motor		Pointer to the step motor structure to make move.		
 * @return			None.
 */
void microstep(struct StepMotor* motor) {
	unsigned int microstep = ((*motor).currentStep) % NUMBER_OF_MICROSTEPS ;
	// Alter duty cycle
	switch (microstep) {
	case 0 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x400 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x0 ;
		break ;
	case 1 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x300 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x100 ;
		break ;
	case 2 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x200 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x200 ;
		break ;
	case 3 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x100 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x300 ;
		break ;
	case 4 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x0 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x400 ;
		break ;
	case 5 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x100 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x300 ;
		break ;
	case 6 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x200 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x200 ;
		break ;
	case 7 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x300 ;
		SMC.DC[(*motor).channelB].B.SIGN = 0 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x100 ;
		break ;
	case 8 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x400 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x0 ;
		break ;
	case 9 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x300 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x100 ;
		break ;
	case 10 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x200 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x200 ;
		break ;
	case 11 :
		SMC.DC[(*motor).channelA].B.SIGN = 1 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x100 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x300 ;
		break ;
	case 12 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x0 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x400 ;
		break ;
	case 13 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x100 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x300 ;
		break ;
	case 14 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x200 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x200 ;
		break ;
	case 15 :
		SMC.DC[(*motor).channelA].B.SIGN = 0 ;
		SMC.DC[(*motor).channelA].B.DUTY = 0x300 ;
		SMC.DC[(*motor).channelB].B.SIGN = 1 ;
		SMC.DC[(*motor).channelB].B.DUTY = 0x100 ;
		break ;
	}
}

/** 
 * UPDATES STEP MOTOR POSITION.
 *
 * @param motor		Pointer to the step motor structure to update.		
 * @return			None.
 */
void update(struct StepMotor* motor) {
	// Regulation
	if ((*motor).currentStep < (*motor).stepOrder) {
		if ((*motor).logic == 0) {
			increase(motor) ;
		}
		else {
			decrease(motor) ;
		}
	}
	if ((*motor).currentStep > (*motor).stepOrder) {
		if ((*motor).logic == 0) {
			decrease(motor) ;
		}
		else {
			increase(motor) ;
		}
	}
}

/** 
 * INDICATES IF THE NEEDLE REACHES THE MINIMUM VALUE.
 *
 * @param motor		Pointer to the step motor structure to update.		
 * @return			1 if the needle displays the minimum value of the indicator.
 * 					0 otherwise.
 */
int isAtMinimum(struct StepMotor* motor) {
	int result = 0 ;
	if ((*motor).logic == 0) {
		result = ((*motor).currentStep <= (*motor).offset) ;
	}
	else {
		result = ((*motor).currentStep >= ((*motor).stepsToMax-(*motor).offset)) ;
	}
	return result ;
}

/** 
 * INDICATES IF THE NEEDLE REACHES THE MAXIMUM VALUE.
 *
 * @param motor		Pointer to the step motor structure to update.		
 * @return			1 if the needle displays the maximum value of the indicator.
 * 					0 otherwise.
 */
int isAtMaximum(struct StepMotor* motor) {
	int result = 0 ;
	if ((*motor).logic == 0) {
		result = ((*motor).currentStep >= (*motor).stepsToMax) ;
	}
	else {
		result = ((*motor).currentStep <= 0) ;
	}
	return result ;
}
