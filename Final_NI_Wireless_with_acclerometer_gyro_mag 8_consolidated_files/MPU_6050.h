/*
 * MPU_6050.h
 *
 *  Created on: 23 Nov 2013
 *      Author: nirani
 */

#ifndef MPU_6050_H_
#define MPU_6050_H_

// Configuration Registers
#define SELF_TEST_X        0x0D        // Accelerometer/Gyroscope X Self Test
#define SELF_TEST_Y        0x0E        // Accelerometer/Gyroscope Y Self Test
#define SELF_TEST_Z        0x0F        // Accelerometer/Gyroscope Z Self Test
#define SELF_TEST_A        0x10        // Accelerometer/Gyroscope A Self Test
#define SMPLRT_DIV         0x19        // Sample rate division
#define CONFIG             0x1A        //
#define GYRO_CONFIG        0x1B        // Packet length
#define ACCEL_CONFIG       0x1C        // Packet automation control
#define MOT_THR            0x1F        // Packet automation control
#define FIFO_EN            0x23        // Device address
#define I2C_MST_CTRL       0x24        // Channel number
#define I2C_SLV0_ADDR      0x25        // Frequency synthesizer control
#define I2C_SLV0_REG       0x26        // Frequency synthesizer control
#define I2C_SLV0_CTRL      0x27        // Frequency control word, high byte
#define I2C_SLV1_ADDR      0x28        // Frequency control word, middle byte
#define I2C_SLV1_REG       0x29        // Frequency control word, low byte
#define I2C_SLV1_CTRL      0x2A        // Modem configuration
#define I2C_SLV2_ADDR      0x2B        // Modem configuration
#define I2C_SLV2_REG       0x2C        // Modem configuration
#define I2C_SLV2_CTRL      0x2D        // Modem configuration
#define I2C_SLV3_ADDR      0x2E        // Modem configuration
#define I2C_SLV3_REG       0x2F        // Modem deviation setting
#define I2C_SLV3_CTRL      0x30        // Main Radio Cntrl State Machine config
#define I2C_SLV4_ADDR      0x31        // Main Radio Cntrl State Machine config
#define I2C_SLV4_REG       0x32        // Main Radio Cntrl State Machine config
#define I2C_SLV4_DO        0x33        // Frequency Offset Compensation config
#define I2C_SLV4_CTRL      0x34        // Bit Synchronization configuration
#define I2C_SLV4_DI        0x35        // AGC control
#define I2C_MST_STATUS     0x36        // AGC control
#define INT_PIN_CFG        0x37        // AGC control
#define INT_ENABLE         0x38        // High byte Event 0 timeout
#define INT_STATUS         0x3A        // Low byte Event 0 timeout
#define ACCEL_XOUT_H       0x3B        // Wake On Radio control
#define ACCEL_XOUT_L       0x3C        // Front end RX configuration
#define ACCEL_YOUT_H       0x3D        // Front end TX configuration
#define ACCEL_YOUT_L       0x3E        // Frequency synthesizer calibration
#define ACCEL_ZOUT_H       0x3F        // Frequency synthesizer calibration
#define ACCEL_ZOUT_L       0x40        // Frequency synthesizer calibration
#define TEMP_OUT_H         0x41        // Frequency synthesizer calibration
#define TEMP_OUT_L         0x42        // RC oscillator configuration
#define GYRO_XOUT_H        0x43        // RC oscillator configuration
#define GYRO_XOUT_L        0x44        // Frequency synthesizer cal control
#define GYRO_YOUT_H        0x45        // Production test
#define GYRO_YOUT_L        0x46        // AGC test
#define GYRO_ZOUT_H        0x47        // Various test settings
#define GYRO_ZOUT_L        0x48        // Various test settings
#define EXT_SENS_DATA_00   0x49        // Various test settings
#define EXT_SENS_DATA_01   0x4A        // Wake On Radio control
#define EXT_SENS_DATA_02   0x4B        // Front end RX configuration
#define EXT_SENS_DATA_03   0x4C        // Front end TX configuration
#define EXT_SENS_DATA_04   0x4D        // Frequency synthesizer calibration
#define EXT_SENS_DATA_05   0x4E        // Frequency synthesizer calibration
#define EXT_SENS_DATA_06   0x4F        // Frequency synthesizer calibration
#define EXT_SENS_DATA_07   0x50        // Frequency synthesizer calibration
#define EXT_SENS_DATA_08   0x51        // RC oscillator configuration
#define EXT_SENS_DATA_09   0x52        // RC oscillator configuration
#define EXT_SENS_DATA_10   0x53        // Frequency synthesizer cal control
#define EXT_SENS_DATA_11   0x54        // Production test
#define EXT_SENS_DATA_12   0x55        // AGC test
#define EXT_SENS_DATA_13   0x56        // Various test settings
#define EXT_SENS_DATA_14   0x57        // Various test settings
#define EXT_SENS_DATA_15   0x58        // Various test settings
#define EXT_SENS_DATA_16   0x59        // Wake On Radio control
#define EXT_SENS_DATA_17   0x5A        // Front end RX configuration
#define EXT_SENS_DATA_18   0x5B        // Front end TX configuration
#define EXT_SENS_DATA_19   0x5C        // Frequency synthesizer calibration
#define EXT_SENS_DATA_20   0x5D        // Frequency synthesizer calibration
#define EXT_SENS_DATA_21   0x5E        // Frequency synthesizer calibration
#define EXT_SENS_DATA_22   0x5F        // Frequency synthesizer calibration
#define EXT_SENS_DATA_23   0x60        // RC oscillator configuration
#define I2C_SLV0_D0        0x63        // RC oscillator configuration
#define I2C_SLV1_D0        0x64        // Frequency synthesizer cal control
#define I2C_SLV2_D0        0x65        // Production test
#define I2C_SLV3_D0        0x66        // AGC test
#define I2C_MST_DELAY_CTRL 0x67        // Various test settings
#define SIGNAL_PATH_RESET  0x68        // Various test settings
#define MOT_DETECT_CTRL    0x69        // Various test settings#define WORCTRL      0x3B        // Wake On Radio control
#define USER_CTRL          0x6A        // Front end RX configuration
#define PWR_MGT_1          0x6B        // Front end TX configuration
#define PWR_MGT_2          0x6C        // Frequency synthesizer calibration
#define FIFO_COUNTH        0x72        // Frequency synthesizer calibration
#define FIFO_COUNTL        0x73        // Frequency synthesizer calibration
#define FIFO_R_W           0x74        // Frequency synthesizer calibration
#define WHO_AM_I           0x75        // RC oscillator configuration




#endif /* MPU_6050_H_ */
