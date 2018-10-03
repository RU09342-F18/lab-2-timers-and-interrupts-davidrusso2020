#include <msp430.h>
/*
 * buttonInterruptG2.c
 *
 *  Created on : Oct 1, 2018
 * Last edited : Oct 1, 2018
 *      Author : David Russo
 *
 * This function toggles an LED (D1) on the negative edge of a button press (S1)
 *
 */
void buttonInterruptG2();

void buttonInterruptG2()
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer

    P1SEL &= ~BIT3;                             // configures P1.3 (S1) as GPIO
    P1SEL &= ~BIT0 & ~BIT6;                     // configures P1.0 (D1) and P1.6 (D2) as GPIO
    P1DIR &= ~BIT3;                             // configures P1.3 (S1) as input
    P1DIR |= BIT0 | BIT6;                       // configures P1.0 and P1.6 as output
    P1REN |= BIT3;                              // enables a resistor on P1.3
    P1OUT |= BIT3;                              // makes resistor a pull-up resistor
    P1OUT |= BIT0 | BIT6;                       // presets P1.0 (D1) as ON
    P1IE  |= BIT3;                              // enables interrupt on P1.3 (S1)
    P1IES |= BIT3;                              // sets interrupt on negative edge
    P1IFG &= ~BIT3;                             // clearing the interrupt

}
