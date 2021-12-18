/*
 * hts.h
 *
 *  Created on: 15. 12. 2021
 *      Author: HP
 */

#ifndef HTS_H_//
#define HTS_H_//

#include "main.h"
#include "i2c.h"
//
#define 	HTS_DEVICE_ADDRESS_0					0xBF
#define 	HTS_DEVICE_ADDRESS_1					0xBE
//
#define 	HTS_WHO_AM_I_VALUE						0xBC
#define 	HTS_WHO_AM_I_ADDRES						0x0F
//
#define 	HTS_ADDRESS_CTRL1						0x20
#define 	HTS_ADDRESS_CTRL1_VAL					0x81
#define 	HTS_ADDRESS_TEMP_L						0x20
//
#define 	HTS_T0_DEGC_X8							0x32
#define 	HTS_T0_T1_DEGC_H2						0x35
#define 	HTS_T0_OUT_L							0x3C
#define 	HTS_TEMP_OUT_L_REG						0x2A
// humidity
#define 	HTS_H0_RH_X2							0x30
#define 	HTS_H0_T0_OUT_L							0x36	//H0_T0_OUT
#define 	HTS_H1_T0_OUT_L							0x3A	//H1_T0_OUT
#define 	HTS_HR_OUT_L_REG						0x28	//H_T_OUT



uint8_t hts_init(void);
uint8_t hts_read_byte(uint8_t reg_addr);
void hts_write_byte(uint8_t reg_addr, uint8_t value);
int8_t hts_get_temp();
//
void hts_get_temperature(float* temperature);
void hts_get_humidity(float* humidity);

#endif /* HTS_H_ */
