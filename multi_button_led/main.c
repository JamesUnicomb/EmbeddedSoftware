#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // LEDS
    P4DIR |= BIT0;                  // blue LED
    P3DIR |= BIT7;                  // red LED
    P8DIR |= BIT2;                  // green LED

    while(1)
    {
        if (P2IN & BIT5) {          // red button
            P3OUT |= BIT7;
        }
        else if (P2IN & BIT4) {     // yellow button
            P3OUT |= BIT7;
            P8OUT |= BIT2;
        }
        else if (P1IN & BIT5) {     // green button
            P8OUT |= BIT2;
        }
        else if (P1IN & BIT4) {     // blue button
            P4OUT |= BIT0;
        }
        else if (P1IN & BIT3) {     // purple button
            P3OUT |= BIT7;
            P4OUT |= BIT0;
        }
        else {
            P4OUT &= ~BIT0;
            P3OUT &= ~BIT7;
            P8OUT &= ~BIT2;
        }
    }
}
