#include <msp430.h> 
/**
 * main.c
 *
 *  Created on : Oct. 3, 2018
 * Last edited : Oct. 10, 2018
 *      Author : David Russo
 *
 *  This function initially blinks an LED (D1) at a default rate.
 *  Holding and releasing a button (S2) for an arbitrary duration sets the LED to blink at that rate.
 *
 */
void buttonBasedDelayG2();

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	                    // stop watchdog timer
	
	BCSCTL3 - LFXT1S_2;                             // enables A clock
	buttonBasedDelayG2();                           // calls the initialization function (Seen at the bottom of the file)
	TACCR1 = 0xFFFE;                                // enables timer A Capture compare register 1 to 0xFFFE
	_BIS_SR(LPM0_bits + GIE);                       // enters into low power mode and enables global interrupts
	return 0;                                       // never reaches this line of code
}

#pragma vector=TIMER0_A0_VECTOR                     // interrupt service routine for Timer 0 CCR0
__interrupt void TIMER0_A0(void)
{
    P1OUT ^= BIT0;                                  // Toggle LED
}

#pragma vector=TIMER0_A1_VECTOR                     // interrupt service routine for Timer 0 CCR1
__interrupt void TIMER0_A1(void)
{
    if ((P1IN & BIT3) == BIT3)                      // if button pressed
    {
        TACCR0 = 0xFFFE;                            // sets the value of Timer A Register to TACCR0
        TACTL = TASSEL_1 | MC_1 | ID_3;             // configures timer: A clock, Up mode, Divide by 8
        TA0R = 0;                                   // resets the timer A register
        P1IES = BIT3;                               // Set the interrupt edge select to positive edge        // positive edgfe interrupt
    }
}

#pragma vector=PORT1_VECTOR                         // interrupt service routine
__interrupt void Port_1(void)
{
    if ((P1IES & BIT3) == BIT3)                     // on rising edge of button press
    {
        P1IES = ~BIT3;                              // change the edge of the interrupt to negative edge
        //TACCR0 = TA0R;                            // store the value of TA0R equal to TACCR0
        TA0R = 0;                                   // clear timer A register
        TACTL = TASSEL_1 | MC_2 | ID_3;             // Timer A Control set to:
                                                    // Timer A Source Select: A clock
                                                    // MC_2 - mode control: Continuous mode
                                                    // ID_3 - internal divider: divides clock by 8
    }
    else                                            // on falling edge of button press
    {
        P1OUT ^= BIT0;                              // turns off LED, turns off timer
        TACCR0 = TA0R;                              // sets the value of Timer A Register to TACCR0
        TACTL = TASSEL_1 | MC_1 | ID_3;             // configures timer: A clock, Up mode, Divide by 8
        TA0R = 0;                                   // resets the timer A register
        P1IES = BIT3;                               // Set the interrupt edge select to positive edge
    }
    P1IFG &= ~BIT3;                                 // clearing the interrupt
}

void buttonBasedDelayG2()
{
    //initial setup
    WDTCTL = WDTPW + WDTHOLD;                       // Stop watchdog timer

    P1SEL &= ~BIT0 & ~BIT6;                         // configures P1.0 (D1) and P1.6 (D2) as GPIO
    P1DIR |= BIT0 | BIT6;                           // configures P1.0 and P1.6 as output
    P1OUT |= BIT0 | BIT6;                           // presets P1.0 (D1) and P1.6 (D2) as ON
    P1REN |= BIT3;                                  // enables a resistor on the P1.3 (S1)
    TACCTL0 = CCIE;                                 // Capture Compare control 0 set to capture compare interrupt enable on register 0
    P1IE |= BIT3;                                   // enables an interrupt on bit 3 of Port 1
    P1IES = BIT3;                                   // presets the interrupt edge to rising edge
    TACTL = TASSEL_2 | MC_1 | ID_3;                 // Timer A Control set to:
                                                    // Timer A Source Select: Secondary master clock
                                                    // MC_1 - mode control: Up mode
                                                    // ID_3 - internal divider: divides clock by 8
    TACCR0 = 50000;                                 // Capture compare register = 0;
}
