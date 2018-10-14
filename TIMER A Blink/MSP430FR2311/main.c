#include <msp430.h> 
/**
 * main.c
 *
 *  Created on : Oct. 13, 2018
 * Last Edited : Oct. 13, 2018
 *      Author : David Russo
 *
 * This function blinks an LED (LED1) using the the secondary master clock using Timer B
 *
 */
void timerAblinkFR(void);                       // previews the function that configures the MSP430FR2311

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	                // stop watchdog timer

	PM5CTL0 &= ~LOCKLPM5;                       // disables GPIO power-on default Hi-Z mode to activate
	                                            // previously configured port settings
	timerAblinkFR();                            // configures the MSP430F5529 for timer A delay (function seen below)
    _BIS_SR(LPM1_bits + GIE);                   // enters into low power mode and enables global interrupts
	return 0;
}

#pragma vector=TIMER0_B0_VECTOR                 // interrupt service routine
__interrupt void TIMER0_B0(void)
{
    P1OUT ^= BIT0;                              // Toggle LED
}

void timerAblinkFR()
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer
    P1SEL0 &= ~BIT0;                            // configures P1.0 (LED1) as GPIO
    P1SEL1 &= ~BIT0;                            // configures P1.0 (LED1) as GPIO
    P1DIR |= BIT0;                              // configures P1.0 (LED1) as output
    P1OUT |= BIT0;                              // initializes P1.0 (LED1) to ON
    TBCCTL0 = CCIE;                             // Timer B Capture Compare control 0 set to capture compare interrupt enable on register 0
    TBCTL = TBSSEL_2 | MC_2 | ID_3;             // Timer B Control set to:
                                                // Timer B Source Select: Secondary master clock
                                                // MC_2 - mode control: Continuous mode
                                                // ID_3 - internal divider: divides clock by 8
    TBCCR0 = 10000;                             // Capture compare register = 0;
}
