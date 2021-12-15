/*
 * hts.c
 *
 *  Created on: 15. 12. 2021
 *      Author: HP
 */

#include "hts.h"

uint8_t addres_temp = HTS_DEVICE_ADDRESS_0;

uint8_t hts_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_temp, 0));
}


void hts_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_temp, 0);
}


void hts_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_temp, 0);
}


int8_t hts_get_temp()
{
	uint8_t temp[2];
	hts_readArray(temp, HTS_ADDRESS_TEMP_L, 2);

	return (((int16_t)((temp[1] << 8) | temp[0])) >> 3)  + 25;
}


void hts_get_acc(float* x, float* y, float* z)
{
	uint8_t data[6];
	int16_t xx, yy, zz;

	uint8_t temp;

	//get current scale and use it for final calculation
    temp = hts_read_byte(HTS_ADDRESS_CTRL1);

	temp = temp >> 2;
    temp &= 0x03;			//full scale bits extracted

	hts_readArray(data, HTS_ADDRESS_ACCX, 6);

	xx = ((uint16_t)data[1]) << 8 | data[0];
	yy = ((uint16_t)data[3]) << 8 | data[2];
	zz = ((uint16_t)data[5]) << 8 | data[4];

	*x = (xx >> 4) / 1000.0f;
	*y = (yy >> 4) / 1000.0f;
	*z = (zz >> 4) / 1000.0f;
}


uint8_t hts_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = hts_read_byte(HTS_WHO_AM_I_ADDRES);

	if(val == HTS_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres_temp = HTS_DEVICE_ADDRESS_1;
		val = hts_read_byte(HTS_WHO_AM_I_ADDRES);
		if(val == HTS_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			//return status;
			
		}
	}

	//acc device init
	uint8_t ctrl1 = hts_read_byte(HTS_ADDRESS_CTRL1);
	ctrl1 &= ~0xFC;
	ctrl1 |= 0x70;
	hts_write_byte(HTS_ADDRESS_CTRL1, ctrl1);

	return status;
}


