#include <sam.h>
#include <math.h>
#include <stdio.h>

#define LED_PIN 17  // blue led
#define WAVE_PERIOD 32768 // 1Hz

void SystemInit() {

}


int main(void){
    //SystemInit();

    // Enable the TCC0 clock in the Power Manager
    PM->APBCMASK.reg |= PM_APBCMASK_TCC2;

    // Enable the OSC32K oscillator
    SYSCTRL->OSC32K.reg = SYSCTRL_OSC32K_STARTUP(6) | // Startup time
                        SYSCTRL_OSC32K_EN32K | // Output a 32kHz clock (required for GCLK)
                        SYSCTRL_OSC32K_ENABLE; // Enable OSC32K
    while (!(SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_OSC32KRDY)); // Wait for OSC32K to be ready

    // Set up GCLK7 to use OSC32K
    GCLK->GENDIV.reg = GCLK_GENDIV_ID(7); // Divide by 1
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY); // Wait for synchronization

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(7) | // Select GCLK7
                        GCLK_GENCTRL_SRC_OSC32K | // Set source to OSC32K
                        GCLK_GENCTRL_GENEN; // Enable GCLK7
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY); // Wait for synchronization

    // Connect GCLK7 to TCC0
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_TCC2_TC3 |  // Select TCC1/TCC0
                        GCLK_CLKCTRL_GEN_GCLK7 |    // Select GCLK7
                        GCLK_CLKCTRL_CLKEN;         // Enable this clock

    // Configure PA17 with peripheral function E
    PORT->Group[0].PINCFG[17].bit.PMUXEN = 1; // Enable the peripheral multiplexer on PA17
    PORT->Group[0].PMUX[17 >> 1].bit.PMUXO = PORT_PMUX_PMUXO_E_Val; // Set the multiplexer
    // // set LED to output and turn on
    // PORT->Group[0].DIRSET.reg |= (1 << LED_PIN);
    // PORT->Group[0].OUTSET.reg |= (1 << LED_PIN);

    // Configure TCC0
    TCC0->CTRLA.reg = TCC_CTRLA_SWRST; // Reset TCC0
    while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_SWRST); // Wait for the reset to complete

    TCC2->CTRLA.bit.PRESCALER = TCC_CTRLA_PRESCALER_DIV1_Val; // No additional division
    TCC2->PER.reg = 32768; // With the 1Hz GCLK7, this gives a frequency of 1Hz
    TCC2->WAVE.bit.WAVEGEN = TCC_WAVE_WAVEGEN_NPWM_Val; // Set up for normal (single-slope) PWM mode
    TCC2->CC[1].reg = 32768 / 4; // 50% duty cycle
    TCC2->CTRLA.bit.ENABLE = 1; // Enable TCC0
    while(TCC2->SYNCBUSY.bit.ENABLE); // Wait for synchronization

    while(1) {
        asm volatile ("nop");
    }

    return 0;
}
