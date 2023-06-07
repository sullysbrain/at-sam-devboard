#include <sam.h>

#define LED_PIN 17

void delay_ms(uint32_t ms);

int main(void)
{
    // Set the pin as output
    REG_PORT_DIR0 |= (1 << LED_PIN);

    while (1) {
        // Toggle the LED
        REG_PORT_OUTTGL0 = (1 << LED_PIN);

        // Delay for a while
        delay_ms(350);
    }

    return 0;
}

void delay_ms(uint32_t ms) {
    for (uint32_t delay = ms * 4000; delay > 0; delay--) {
        __asm__ volatile ("nop");
    }
}
