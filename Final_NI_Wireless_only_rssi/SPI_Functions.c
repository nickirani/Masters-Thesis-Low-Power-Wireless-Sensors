/*
 * Functions.c
 *
 *  Created on: 14 Aug 2013
 *      Author: nirani
 */

#include "SPI_Functions.h"
#include <msp430.h>
#define SOMI 		BIT1
#define SIMO 		BIT2
#define A0SPICLK	BIT4
#define CSN 		BIT5

void SPISetup(void)// sets up SPI port
{
		  P1DIR |=  SIMO + A0SPICLK + CSN;
		  P1SEL |= SOMI + SIMO + A0SPICLK;
		  P1SEL2 |= SOMI + SIMO + A0SPICLK;
		  UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
		  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
		  UCA0BR0 |= 0x02;                          // 1MHz
		  UCA0BR1 = 0;                              //
		  UCA0MCTL = 0;                             // No modulation
		  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}
void SPIWrite(char address,char data) // writes to a register at an address specified
{
	 P1OUT&=~CSN;     // /CS enable
	  while (!(IFG2&UCA0TXIFG));               // Wait for TXBUF ready
	  UCA0TXBUF = address;                         // Send address
	  while (!(IFG2&UCA0TXIFG));               // Wait for TXBUF ready
	  UCA0TXBUF = data;                        // Send data
	  while (UCA0STAT & UCBUSY);                // Wait for TX complete
	  P1OUT|=CSN;         // /CS disable
}
char SPIRead(char address) // reads from a register at an address specified
{
	  char x;

	  P1OUT&=~CSN;     // /CS enable
	  while (!(IFG2&UCA0TXIFG));               // Wait for TXBUF ready
	  UCA0TXBUF = (address | 0x80);// Send address
	  while (!(IFG2&UCA0TXIFG));               // Wait for TXBUF ready
	  UCA0TXBUF = 0;                            // Dummy write so we can read data
	  while (UCA0STAT & UCBUSY);                // Wait for TX complete
	  x = UCA0RXBUF;                            // Read data
	  P1OUT|=CSN;         // /CS disable

	  return x;
}
