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

#define 	HTS_WHO_AM_I_VALUE						0x6B	//...
#define 	HTS_WHO_AM_I_ADDRES						0x0F

#define 	HTS_ADDRESS_CTRL1						0x10

#define 	HTS_ADDRESS_ACCX						0x28
#define 	HTS_ADDRESS_ACCY						0x2A
#define 	HTS_ADDRESS_ACCZ						0x2C

#define 	HTS_ADDRESS_TEMP_L						0x20

uint8_t hts_init(void);
void hts_get_acc(float* x, float * y, float * z);
uint8_t hts_read_byte(uint8_t reg_addr);
void hts_write_byte(uint8_t reg_addr, uint8_t value);
int8_t hts_get_temp();


//
#endif /* HTS_H_ */
