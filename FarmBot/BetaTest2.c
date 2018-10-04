#include<msp430g2553.h>										// Include the source (header) file of the code, specify the genre of MSP430 micro-controller
															// Here the series used is MSP430G2553
/*
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 * INITIALIZATION
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 */
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;									// Stop the Watchdog timer

  P1DIR=BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;			// Enable the direction of PIN 1.0 to PIN 1.7 of the PORT1
  P2DIR=BIT0+BIT1;											// Enable the direction of PIN 2.0 AND PIN 2.1 of the PORT2
  P1OUT=0X00;												// Set PORT1 to output direction, set all the outputs of PORT1 LOW
  P2OUT=0X00;												// Set PORT2 to output direction, set all the outputs of PORT2 LOW
  BCSCTL1 = CALBC1_1MHZ;									// Calibrate MCLK using Basic Clock System Control 1 to 1MHz
  DCOCTL = CALDCO_1MHZ;										// Calibrate the Digitally controlled oscillator using DCO Clock Frequency Control to 1MHz

/*
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 *  ENABLE UART SERIAL COMMUNICATION
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 */
  P1SEL = (BIT1+BIT2);										// Port 1 Selection for PIN 1.1 and PIN 1.2 used for UART mode
  P1SEL2 = (BIT1+BIT2);										// Port 1 Selection 2 for PIN 1.1 and PIN 1.2 used for UART mode
  UCA0CTL1 |= UCSSEL_2;										// Universal serial control interface using USCI A0 Control Register 1
  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	// USCI 0 Clock Source: 2
  UCA0BR0 = 104;											// USCI A0 Baud Rate 0 set to 104BPs
  UCA0BR1 = 0;												// USCI A0 Baud Rate 1 set to 0BPs
  UCA0MCTL = UCBRS0;										// USCI A0 Modulation Control for USCI Second Stage Modulation Select 0
  UCA0CTL1 &= ~UCSWRST;										// USCI A0 Control Register 1 for USCI Software Reset
  IE2 |= UCA0RXIE;											// Interrupt Enable 2 for USCI/UART reception

  __bis_SR_register(LPM0_bits + GIE);						// Predefined function to activate low power mode (CPU OFF)

}

/*
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 * ESTABLISH COMMUNICATION LINK AND ACCEPT INSTRUCTIONS
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 */

#pragma vector=USCIAB0RX_VECTOR								// USCI reception vector activation interrupt service routine
__interrupt void USCI0RX_ISR(void)							// Enable USCI interrupt service routine to accept values
{
  while (!(IFG2&UCA0TXIFG));								// Enable interrupt flag 2 and wait to receive inputs
   UCA0TXBUF = UCA0RXBUF;									// USCI A0 Transmit Buffer and USCI A0 receive Buffer have similar values

  if(UCA0RXBUF=='go')									// when USCI A0 Receive Buffer has the value 'go'

/*
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 * START EXECUTING THE CODE SEQUENTIALLY AS PER THE INSTRUCTIONS RECEIVED BY THE USER
 *
 * 1. PLOUGHING
 * -------------------------------------------------------------------------------------------------------------------------------------------------
 */

	  P2OUT |=0X00;											// Set all outputs of PORT 2 as LOW
	  P1OUT |=(BIT3+BIT4);									// Set direction of PORT 1 as output and make PIN 1.3 and PIN 1.4 HIGH
	  	  _delay_cycles(5000000);							// Swarm robot goes forward for 5 seconds
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	  	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
	  P1OUT |=(BIT3);										// Set direction of PORT 1 as output and make PIN 1.3 HIGH
	  	  _delay_cycles(1000000);							// Swarm robot turns to direction RIGHT
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	   	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
	  P1OUT |=(BIT3+BIT4);									// Set direction of PORT 1 as output and make PIN 1.3 and PIN 1.4 HIGH
	   	  _delay_cycles(3000000);							// Swarm robot goes forward for 3 seconds
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	  	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
	  P1OUT |=(BIT3);										// Set direction of PORT 1 as output and make PIN 1.3 HIGH
	   	  _delay_cycles(1000000);							// Swarm robot turns to direction RIGHT
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	   	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
	  P1OUT |=(BIT3+BIT4);									// Set direction of PORT 1 as output and make PIN 1.3 and PIN 1.4 HIGH
		  _delay_cycles(5000000);							// Swarm robot goes forward for 5 seconds
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	  	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
	  P1OUT |=(BIT3);										// Set direction of PORT 1 as output and make PIN 1.3 HIGH
	  	  _delay_cycles(1000000);							// Swarm robot turns to direction RIGHT
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	   	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
	  P1OUT |=(BIT3+BIT4);									// Set direction of PORT 1 as output and make PIN 1.3 and PIN 1.4 HIGH
	   	  _delay_cycles(3000000);							// Swarm robot goes forward for 3 seconds
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	  	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
	  P1OUT |=(BIT3);										// Set direction of PORT 1 as output and make PIN 1.3 HIGH
	   	  _delay_cycles(1000000);							// Swarm robot turns to direction RIGHT
	  P1OUT =0x00;											// Set all outputs of PORT 1 as LOW
	   	  _delay_cycles(1000000);							// Swarm robot stays IDLE for 1 second
}
