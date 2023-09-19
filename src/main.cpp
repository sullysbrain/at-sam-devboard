 /*
 * SAMD21 J Breakout Board
 *
 * Created: 9/12/2023
 * Author : scott.sullivan
 */ 

/*
* GClk Uses
* 0 - CPU Clock set to DFFL 48MHz
* 1
* 2 - 48MHz scaled down for TLC
* 3 - 8MHz internal OSC for DFFL source
* 4 - 1KHz clock for firefly delay
* 5
* 6
* 7
*/


#include "sam.h"
#include "PinDefinitions.h"

/***************RANDOM FOR TESTING*************/
#include <time.h>
#include <stdlib.h>


// Adding timer function for ATSAM
// TODO:  get I2C working
void i2c_init(void) {
	// Peripheral C settings:
	// Pin 17	PA08	SERCOM0/PAD[0]	SDA
	// Pin 18	PA09	SERCOM0/PAD[1]	SCL
	
	// Enable pins for peripheral functionality
	PORT->Group[I2C_GROUP].PINCFG[I2C_SDA].bit.PMUXEN = 1;
	PORT->Group[I2C_GROUP].PINCFG[I2C_SCL].bit.PMUXEN = 1;
	// Configure PA08 and PA09 for SERCOM Alternate Function C
	PORT->Group[I2C_GROUP].PMUX[I2C_SDA / 2].bit.PMUXE = PORT_PMUX_PMUXE_C_Val;
	PORT->Group[I2C_GROUP].PMUX[I2C_SCL / 2].bit.PMUXO = PORT_PMUX_PMUXO_C_Val;
	

	// Set the GCLK (Generic Clock) for SERCOM0
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;
	while(SERCOM0->I2CM.SYNCBUSY.bit.SYSOP);

	//	SERCOM0
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0)|GCLK_CLKCTRL_CLKEN|GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_CORE);
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0)|GCLK_CLKCTRL_CLKEN|GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_SLOW);
	while (GCLK->STATUS.bit.SYNCBUSY);

	// Reset the SERCOM
	//I2C_SERCOM->I2CM.CTRLA.bit.SWRST = 1;
	//while (I2C_SERCOM->I2CM.SYNCBUSY.bit.SWRST);

	SERCOM0->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_MODE_I2C_MASTER;

	// Set to I2C master mode, using internal pull-ups
	I2C_SERCOM->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_MODE_I2C_MASTER;
	I2C_SERCOM->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_SDAHOLD(1);
	
	// Assuming a 32MHz clock and desired 100kHz I2C baud
	I2C_SERCOM->I2CM.BAUD.reg = (32000000 / (2 * 100000)) - 1;

	// Enable the I2C master mode
	I2C_SERCOM->I2CM.CTRLA.bit.ENABLE = 1;
	while (I2C_SERCOM->I2CM.SYNCBUSY.bit.ENABLE);
	
}



int main(void)
{
    /* Initialize the SAM system */
	//MaxClockSpeed();
    //SystemInit();
	
	//PORT->Group[0].DIRSET.reg = PORT_PA16;
	//PORT->Group[0].OUTSET.reg = PORT_PA16;
	//PORT->Group[STATUS_LED_GROUP].DIRSET.reg = STATUS_LED;
	//PORT->Group[STATUS_LED_GROUP].OUTSET.reg = STATUS_LED;

	
		
	while(true){


	}
}

