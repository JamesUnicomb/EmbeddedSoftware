#include <msp430f5529.h>

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

  /*
   * LEDs
   */
  P1DIR |= BIT0;                // P1.0 as output
  P4DIR |= BIT7;                // P4.7 as outout

  P1OUT &= ~BIT0;               // P1.0 to low
  P4OUT |= BIT7;                // P4.7 to high


  /*
   * ADC
   */
  P6SEL     |= BIT0;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+ADC12SHT0_8+ADC12MSC;     // Turn on ADC12, set sampling time
                                                // set multiple sample conversion
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_2;           // Use sampling timer, set mode
  ADC12IE   = BIT0;                             // Enable ADC12IFG.0
  ADC12CTL0 |= ADC12ENC;                        // Enable conversions
  ADC12CTL0 |= ADC12SC;                         // Start conversion

  __bis_SR_register(LPM4_bits + GIE);           // Enter LPM4, Enable interrupts

}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  __delay_cycles(1000);

  int value = ADC12MEM0;

  if (value > 2048)
  {
      P1OUT |= BIT0;
      P4OUT &= ~BIT7;
  }
  else
  {
      P1OUT &= ~BIT0;
      P4OUT |= BIT7;
  }
}
