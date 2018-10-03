#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	buttonInterruptG2();
	_BIS_SR(LPM3_bits + GIE); // enters into low power mode and enables global interrupts
	return 0;
}

#pragma vector=PORT1_VECTOR     // interrupt service routine
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;              // Toggle LED
    P1IFG &= ~BIT3;             // clearing the interrupt
}
