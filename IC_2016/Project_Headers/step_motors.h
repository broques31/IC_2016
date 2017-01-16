/*
 * step_motors.h
 *
 * Created on: Nov 4, 2016
 * Author: Ludovic Lesur
 */


#ifndef STEP_MOTORS_H
#define STEP_MOTORS_H

#include "MPC5645S.h"
#include "gpio.h"


/* GLOBAL NAMING */


/* MACRO DECLARATION */

// For all step motors
#define NUMBER_OF_MICROSTEPS 16 // Number of microsteps per full step.
#define TIMER_SMC 1 // PIT timer associated to the SMC module.
#define MICROSTEP_TIME 150000 // Duration of each microstep.

// Speed indicator (values in km/h).
#define OFFSET_SPEED_INDICATOR 60 // Offset position to read '0 km/h'.
#define MIN_SPEED_INDICATOR 0 // Minimum value.
#define MAX_SPEED_INDICATOR 240 // Maximum value.
#define FULL_SCALE_SPEED_INDICATOR 2500 // Number of steps required to indicate 'valueMax'.
#define LOGIC_SPEED_INDICATOR 0 // Direction of step motor revolution.

// Motor RPM indicator (values in rpm).
#define OFFSET_RPM_INDICATOR 180
#define MIN_RPM_INDICATOR 0
#define MAX_RPM_INDICATOR 6000
#define FULL_SCALE_RPM_INDICATOR 2500
#define LOGIC_RPM_INDICATOR 0

// Oil indicator (values in %).
#define OFFSET_OIL_INDICATOR 210
#define MIN_OIL_INDICATOR 0
#define MAX_OIL_INDICATOR 100
#define FULL_SCALE_OIL_INDICATOR 1000
#define LOGIC_OIL_INDICATOR 1

// Temperature indicator (values in °C).
#define OFFSET_TEMPERATURE_INDICATOR 180
#define MIN_TEMPERATURE_INDICATOR 60
#define MAX_TEMPERATURE_INDICATOR 120
#define FULL_SCALE_TEMPERATURE_INDICATOR 760
#define LOGIC_TEMPERATURE_INDICATOR 0

/* STRUCTURES */

struct StepMotor {
	// Output pins.
	int C0M ; // Channel 0 minus.
	int C0P ; // Channel 0 plus.
	int C1M ; // Channel 1 minus.
	int C1P ; // Channel 1 plus.
	// SMC Channels.
	int channelA ;
	int channelB ;
	// Extreme values of the represented value.
	int valueMin ;
	int valueMax ;
	// Calibration (not used in this version, requires the Stall Detection).
	int bottomCalib ;
	int topCalib ;
	int ready ;
	// Positioning
	unsigned int stepsToMax ; // Number of steps required to indicate 'valueMax'.
	unsigned int currentStep ; // Current position.
	unsigned int stepOrder ; // Objective.
	int logic ; // 0 => stepUp() to increase value.
				// 1 => StepDown() to increase value.
				// Depends of the mechanical configuration of the step motor and its needle.
	unsigned int offset ;
} ;


/* FUNCTIONS PROTOTYPES */

void configurePin(int pin) ;

void setParameters(struct StepMotor* motor,
			int pC0M,
			int pC0P,
			int pC1M,
			int pC1P,
			int pChannelA,
			int pChannelB,
			int pValueMin,
			int pValueMax,
			int pDirection,
			unsigned int pStepsToMax,
			unsigned int pOffset) ;

void initSMC() ;

void initStepMotor(struct StepMotor* motor) ;

int calibrate(struct StepMotor* motor) ;

void resetCurrentStep(struct StepMotor* motor) ;

void setOrder(struct StepMotor* motor, float physicalValue) ;

void increase(struct StepMotor* motor) ;

void decrease(struct StepMotor* motor) ;

void microstep(struct StepMotor* motor) ;

void update(struct StepMotor* motor) ;

int isAtMinimum() ;

int isAtMaximum() ;

#endif
