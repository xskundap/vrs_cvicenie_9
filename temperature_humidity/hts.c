/*
 * hts.c
 *
 *  Created on: 15. 12. 2021
 *      Author: HP
 */

#include "../temperature_humidity/hts.h"

#include "i2c.h"

//uint8_t addres_temp = 0xBEU;

uint8_t hts_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, HTS_DEVICE_ADDRESS_1, 0));
}

void hts_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, HTS_DEVICE_ADDRESS_1, 0);
}

void hts_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, HTS_DEVICE_ADDRESS_1, 1);
}


int8_t hts_get_temp()
{
	uint8_t temp[2];
	hts_readArray(temp, HTS_ADDRESS_TEMP_L, 2);

	return (((int16_t)((temp[1] << 8) | temp[0])) >> 3)  + 25;
}

void hts_get_temperature(float* temperature){
	int16_t T0_out, T1_out, T_out, T0_degC_x8_u16, T1_degC_x8_u16;
	int16_t T0_degC, T1_degC;
	uint8_t buffer[4], tmp;
	int32_t tmp32;
	float value;

	/*1. Read from 0x32 & 0x33 registers the value of coefficients T0_degC_x8 and T1_degC_x8*/
	hts_readArray(buffer, HTS_T0_DEGC_X8, 2);
	/*2. Read from 0x35 register the value of the MSB bits of T1_degC and T0_degC */
	tmp = hts_read_byte(HTS_T0_T1_DEGC_H2);
	/*Calculate the T0_degC and T1_degC values*/
	T0_degC_x8_u16 = (((uint16_t)(tmp & 0x03)) << 8) | ((uint16_t)buffer[0]);
	T1_degC_x8_u16 = (((uint16_t)(tmp & 0x0C)) << 6) | ((uint16_t)buffer[1]);
	T0_degC = T0_degC_x8_u16>>3;
	T1_degC = T1_degC_x8_u16>>3;
	/*3. Read from 0x3C & 0x3D registers the value of T0_OUT*/
	/*4. Read from 0x3E & 0x3F registers the value of T1_OUT*/
	hts_readArray(buffer, HTS_T0_OUT_L, 4);
	T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];
	T1_out = (((uint16_t)buffer[3])<<8) | (uint16_t)buffer[2];
	/* 5.Read from 0x2A & 0x2B registers the value T_OUT (ADC_OUT).*/
	hts_readArray(buffer, HTS_TEMP_OUT_L_REG, 2);
	T_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];
	/* 6. Compute the Temperature value by linear interpolation*/
	tmp32 = ((int32_t)(T_out - T0_out)) * ((int32_t)(T1_degC - T0_degC)*10);

	value = tmp32 /(T1_out - T0_out) + T0_degC*10;

	*temperature = value/10;
}

void hts_get_humidity(float* humidity){
	int16_t H0_T0_out, H1_T0_out, H_T_out;
	int16_t H0_rh, H1_rh;
	uint8_t buffer[2];
	int32_t tmp;
	uint16_t value;

	/* 1. Read H0_rH and H1_rH coefficients*/
	hts_readArray(buffer, HTS_H0_RH_X2, 2);
	H0_rh = buffer[0]>>1;
	H1_rh = buffer[1]>>1;

	/*2. Read H0_T0_OUT */
	hts_readArray(buffer, HTS_H0_T0_OUT_L, 2);
	H0_T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	/*3. Read H1_T0_OUT */
	hts_readArray(buffer, HTS_H1_T0_OUT_L, 2);
	H1_T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	/*4. Read H_T_OUT */
	hts_readArray(buffer, HTS_HR_OUT_L_REG, 2);
	H_T_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	/*5. Compute the RH [%] value by linear interpolation */
	tmp = ((int32_t)(H_T_out - H0_T0_out)) * ((int32_t)(H1_rh - H0_rh)*10);
	value = (uint16_t)(tmp/(H1_T0_out - H0_T0_out) + H0_rh*10);

	/* Saturation condition*/
	if(value>1000) value = 1000;

	*humidity = (float)value/10.0;
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
		//addres_temp = HTS_DEVICE_ADDRESS_1;
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

	hts_write_byte(HTS_ADDRESS_CTRL1, HTS_ADDRESS_CTRL1_VAL);

	return status;
}


