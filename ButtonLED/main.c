#include <msp430f5529.h>

void main( void )
{
  WDTCTL = WDTPW | WDTHOLD;     // Stop watchdog timer

  /*
   * LEDs
   */
  P1DIR |= BIT0;                // P1.0 as output
  P4DIR |= BIT7;                // P4.7 as outout

  P1OUT &= ~BIT0;               // P1.0 to low
  P4OUT |= BIT7;                // P4.7 to high


  /*
   * BUTTONS
   */
  P2IE  |= BIT1;                // P2.1 interrupt enabled
  P2IFG &= ~BIT1;               // P2.1 interrupt flag cleared
  P2REN |= BIT1;                // Enable resistor on P2.1
  P2OUT |= BIT1;                // P2.1 as high

  __bis_SR_register(GIE);       // Enable all interrupts

  while(1)
  {}
}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1OUT ^= BIT0;              // Toggle P1.0
    P4OUT ^= BIT7;              // Toggle P4.7
    P2IFG &= ~BIT1;             // P2.1 interrupt flag cleared
}

