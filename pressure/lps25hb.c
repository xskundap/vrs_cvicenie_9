/*
 * lps22hb.c
 *
 *  Created on: Dec 17, 2021
 *      Author: HP
 */
#include "i2c.h"

#include "lps22hb.h"

uint8_t addres_temp = 0xBA;

uint8_t lps22hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_temp, 0));
}

void lps22hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_temp, 0);
}

void lps22hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_temp, 1);
}

void lps22hb_get_pressure(float* pressure){
	uint8_t PressOut_H, PressOut_L, PressOut_XL;

	PressOut_H = lps22hb_read_byte(0x2A);
	PressOut_L = lps22hb_read_byte(0x29);
	PressOut_XL = lps22hb_read_byte(0x28);

	*pressure = (float)(PressOut_H << 16 | PressOut_L << 8 | PressOut_XL) / 4096.0;
}

uint8_t lps22hb_init(void)
{

	uint8_t status = 1;

	//LPS22HB;
	LL_mDelay(100);

	uint8_t val = lps22hb_read_byte(LPS22HB_WHO_AM_I_ADDRES);

	if(val == LPS22HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres_temp = LPS22HB_DEVICE_ADDRESS_1;
		val = lps22hb_read_byte(LPS22HB_WHO_AM_I_ADDRES);
		if(val == LPS22HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
		}
	}

	//lps22hb_write_byte(LPS22HB_ADDRESS_CTRL2, 0b10000000);
	LL_mDelay(100);
	lps22hb_write_byte(LPS22HB_ADDRESS_CTRL2, 0b00010000); //default
	//lps22hb_write_byte(LPS22HB_ADDRESS_CTRL1, 0b10110000);
	lps22hb_write_byte(LPS22HB_ADDRESS_CTRL1, 0b01010000); //75Hz
	LL_mDelay(100);
	//lps22hb_write_byte(LPS22HB_RES_CONF, 0b11001111);
	lps22hb_write_byte(LPS22HB_ADDRESS_CTRL3, 0b00000000); //default
	return status;
}
