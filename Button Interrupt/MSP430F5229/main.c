#include <msp430.h> 
/**
 * main.c
 *
 *  Created on : Oct. 10, 2018
 * Last Edited : Oct. 13, 2018
 *      Author : David Russo
 *
 * This function toggles an LED1 on the positive edge of a button press (S1)
 * Note: this code does not account for debouncing, so implementation is not perfect
 *
 */
void buttonInterruptF5();                       // previews the function that configures the MSP430F5529

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	                // stop watchdog timer
	
	buttonInterruptF5();                        // configures the MSP430F5529 for button interrupt
    _BIS_SR(LPM1_bits + GIE);                   // enters into low power mode and enables global interrupts
	return 0;
}

#pragma vector=PORT2_VECTOR                     // interrupt service routine
__interrupt void Port_2(void)
{
    P1OUT ^= BIT0;                              // toggle LED
    P2IFG &= ~BIT1;                             // clearing the interrupt
}

void buttonInterruptF5()
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer

    P2SEL &= ~BIT1;                             // configures P2.1 (S1) as GPIO
    P1SEL &= ~BIT0;                             // configures P1.0 (LED1) as GPIO
    P4SEL &= ~BIT7;                             // configures P4.7 (LED2) as GPIO
    P2DIR &= ~BIT1;                             // configures P2.1 (S1) as input
    P1DIR |= BIT0;                              // configures P1.0 and as output
    P4DIR |= BIT7;                              // configures P4.7 and as output
    P2REN |= BIT1;                              // enables a resistor on P2.1
    P2OUT |= BIT1;                              // makes resistor a pull-up resistor
    P1OUT |= BIT0;                              // presets P1.0 (LED1) as ON
    P4OUT |= BIT7;                              // presets P4.7 (LED2) as ON
    P2IE  |= BIT1;                              // enables interrupt on P2.1 (S1)
    P2IES |= BIT1;                              // sets interrupt on positive edge
    P2IFG &= ~BIT1;                             // clearing the interrupt
}
