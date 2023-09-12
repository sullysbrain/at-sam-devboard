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

