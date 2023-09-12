#include <sam.h>
#include <math.h>
#include <stdio.h>

#define LED_PIN 17  // PA17
#define MAX_BRIGHTNESS 5
#define STEP_SIZE 5
#define PI 3.14159265

// external variables
extern int my_public_int;


// Internal Math functions
int double_int(int input);
void delay_ms(uint32_t ms);


int main(void){
    // Enable the TCC1 clock in the Power Manager
    PM->APBCMASK.reg |= PM_APBCMASK_TCC1;

    // Enable the OSC32K oscillator
    SYSCTRL->OSC32K.reg = SYSCTRL_OSC32K_STARTUP(6) | // Startup time
                        SYSCTRL_OSC32K_EN32K | // Output a 32kHz clock (required for GCLK)
                        SYSCTRL_OSC32K_ENABLE; // Enable OSC32K
    while (!(SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_OSC32KRDY)); // Wait for OSC32K to be ready

    // Set up GCLK7 to use OSC32K
    GCLK->GENDIV.reg = GCLK_GENDIV_ID(7) | GCLK_GENDIV_DIV(32768); // Divide by 32768
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY); // Wait for synchronization

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(7) | // Select GCLK7
                        GCLK_GENCTRL_SRC_OSC32K | // Set source to OSC32K
                        GCLK_GENCTRL_GENEN; // Enable GCLK7
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY); // Wait for synchronization

    // Connect GCLK7 to TCC1
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_TCC0_TCC1 |  // Select TCC1/TCC0
                        GCLK_CLKCTRL_GEN_GCLK7 |    // Select GCLK7
                        GCLK_CLKCTRL_CLKEN;         // Enable this clock
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY); // Wait for synchronization

    // Configure PA17 with peripheral function F
    PORT->Group[0].PINCFG[17].bit.PMUXEN = 1; // Enable the peripheral multiplexer on PA17
    PORT->Group[0].PMUX[17 >> 1].bit.PMUXO = PORT_PMUX_PMUXO_F_Val; // Set the multiplexer to peripheral function F

    // Configure TCC1
    TCC1->CTRLA.bit.PRESCALER = TCC_CTRLA_PRESCALER_DIV1_Val; // No additional division
    TCC1->PER.reg = 1;  // With the 1Hz GCLK7, this gives a frequency of 1Hz

    TCC1->WAVE.bit.WAVEGEN = TCC_WAVE_WAVEGEN_NPWM_Val;  // Set up for normal (single-slope) PWM mode
    TCC1->CC[1].reg = 1 / 2; // 50% duty cycle
    TCC1->CTRLA.bit.ENABLE = 1;  // Enable TCC1
    while(TCC1->SYNCBUSY.bit.ENABLE); // Wait for synchronization

    while (1){
    }

}
