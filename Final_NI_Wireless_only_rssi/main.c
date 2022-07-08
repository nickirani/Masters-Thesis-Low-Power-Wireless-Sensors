////////////////////////////////////////////////////////////////////////////////////////////////
//Name: 			Nicholas Irani
//Student Number:	X00077430
//Supervisor:		Mike Gill / Andrew Donnalon
//Date: 01/03/2014
//Revision Notes; Attempting to consolidate files. Move I2C functions to separate file to be called as a function
//
//Date: 02/03/2014
//Revision Notes; Consolidated files
//
//Date: 07/03/2014
//Revision Notes; Solved issue with I2C rx. Issue pertained to TX interrupt not being set before Rx setup, this meant GIE was on but no TX interrupt flag could be raised
//
//Date: 23/04/2014
//Revision Notes; Solved issue with incorrect data being transmitted. Required PTxData2 to be used in transmit routine instead of PTx1.
//
//Date: 24/04/2014
//Revision Notes; Added timer function to main routine to broadcast data once every 3 seconds.
//
//Date: 04/05/2014
//Revision Notes; Added magnetometer reading extraction
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//Header includes
#include <msp430.h>
#include "SPI_Functions.h"
#include "Air_Booster_Pack_Functions.h"
#include "Air_Booster_Pack.h"
///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
//#defines and global variables
char i,x,time,value=0;
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//Main function defined here
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;			// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;				// Calibrate MSP430 to run at 1MHz
    DCOCTL = CALDCO_1MHZ;
	P1DIR |= BIT0;
    SPISetup(); 						// Setup SPI port
    AIR_POR_RES(); 						// Reset Air module
    RF_868MHz_GFSK_CRC_RSSI_0DBM(); 	// Setup radio profile
    SPIWrite(PATABLE,0x50);				// Write PA value
    AIR_CMD_REG(SPWD); 					// Sleep mode

    while(1)
    {

        P1OUT=0x00;
    	while(time<6)

    	{
        TACTL = TASSEL_2 + MC_2 + TAIE + ID_3;// SMCLK, continuous mode, interrupt enabled
        __bis_SR_register(CPUOFF + GIE);	// Enter LPM0 w/ interrupts
        time++;
    	}
    	P1OUT=0x01;

        SPIWrite(TEST2,0x81);			// Write values to test registers after wake up
        x=SPIRead(TEST2);
        SPIWrite(TEST1,0x35);
        SPIWrite(TEST0,0x09);
        SPIWrite(0x3F,value); 	// write received data from I2C device to Air booster pack
        AIR_CMD_REG(STX); 					// Sleep mode
        value++;
        time =0;
        if(value>5)
        {value=0;}
        AIR_CMD_REG(SPWD); 					// Sleep mode

    }



}//end of main
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
// Timer_A3 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
 switch( TA0IV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 10:
    if(time==3){
   	void AIR_WAKE();
	  }
   __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
            break;
 }
}
///////////////////////////////////////////////////////////////////////////////////////////////





