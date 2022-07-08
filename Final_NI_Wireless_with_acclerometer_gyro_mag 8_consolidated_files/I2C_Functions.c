/*
 * I2C_Functions.c
 *
 *  Created on: 14 Aug 2013
 *      Author: nirani
 */

#include "I2C_Functions.h"
#include <msp430.h>
extern unsigned char RX_FLAG;
void I2C_TX_Setup(void)
{
	 _DINT();									// Disable Interrupts
	  RX_FLAG = 0;								// Set flag for receive Interrupt function to zero
	  IE2 &= ~UCB0RXIE; 						// Disable I2C Receive interrupt
	  while (UCB0CTL1 & UCTXSTP); 				// Ensure stop condition was sent from previous transaction
	  UCB0CTL1 &= UCSWRST; 						// Put I2C state machine in reset
	  UCB0CTL1 |= UCSSEL_2;						// SMCLK clock is source
	  UCB0CTL0 |= UCMST + UCSYNC + UCMODE_3; 	// I2C Master, synchronous.
	  UCB0BR0 = 0x10; 							// I2C Frequency of ~100KHz
	  UCB0BR1 = 0;
	  UCB0CTL1 &= ~UCSWRST;  					// Start I2C state machine
	  IE2 |= UCB0TXIE;							// Enable I2C Transmit interrupt
}


void I2C_RX_Setup(void)
{
	  _DINT();									// Disable Interrupts
	  RX_FLAG = 1;								// Set flag for receive Interrupt function to one
	  IE2 &= ~UCB0TXIE; 						// Disable I2C Transmit interrupt
	  UCB0CTL1 &= UCSWRST; 						// Put I2C state machine in reset
	  UCB0CTL1 |= UCSSEL_2; 					// SMCLK clock is source
	  UCB0CTL0 |= UCMST + UCSYNC + UCMODE_3; 	// I2C Master, synchronous.
	  UCB0BR0 = 0x10; 							// I2C Frequency of ~100KHz
	  UCB0BR1 = 0;
	  UCB0CTL1 &= ~UCSWRST;  					// Start I2C state machine
	  IE2 |= UCB0RXIE;	 						// Enable I2C Receive interrupt
}
