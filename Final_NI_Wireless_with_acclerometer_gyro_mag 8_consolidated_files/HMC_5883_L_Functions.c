
#include "HMC_5883L.h"
#include "HMC_5883L_Functions.h"
#include "I2C_Functions.h"
#include <msp430.h>

const unsigned char TxData3[] =              // array of HMC5883L values for writing
{
		CRA,	// Configuration Register A
		CRB,	// Configuration Register B
		MR		// Mode Register

};

const unsigned char TxData4[] =              // array of HMC5883L values for writing
{
		0x10,	// Configuration Register A
		0x20,	// Configuration Register B
		0x00	// Mode Register

};
