/*
 * PinDefinitions.h
 *
 * Created: 09/12/2023
 *  Author: scott.sullivan
 */

#ifndef PINDEFINITIONS_H_
#define PINDEFINITIONS_H_
#include "sam.h"

/****************PIN DEFINITIONS******************/
/****************I2C MASTER**********************/
#define I2C_GROUP 0

#define C1_SDA PORT_PA08
#define C1_SCL PORT_PA09
#define C1_SERCOM SERCOM0

#define C2_SDA PORT_PA16
#define C2_SCL PORT_PA17
#define C2_SERCOM SERCOM1

#define C3_SDA PORT_PA12
#define C3_SCL PORT_PA13
#define C3_SERCOM SERCOM2

#define C4_SDA PORT_PA22
#define C4_SCL PORT_PA23
#define C4_SERCOM SERCOM3




//**************USB**************************/
#define USB_N PORT_PA24
#define USB_P PORT_PA25


//**************SWCLK**************************/
#define SWCLK PORT_PA30
#define SWDIO PORT_PA31


/**************LED INDICATORS********************/
#define STATUS_LED PORT_PB31
#define STATUS_LED_GROUP 1



/****************GLOBAL VARIABLES****************/



/************* MODES*****************/
#define NUMBER_OF_MODES 12


// MODES v3
//Program Mode data
enum ProgramState
{
	Running,
	TestMode,
};

// Define the property values
#define DMX_BASE_ADDRESS 0
#define MODE 1
#define COLOR_PRIMARY 2
#define COLOR_SECONDARY 3


/**********************General Definitions*************/
#define NUMBER_OF_DMX_ADDRESSESS 512

#endif /* PINDEFINITIONS_H_ */