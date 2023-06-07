#include "sam.h"

#define LED_PIN PIN_PA17

void delay(uint32_t delay);

int main(void) {
    /* Initialize the SAM system */
    SystemInit();
  
    /* Switch the multiplexer to the GPIO function (N is the port number) */
    PORT->Group[0].PINCFG[LED_PIN].bit.PMUXEN = 0;
  
    /* Set the direction of the LED pin to output */
    PORT->Group[0].DIRSET.reg = (1 << LED_PIN);
  
    /* Start blinking loop */
    while (1) {
        /* Toggle the LED state */
        PORT->Group[0].OUTTGL.reg = (1 << LED_PIN);
      
        /* Delay to make the LED blinking visible */
        delay(1000000);
    }
}

void delay(uint32_t delay) {
    while(delay > 0) {
        delay--;
    }
}
