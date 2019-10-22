#include <msp430.h>
#include <stdbool.h>

void turn_on_leds(bool green, bool red, bool blue)
{
    if (green)
        P8OUT |= BIT2;
    if (red)
        P3OUT |= BIT7;
    if (blue)
        P4OUT |= BIT0;
}

void turn_off_leds(void)
{
    P4OUT &= ~BIT0;
    P3OUT &= ~BIT7;
    P8OUT &= ~BIT2;
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // LEDS
    P4DIR |= BIT0;                  // blue LED
    P3DIR |= BIT7;                  // red LED
    P8DIR |= BIT2;                  // green LED

    P4OUT &= ~BIT0;                 // set LEDs to low
    P3OUT &= ~BIT7;
    P8OUT &= ~BIT2;

    while(1)
    {
        if (P2IN & BIT5) {          // red button
            turn_on_leds(false, true, false);
        }
        else if (P2IN & BIT4) {     // yellow button
            turn_on_leds(true, true, false);
        }
        else if (P1IN & BIT5) {     // green button
            turn_on_leds(true, false, false);
        }
        else if (P1IN & BIT4) {     // blue button
            turn_on_leds(false, false, true);
        }
        else if (P1IN & BIT3) {     // purple button
            turn_on_leds(false, true, true);
        }
        else {
            turn_off_leds();
        }
    }
}
