/*
 * Air_Booster_Pack_Functions.h
 *
 *  Created on: 14 Aug 2013
 *      Author: nirani
 */

#ifndef AIR_BOOSTER_PACK_FUNCTIONS_H_
#define AIR_BOOSTER_PACK_FUNCTIONS_H_


// Configuration register setup
void RF_868MHz_GFSK_CRC_RSSI_0DBM();
/*
void RF_868MHz_2FSK_CRC_RSSI_POS1DBM();
void RF_868MHz_2FSK_CRC_RSSI_POS2DBM();
void RF_868MHz_2FSK_CRC_RSSI_POS3DBM();
void RF_868MHz_2FSK_CRC_RSSI_POS4DBM();
void RF_868MHz_2FSK_CRC_RSSI_NEG1DBM();
void RF_868MHz_2FSK_CRC_RSSI_NEG6DBM();
void RF_868MHz_2FSK_CRC_RSSI_NEG12DBM();
*/

//Command access
void AIR_CMD_REG(char);

//Status access

char AIR_ST_REG(char);
//Power on reset
void AIR_POR_RES();

void AIR_WAKE();



#endif /* AIR_BOOSTER_PACK_FUNCTIONS_H_ */
