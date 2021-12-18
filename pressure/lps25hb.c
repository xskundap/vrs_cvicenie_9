/*
 * lps25hb.c
 *
 *  Created on: Dec 17, 2021
 *      Author: HP
 */
#include "i2c.h"
#include "../pressure/lps25hb.h"

uint8_t addres_temp = 0xBB;

uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_temp, 0));
}

void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_temp, 0);
}

void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_temp, 1);
}

int8_t lps25hb_get_temp()
{
	uint8_t temp[2];
	lps25hb_readArray(temp, LPS25HB_ADDRESS, 2);

	return (((int16_t)((temp[1] << 8) | temp[0])) >> 3)  + 25;
}

void lps25hb_get_height(float* height){

}


void lps25hb_get_pressure(float* pressure){
	uint8_t PressOut_H, PressOut_L, PressOut_XL;
	uint32_t value, value_1;

//	PressOut_H = lps25hb_read_byte(LPS25HB_PRESSOUT_H);
	//PressOut_L = lps25hb_read_byte(LPS25HB_PRESSOUT_L);
	//PressOut_XL = lps25hb_read_byte(LPS25HB_PRESSOUT_XL);

	PressOut_H = lps25hb_read_byte(0x2A);
	PressOut_L = lps25hb_read_byte(0x29);
	PressOut_XL = lps25hb_read_byte(0x28);

	value = (PressOut_H << 16 | PressOut_L << 8 | PressOut_XL);

	*pressure = (float)(PressOut_H << 16 | PressOut_L << 8 | PressOut_XL) / 3019.0;
}

uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	//LPS25HB;

	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);

	if(val == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres_temp = LPS25HB_DEVICE_ADDRESS_1;
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);
		if(val == LPS25HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			//return status;
		}
	}

	//device init
	//uint8_t ctrl1 = lps25hb_read_byte(LPS25HB_ADDRESS_CTRL1);
	//ctrl1 &= ~0xFC;
	//ctrl1 |= 0x70;

	lps25hb_write_byte(LPS25HB_ADDRESS_CTRL1, LPS25HB_ADDRESS_CTRL1_VAL);

	return status;
}
