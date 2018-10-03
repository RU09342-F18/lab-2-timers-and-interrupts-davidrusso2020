#include<msp430.h>
/*
 * timerAblinkG2.c
 *
 *  Created on : Oct 3, 2018
 * Last edited : Oct 3, 2018
 *      Author : David Russo
 *
 * This function blinks an LED (D1) using the the secondary master clock
 *
 */
void timerAblinkG2(void);

void timerAblinkG2(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer

    P1SEL &= ~BIT0 & ~BIT6;                     // configures P1.0 (D1) and P1.6 (D2) as GPIO
    P1DIR |= BIT0 | BIT6;                       // configures P1.0 and P1.6 as output
    P1OUT |= BIT0 | BIT6;                       // presets P1.0 (D1) and P1.6 (D2) as ON
    CCTL0 = CCIE;                               // Capture Compare control 0 set to capture compare interrupt enable on register 0
    TACTL = TASSEL_2 | MC_2 | ID_3;             // Timer A Control set to:
                                                // Timer A Source Select: Secondary master clock
                                                // MC_2 - mode control: Continuous Up mode
                                                // ID_3 - internal divider: divides clock by 8
    CCR0 = 10000;                               // Capture compare register = 0;
}
