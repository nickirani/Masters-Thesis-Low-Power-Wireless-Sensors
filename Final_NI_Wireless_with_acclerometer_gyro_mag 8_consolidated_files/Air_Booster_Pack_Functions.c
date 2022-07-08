/*
 * Air_Booster_Pack_Functions.c
 *
 *  Created on: 14 Aug 2013
 *      Author: nirani
 */
#include <msp430.h>
#include "SPI_Functions.h"
#include "Air_Booster_Pack.h"

#define CSN 		BIT5

void RF_868MHz_GFSK_CRC_RSSI_0DBM()
{
	SPIWrite(IOCFG2,0x29);
	SPIWrite(IOCFG1,0x2E);
    SPIWrite(IOCFG0,0x06);
    SPIWrite(FIFOTHR,0x47);
    SPIWrite(SYNC1,0xD3);
    SPIWrite(SYNC0,0x91);
    SPIWrite(PKTLEN,0x14);
    SPIWrite(PKTCTRL1,0x04);
    SPIWrite(PKTCTRL0,0x04);
    SPIWrite(ADDR,0x00);
    SPIWrite(CHANNR,0x00);
    SPIWrite(FSCTRL1,0x06);
    SPIWrite(FSCTRL0,0x00);
    SPIWrite(FREQ2,0x21);
    SPIWrite(FREQ1,0x62);
    SPIWrite(FREQ0,0x76);
    SPIWrite(MDMCFG4,0xF5);
    SPIWrite(MDMCFG3,0x83);
    SPIWrite(MDMCFG2,0x13);
    SPIWrite(MDMCFG1,0x42);
    SPIWrite(MDMCFG0,0xF8);
    SPIWrite(DEVIATN,0x15);
    SPIWrite(MCSM2,0x07);
    SPIWrite(MCSM1,0x30);
    SPIWrite(MCSM0,0x18);
    SPIWrite(FOCCFG,0x16);
    SPIWrite(BSCFG,0x6C);
    SPIWrite(AGCCTRL2,0x03);
    SPIWrite(AGCCTRL1,0x40);
    SPIWrite(AGCCTRL0,0x91);
    SPIWrite(0x20,0xFB);
    SPIWrite(FREND1,0x56);
    SPIWrite(FREND0,0x10);
    SPIWrite(FSCAL3,0xE9);
    SPIWrite(FSCAL2,0x2A);
    SPIWrite(FSCAL1,0x00);
    SPIWrite(FSCAL0,0x1F);
    SPIWrite(0x29,0x59);
    SPIWrite(0x2A,0x7F);
    SPIWrite(0x2B,0x3F);
    SPIWrite(TEST2,0x81);
    SPIWrite(TEST1,0x35);
    SPIWrite(TEST0,0x09);

}

//Command access
void AIR_CMD_REG(char address)
{
	  P1OUT&=~CSN;     // /CS enable
	  while (!(IFG2&UCA0TXIFG));               // Wait for TXBUF ready
	  UCA0TXBUF = address;                         // Send address
	  while (UCA0STAT & UCBUSY);                // Wait for TX complete
	  P1OUT|=CSN;         // /CS disable
}

//Status access

char AIR_ST_REG(char address)
{
	  char x;

	  P1OUT&=~CSN;     // /CS enable
	  while (!(IFG2&UCA0TXIFG));               // Wait for TXBUF ready
	  UCA0TXBUF = (address | 0xC0);// Send address
	  while (!(IFG2&UCA0TXIFG));               // Wait for TXBUF ready
	  UCA0TXBUF = 0;                            // Dummy write so we can read data
	  while (UCA0STAT & UCBUSY);                // Wait for TX complete
	  x = UCA0RXBUF;                            // Read data
	  P1OUT|=CSN;         // /CS disable

	  return x;
}
//Power on reset
void AIR_POR_RES()
{
	  P1OUT&=~CSN;     // /CS enable
	  P1OUT|=CSN;         // /CS disable
	  __delay_cycles(640); //40us delay
	  AIR_CMD_REG(SRES);
}

//Wake up
void AIR_WAKE()
{
	  P1OUT&=~CSN;     // /CS enable
	  P1OUT|=CSN;         // /CS disable
}


