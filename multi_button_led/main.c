#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // LEDS
    P2DIR |= BIT5;                  // blue LED
    P2DIR |= BIT4;                  // red LED
    P1DIR |= BIT5;                  // green LED

    while(1)
    {
        if (P4IN & BIT0) {          // yellow button
            P2OUT |= BIT4;
            P1OUT |= BIT5;
        }
        else if (P4IN & BIT3) {     // red button
            P2OUT |= BIT4;
        }
        else if (P3IN & BIT7) {     // green button
            P1OUT |= BIT5;
        }
        else if (P8IN & BIT2) {     // blue button
            P2OUT |= BIT5;
        }
        else if (P8IN & BIT1) {     // purple button
            P2OUT |= BIT4;
            P2OUT |= BIT5;
        }
        else {
            P1OUT &= ~BIT5;
            P2OUT &= ~BIT4;
            P2OUT &= ~BIT5;
        }
    }
}
