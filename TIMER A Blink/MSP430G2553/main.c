#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	timerAblinkG2();
	_BIS_SR(LPM0_bits + GIE); // enters into low power mode and enables global interrupts
	return 0;
}
#pragma vector=TIMER0_A0_VECTOR     // interrupt service routine
__interrupt void TIMER0_A0(void)
{
    P1OUT ^= BIT0;              // Toggle LED
    //P1IFG &= ~BIT3;             // clearing the interrupt
}
