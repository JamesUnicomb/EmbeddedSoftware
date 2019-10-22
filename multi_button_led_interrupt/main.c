#include <msp430.h>

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


    /*
     * BUTTONS
     */
    P1IE  |= BIT3;                // P1.3 interrupt enabled
    P1IFG &= ~BIT3;               // P1.3 interrupt flag cleared
    P1OUT |= BIT3;                // P1.3 as high

    P2IE  |= BIT4;                // P2.4 interrupt enabled
    P2IFG &= ~BIT4;               // P2.4 interrupt flag cleared
    P2OUT |= BIT4;                // P2.4 as high

    __bis_SR_register(GIE);       // Enable all interrupts

    while(1)
    {}
  }


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P8OUT |= BIT2;                 // set green LED to high
    __delay_cycles(400000);

    P4OUT &= ~BIT0;                // set LEDs to low
    P3OUT &= ~BIT7;
    P8OUT &= ~BIT2;

    P1IFG &= ~BIT3;               // P1.3 interrupt flag cleared
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P4OUT |= BIT0;                 // set blue LED to high
    __delay_cycles(400000);

    P4OUT &= ~BIT0;                // set LEDs to low
    P3OUT &= ~BIT7;
    P8OUT &= ~BIT2;

    P2IFG &= ~BIT4;               // P2.4 interrupt flag cleared
}
