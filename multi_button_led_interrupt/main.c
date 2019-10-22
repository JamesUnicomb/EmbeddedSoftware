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

void toggle_leds(bool green, bool red, bool blue)
{
    if (green)
        P8OUT ^= BIT2;
    if (red)
        P3OUT ^= BIT7;
    if (blue)
        P4OUT ^= BIT0;
}

void turn_off_leds(void)
{
    P4OUT &= ~BIT0;
    P3OUT &= ~BIT7;
    P8OUT &= ~BIT2;
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;         // stop watchdog timer

    // LEDS
    P4DIR |= BIT0;                    // blue LED
    P3DIR |= BIT7;                    // red LED
    P8DIR |= BIT2;                    // green LED

    turn_off_leds();                  // set LEDs to low


    /*
     * BUTTONS
     */
    P1IE  |= (BIT3 | BIT4 | BIT5);    // P1.3, P1.4, P1.5 interrupt enabled
    P1IFG &= ~(BIT3 | BIT4 | BIT5);   // P1.3, P1.4, P1.5  interrupt flag cleared

    P2IE  |= (BIT4 | BIT5);           // P2.4, P2.5 interrupt enabled
    P2IFG &= ~(BIT4 | BIT5);          // P2.4, P2.5  interrupt flag cleared

    __bis_SR_register(GIE);           // Enable all interrupts

    while(1)
    {}
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i;
    bool green = false;
    bool red   = false;
    bool blue  = false;

    if (P1IN & BIT3) {     // purple button
        red = true;
        blue = true;
    }
    if (P1IN & BIT4) {     // blue button
        blue = true;
    }
    if (P1IN & BIT5) {     // green button
        green = true;
    }

    for (i = 10; i > 0; i--) {
        toggle_leds(green, red, blue);
        __delay_cycles(100000);
    }

    P1IFG &= ~(BIT3 | BIT4 | BIT5);   // P1.3, P1.4, P1.5  interrupt flag cleared
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    unsigned int i;
    bool green = false;
    bool red   = false;
    bool blue  = false;

    if (P2IN & BIT4) {          // yellow button
        green = true;
        red   = true;
    }
    if (P2IN & BIT5) {          // red button
        red = true;
    }

    for (i = 10; i > 0; i--) {
        toggle_leds(green, red, blue);
        __delay_cycles(100000);
    }

    turn_off_leds();

    P2IFG &= ~(BIT4 | BIT5);          // P2.4, P2.5  interrupt flag cleared
}
