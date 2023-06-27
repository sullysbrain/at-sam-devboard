#include <sam.h>
#include <math.h>

#define LED_PIN 17
#define MAX_BRIGHTNESS 5
#define STEP_SIZE 5
#define PI 3.14159265


// Internal Math functions
int double_int(int input);
void delay_ms(uint32_t ms);


int main(void)
{
    REG_PORT_DIR0 |= (1 << LED_PIN);

    uint8_t brightness = 0;
    int8_t step = STEP_SIZE;

    while (1) {
        for (brightness = 0; brightness <= MAX_BRIGHTNESS; brightness += STEP_SIZE) {
            // LED on
            REG_PORT_OUTCLR0 = (1 << LED_PIN);
            delay_ms(brightness);

            // LED off
            REG_PORT_OUTSET0 = (1 << LED_PIN);
            delay_ms((int)(sin((1 - brightness) * PI) * MAX_BRIGHTNESS));
        }
        for (brightness = MAX_BRIGHTNESS; brightness >= 0; brightness -= STEP_SIZE) {
            // LED on
            REG_PORT_OUTCLR0 = (1 << LED_PIN);
            delay_ms((int)(sin(brightness * PI) * MAX_BRIGHTNESS));

            // LED off
            REG_PORT_OUTSET0 = (1 << LED_PIN);
            delay_ms(MAX_BRIGHTNESS - brightness);
        }

    }

    return 0;
}

// Math functions

void delay_ms(uint32_t ms) {
    for (uint32_t delay = ms * 4; delay > 0; delay--) {
        __asm__ volatile ("nop");
    }
}

int double_int(int input) {
    return input * 2;
}

