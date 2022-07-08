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
//Date: 17/05/2014
//Revision Notes; Corrected magnetometer I2C IF algo. Write and Reads operate correctly now.
//
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//Header includes
#include <msp430.h>
#include "SPI_Functions.h"
#include "I2C_Functions.h"
#include "Air_Booster_Pack_Functions.h"
#include "Air_Booster_Pack.h"
#include "HMC_5883L.h"
#include "HMC_5883L_Functions.h"
#include "MPU_6050.h"
#include "MPU_6050_Functions.h"
///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
//#defines and global variables as well as extern variables declared here
#define SCL  BIT6
#define SDA  BIT7
#define MPU6050  0x01
#define HMC5883L  0x02
#define HMC5883LR  0x03
unsigned char *PTxData1;				// Pointer to TX data
unsigned char *PTxData2;				// Pointer to TX data
unsigned char *PTxData3;				// Pointer to TX data
unsigned char *PTxData4;				// Pointer to TX data
unsigned char *PRxData;					// Pointer to RX data
unsigned char TXByteCtr,RX_FLAG,RXByteCtr;		// Transmit byte counter
volatile unsigned char RxBuffer[20];   	// Allocate 128 byte of RAM
unsigned char sensorsel = 0;			// Variable for selecting which I2C peripheral to talk to
unsigned char time = 0;					// Variable for timer a loops
extern const unsigned char TxData1[38];	// Array of MPU6050 Registers for writing
extern const unsigned char TxData2[38];	// Array of MPU6050 values for writing
extern const unsigned char TxData3[3];	// Array of HMC5883L values for writing
extern const unsigned char TxData4[3];	// Array of HMC5883L values for writing
const unsigned char RxData[3]={0x3B,0x3D,0x06};	// Array that will hold two values, one for start of MPU6050 Read address and 1 for HMC5883L read address
char i,x=0;
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//Main function defined here
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;			// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;				// Calibrate MSP430 to run at 1MHz
    DCOCTL = CALDCO_1MHZ;
	P2OUT |= BIT0 + BIT1;
	P1DIR |= SDA | SCL | BIT0;  				// set SCL and SDA as outputs
	P1SEL  = SDA + SCL;  				// Sets up P1.6/7 as SDA/SCL
	P1SEL2 = SDA + SCL;
    SPISetup(); 						// Setup SPI port
    I2C_TX_Setup(); 					// Setup I2C port
    AIR_POR_RES(); 						// Reset Air module
    RF_868MHz_GFSK_CRC_RSSI_0DBM(); 	// Setup radio profile
    SPIWrite(PATABLE,0x50);				// Write PA value
    AIR_CMD_REG(SPWD); 					// Sleep mode
    PTxData1 = (unsigned char *)TxData1;// TX array1 start address
    PTxData2 = (unsigned char *)TxData2;// TX array2 start address
    PTxData3 = (unsigned char *)TxData3;// TX array3 start address
    PTxData4 = (unsigned char *)TxData4;// TX array4 start address
    PRxData = (unsigned char *)RxBuffer;// Start of RX buffer
    sensorsel = MPU6050;
    UCB0I2CSA = 0x68;

    while (x<sizeof TxData1) 			// Setup MPU6050 registers
    {
  	  x++;
      TXByteCtr = 2;              		// Load TX byte counter
      while (UCB0CTL1 & UCTXSTP);       // Ensure stop condition got sent
      UCB0CTL1 |= UCTR + UCTXSTT;       // I2C TX, start condition
      __bis_SR_register(CPUOFF + GIE); 	// Enter LPM0 w/ interrupts
    }	                              	// Remain in LPM0 until all data
                                        // is TX'd

    x=0;
    sensorsel = HMC5883L;
    UCB0I2CSA = 0x1E;
    while (x<sizeof TxData3) 			// Setup HMC5883L registers
    {
  	  x++;
      TXByteCtr = 2;              		// Load TX byte counter
      while (UCB0CTL1 & UCTXSTP);		// Ensure stop condition got sent
      UCB0CTL1 |= UCTR + UCTXSTT;		// I2C TX, start condition
      __bis_SR_register(CPUOFF + GIE);	// Enter LPM0 w/ interrupts
    }                                   // Remain in LPM0 until all data
                                 	 	// is TX'd

    while(1)
    {
        sensorsel = MPU6050;			// Select MPU6050 for I2C transaction
        UCB0I2CSA = 0x68;				// Load MPU6050 I2C address
        I2C_TX_Setup(); 				// Setup I2C port
    	PTxData2 = (unsigned char *)RxData;// TX array1 start address
        TXByteCtr = 1;              	// Load TX byte counter
        while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
        UCB0CTL1 |= UCTR + UCTXSTT;     // I2C TX, start condition
        __bis_SR_register(CPUOFF + GIE);// Enter LPM0 w/ interrupts
    	I2C_RX_Setup();
        RXByteCtr = 14;                 // Load RX byte counter
        PRxData = (unsigned char *)RxBuffer;// Start of RX buffer
        while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
        UCB0CTL1 |= UCTXSTT;            // I2C start condition
        __bis_SR_register(CPUOFF + GIE);// Enter LPM0 w/ interrupts
                                        // Remain in LPM0 until all data
                                        // is RX'd
        sensorsel = HMC5883L;
        UCB0I2CSA = 0x1E;
        I2C_TX_Setup(); 				// Setup I2C port
        TXByteCtr = 2;              	// Load TX byte counter
    	PTxData3 = (unsigned char *)&TxData3[2];// TX array3 Mode register address
    	PTxData4 = (unsigned char *)&TxData4[2];// TX array4 Single measurement mode value
        while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
        UCB0CTL1 |= UCTR + UCTXSTT;     // I2C TX, start condition
        __bis_SR_register(CPUOFF + GIE);// Enter LPM0 w/ interrupts
        while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
    	P1OUT = 0x01;
    	while(time<6)
    	{
        TACTL = TASSEL_2 + MC_2 + TAIE + ID_3;// SMCLK, continuous mode, interrupt enabled
        __bis_SR_register(CPUOFF + GIE);	// Enter LPM0 w/ interrupts
        time++;
    	}
    	P1OUT = 0x00;

    	void AIR_WAKE();
        sensorsel = HMC5883LR;
        TXByteCtr = 1;
        RXByteCtr = 6;              	// Load RX byte counter
        PRxData = (unsigned char *)&RxBuffer[14];// Start of RX buffer
        while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
        UCB0CTL1 |= UCTR + UCTXSTT;      		// I2C start condition
        __bis_SR_register(CPUOFF + GIE);// Enter LPM0 w/ interrupts
    	I2C_RX_Setup();
        sensorsel = HMC5883L;
        while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
        UCB0CTL1 |= UCTXSTT;            // I2C start condition
        __bis_SR_register(CPUOFF + GIE);// Enter LPM0 w/ interrupts
        P1OUT = 0x00;
        SPIWrite(TEST2,0x81);			// Write values to test registers after wake up
        SPIRead(TEST2);
        SPIWrite(TEST1,0x35);
        SPIWrite(TEST0,0x09);


        for (i=0;i<20;i++)
        {
        SPIWrite(0x3F,RxBuffer[i]); 	// write received data from I2C device to Air booster pack
        }
        x=AIR_ST_REG(TXBYTES); 			// check tx fifo is empty

        while(x>0)
        {
            __no_operation();			// Set breakpoint >>here<< and
            AIR_CMD_REG(STX); 			// transmit data
            x=AIR_ST_REG(TXBYTES);		// check tx fifo is empty
        }
        time =0;
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
   __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
            break;
 }
}
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it can be used to transmit any
// number of bytes by pre-loading TXByteCtr with the byte count. Also, TXData
// points to the next byte to transmit.
//------------------------------------------------------------------------------
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if(RX_FLAG==1)
	{
		switch(sensorsel)
			{
			case MPU6050:

				  RXByteCtr--;                              // Decrement RX byte counter
				  if (RXByteCtr)
				  {
				    *PRxData++ = UCB0RXBUF;                 // Move RX data to address PRxData
				    if (RXByteCtr == 1)                     // Only one byte left?
				      UCB0CTL1 |= UCTXSTP;                  // Generate I2C stop condition
				  }
				  else
				  {
				    *PRxData = UCB0RXBUF;                   // Move final RX data to PRxData
				    __bic_SR_register_on_exit(CPUOFF + GIE);      // Exit LPM0
				  }
			  break;

			case HMC5883L:
				  RXByteCtr--;                              // Decrement RX byte counter
				  if (RXByteCtr)
				  {
				    *PRxData++ = UCB0RXBUF;                 // Move RX data to address PRxData
				    if (RXByteCtr == 1)                     // Only one byte left?
				      UCB0CTL1 |= UCTXSTP;                  // Generate I2C stop condition
				  }
				  else
				  {
				    *PRxData = UCB0RXBUF;                   // Move final RX data to PRxData
				    __bic_SR_register_on_exit(CPUOFF + GIE);      // Exit LPM0
				  }
			  break;

			default :

				break;
			}
	}

	else
	{

		switch(sensorsel)
		{
		case MPU6050:


		  if (TXByteCtr==2)					// Check TX byte counter
		  {
			UCB0TXBUF = *PTxData1++;   		// Load TX buffer
			TXByteCtr--;             		// Decrement TX byte counter

		  }
		  else if (TXByteCtr==1)     		// Check TX byte counter
		  {
			UCB0TXBUF = *PTxData2++;		// Load TX buffer
			TXByteCtr--;             		// Decrement TX byte counter

		  }
		  else
		  {
			UCB0CTL1 |= UCTXSTP;        	// I2C stop condition
			IFG2 &= ~UCB0TXIFG;      		// Clear USCI_B0 TX int flag
			__bic_SR_register_on_exit(CPUOFF + GIE);      // Exit LPM0

		  }
		  break;

		case HMC5883L:
			if (TXByteCtr==2)   			// Check TX byte counter
			  {
				UCB0TXBUF = *PTxData3++; 	// Load TX buffer
				TXByteCtr--;     			// Decrement TX byte counter

			  }
			  else if (TXByteCtr==1)    	// Check TX byte counter
			  {
				UCB0TXBUF = *PTxData4++;  	// Load TX buffer
				TXByteCtr--;    			// Decrement TX byte counter

			  }
			  else
			  {
				UCB0CTL1 |= UCTXSTP;    	// I2C stop condition
				IFG2 &= ~UCB0TXIFG;    		// Clear USCI_B0 TX int flag
				__bic_SR_register_on_exit(CPUOFF + GIE);      // Exit LPM0

			  }
			break;
		case HMC5883LR:
			if (TXByteCtr==1)    	// Check TX byte counter
			{
				UCB0TXBUF = 0x03;  	// Load TX buffer
				TXByteCtr--;    			// Decrement TX byte counter
			}
			  else
			  {
				IFG2 &= ~UCB0TXIFG;    		// Clear USCI_B0 TX int flag
				__bic_SR_register_on_exit(CPUOFF + GIE);      // Exit LPM0

			  }
			break;

		default :

			break;
		}
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////



