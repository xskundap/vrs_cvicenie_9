/*
 * hts.c
 *
 *  Created on: 15. 12. 2021
 *      Author: HP
 */

#include "hts.h"
#include "i2c.h"

uint8_t addres_temp = 0xbe;


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
	i2c_master_read(data, length, reg, addres_temp, 1);
}


int8_t hts_get_temp()
{
	uint8_t temp[2];
	hts_readArray(temp, HTS_ADDRESS_TEMP_L, 2);

	return (((int16_t)((temp[1] << 8) | temp[0])) >> 3)  + 25;
}

int16_t HTS221_Get_Temperature()
{
	 int16_t T0_out, T1_out, T_out, T0_degC_x8_u16, T1_degC_x8_u16;
	 int16_t T0_degC, T1_degC;
	 uint8_t buffer[4], tmp;
	 int32_t tmp32;
	 int16_t value;

	/*1. Read from 0x32 & 0x33 registers the value of coefficients T0_degC_x8 and T1_degC_x8*/
	 hts221_readArray(buffer, HTS221_T0_DEGC_REG, 2);

	/*2. Read from 0x35 register the value of the MSB bits of T1_degC and T0_degC */
	 tmp = hts221_read_byte(HTS221_MSB_T1_T0);

	/*Calculate the T0_degC and T1_degC values*/
	 T0_degC_x8_u16 = (((uint16_t)(tmp & 0x03)) << 8) | ((uint16_t)buffer[0]);
	 T1_degC_x8_u16 = (((uint16_t)(tmp & 0x0C)) << 6) | ((uint16_t)buffer[1]);
	 T0_degC = T0_degC_x8_u16>>3;
	 T1_degC = T1_degC_x8_u16>>3;

	/*3. Read from 0x3C & 0x3D registers the value of T0_OUT*/
	/*4. Read from 0x3E & 0x3F registers the value of T1_OUT*/
	 hts221_readArray(buffer, HTS221_T0_OUT, 4);

	 T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];
	 T1_out = (((uint16_t)buffer[3])<<8) | (uint16_t)buffer[2];

	/* 5.Read from 0x2A & 0x2B registers the value T_OUT (ADC_OUT).*/
	 hts221_readArray(buffer, HTS221_T_OUT, 2);

	 T_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];
	/* 6. Compute the Temperature value by linear interpolation*/
	 tmp32 = ((int32_t)(T_out - T0_out)) * ((int32_t)(T1_degC - T0_degC)*10);
	 value = tmp32 /(T1_out - T0_out) + T0_degC*10;
	 return value;
}
void hts_get_acc(float* x, float* y, float* z)
{
	uint8_t data[6];
	int16_t xx, yy, zz;

	uint8_t temp;

	//get current scale and use it for final calculation
    temp = hts_read_byte(HTS_ADDRESS_CTRL1);

	temp = temp >> 3;
    temp &= 0x03;			//full scale bits extracted

	//hts_readArray(data, HTS_ADDRESS_ACCX, 6);
    hts_readArray(data, HTS_ADDRESS_VAL_TEMP, 2);

    xx = ((uint16_t)data[1]) << 8 | data[0];
    /*
	xx = ((uint16_t)data[1]) << 8 | data[0];
	yy = ((uint16_t)data[3]) << 8 | data[2];
	zz = ((uint16_t)data[5]) << 8 | data[4];

	*x = (xx >> 4) / 1000.0f;
	*y = (yy >> 4) / 1000.0f;
	*z = (zz >> 4) / 1000.0f;
	*/
    *x = (xx >> 4) / 1000.0f;

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
	//uint8_t ctrl1 = hts_read_byte(HTS_ADDRESS_CTRL1);
	//ctrl1 &= ~0xFC;
	//ctrl1 |= 0x70;

	hts_write_byte(HTS_ADDRESS_CTRL1, 0x81);

	return status;
}


