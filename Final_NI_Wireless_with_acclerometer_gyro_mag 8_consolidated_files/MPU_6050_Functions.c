


#include "MPU_6050.h"
#include "MPU_6050_Functions.h"
#include "I2C_Functions.h"
#include <msp430.h>

const unsigned char TxData1[] =              // array of MPU6050 Registers for writing
{
		SMPLRT_DIV,
		CONFIG,
		GYRO_CONFIG,
		ACCEL_CONFIG,
		MOT_THR,
		FIFO_EN,
		I2C_MST_CTRL,
		I2C_SLV0_ADDR,
		I2C_SLV0_REG,
		I2C_SLV0_CTRL,
		I2C_SLV1_ADDR,
		I2C_SLV1_REG,
		I2C_SLV1_CTRL,
		I2C_SLV2_ADDR,
		I2C_SLV2_REG,
		I2C_SLV2_CTRL,
		I2C_SLV3_ADDR,
		I2C_SLV3_REG,
		I2C_SLV3_CTRL,
		I2C_SLV4_ADDR,
		I2C_SLV4_REG,
		I2C_SLV4_DO,
		I2C_SLV4_CTRL,
		I2C_SLV4_DI,
		I2C_MST_STATUS,
		INT_PIN_CFG,
		INT_ENABLE,
		I2C_SLV0_D0,
		I2C_SLV1_D0,
		I2C_SLV2_D0,
		I2C_SLV3_D0,
		I2C_MST_DELAY_CTRL,
		SIGNAL_PATH_RESET,
		MOT_DETECT_CTRL,
		USER_CTRL,
		PWR_MGT_1,
		PWR_MGT_2,
		FIFO_R_W
};

const unsigned char TxData2[] =              // array of MPU6050 values for writing
{
		0x07, //SMPLRT_DIV,
		0x00, //CONFIG,
		0x08, //GYRO_CONFIG,
		0x00, //ACCEL_CONFIG,
		0x00, //MOT_THR,
		0x00, //FIFO_EN,
		0x00, //I2C_MST_CTRL,
		0x00, //I2C_SLV0_ADDR,
		0x00, //I2C_SLV0_REG,
		0x00, //I2C_SLV0_CTRL,
		0x00, //I2C_SLV1_ADDR,
		0x00, //I2C_SLV1_REG,
		0x00, //I2C_SLV1_CTRL,
		0x00, //I2C_SLV2_ADDR,
		0x00, //I2C_SLV2_REG,
		0x00, //I2C_SLV2_CTRL,
		0x00, //I2C_SLV3_ADDR,
		0x00, //I2C_SLV3_REG,
		0x00, //I2C_SLV3_CTRL,
		0x00, //I2C_SLV4_ADDR,
		0x00, //I2C_SLV4_REG,
		0x00, //I2C_SLV4_DO,
		0x00, //I2C_SLV4_CTRL,
		0x00, //I2C_SLV4_DI,
		0x00, //I2C_MST_STATUS,
		0x00, //INT_PIN_CFG,
		0x00, //INT_ENABLE,
		0x00, //I2C_SLV0_D0,
		0x00, //I2C_SLV1_D0,
		0x00, //I2C_SLV2_D0,
		0x00, //I2C_SLV3_D0,
		0x00, //I2C_MST_DELAY_CTRL,
		0x00, //SIGNAL_PATH_RESET,
		0x00, //MOT_DETECT_CTRL,
		0x00, //USER_CTRL,
		0x00, //PWR_MGT_1,
		0x00, //PWR_MGT_2,
		0x00, //FIFO_R_W

};
