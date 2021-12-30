/*
 * lps22hb.h
 *
 *  Created on: Dec 17, 2021
 *      Author: HP
 */

#ifndef LPS22HB_H_
#define LPS22HB_H_

#include "main.h"
#include "i2c.h"

#define 	LPS22HB_WHO_AM_I_VALUE					0xB1
#define 	LPS22HB_WHO_AM_I_ADDRES					0x0F
#define 	LPS22HB_ADDRESS							0xBA

#define 	LPS22HB_DEVICE_ADDRESS_0				0xB8
#define 	LPS22HB_DEVICE_ADDRESS_1				0xBA

#define 	LPS22HB_RES_CONF						0x1A
#define 	LPS22HB_ADDRESS_CTRL1					0x10
#define 	LPS22HB_ADDRESS_CTRL1_VAL				0x50
#define 	LPS22HB_ADDRESS_CTRL2					0x11
#define 	LPS22HB_ADDRESS_CTRL3					0x12

#define 	LPS22HB_STATUS_REG					    0x27

#define 	LPS22HB_PRESSOUT_H					    0x2A
#define 	LPS22HB_PRESSOUT_L					    0x29
#define 	LPS22HB_PRESSOUT_XL					    0x28

uint8_t lps22hb_init(void);
uint8_t lps22hb_read_byte(uint8_t reg_addr);
void lps22hb_write_byte(uint8_t reg_addr, uint8_t value);
void lps22hb_get_pressure(float* pressure);

#endif /* LPS22HB_H_ */
