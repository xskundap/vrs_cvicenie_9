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


#define 	HTS_DEVICE_ADDRESS_0					0xBF
#define 	HTS_DEVICE_ADDRESS_1					0xD7	//

#define 	HTS_WHO_AM_I_VALUE						0xBC
#define 	HTS_WHO_AM_I_ADDRES						0x0F

#define 	HTS_ADDRESS_CTRL1						0x20

#define 	HTS_ADDRESS_VAL_TEMP					0x2A
#define 	HTS_ADDRESS_ACCX						0x28
#define 	HTS_ADDRESS_ACCY						0x2A
#define 	HTS_ADDRESS_ACCZ						0x2C

#define 	HTS_ADDRESS_TEMP_L						0x20

#define 	HTS221_T0_DEGC_REG						0x32
#define 	HTS221_T0_OUT							0x3C
#define 	HTS221_T_OUT							0x2A
#define 	HTS221_MSB_T1_T0						0x35

uint8_t hts_init(void);
void hts_get_acc(float* x, float * y, float * z);
uint8_t hts_read_byte(uint8_t reg_addr);
void hts_write_byte(uint8_t reg_addr, uint8_t value);
int8_t hts_get_temp();

//
#endif /* HTS_H_ */

