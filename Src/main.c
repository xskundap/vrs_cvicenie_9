/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "display.h"
#include <string.h>

#include "i2c.h"
#include "../temperature_humidity/hts.h"
#include "../pressure/lps25hb.h"
#include <math.h>

void SystemClock_Config(void);

extern uint64_t disp_time;

uint64_t saved_time;
double num_to_display = 10;

//char retazec[] = "123456789\0";
char retazec[] = "TEMP_00.0\0";
int i_bodka = -1;
int dlzka = 0;
int i = 0;
extern char pole[4];
int pom = 1;

float teplota[1];
float teplota_skuska[1];
float vlhkost_vzduchu[1];
float tlak[1];
float height;
int init = 0;

float teplota_akt;
float hum_akt;
float bar_akt;
float alt_akt;
uint8_t checkButtonState(GPIO_TypeDef* PORT, uint8_t PIN);
uint8_t switch_state = 0;

uint8_t tlacidlo = 0;

char temp_val[5];
uint8_t s_temp[10];

char hum_val[2];
uint8_t s_hum[7];

char bar_val[7];
uint8_t s_bar[12];

char alt_val[6];
uint8_t s_alt[11];

int main(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* SysTick_IRQn interrupt configuration */
 // NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();

  setSegments();
  setDigits();

  LL_mDelay(2000);

  resetDigits();
  resetSegments();

  MX_TIM2_Init();

  while(!(init = hts_init())){
	  LL_mDelay(100);
  }

  while(!(init = lps25hb_init())){
	  LL_mDelay(100);
  }

  dlzka = strlen(retazec);
  while (1)
  {
	  hts_get_temperature(teplota);
	  teplota_akt = teplota[0];
	  if(teplota_akt < -99.9){
		  teplota_akt = -99.9;
	  }
	  else if(teplota_akt > 99.9){
		  teplota_akt = 99.9;
	  }
	  LL_mDelay(50);
	  hts_get_humidity(vlhkost_vzduchu);
	  hum_akt = vlhkost_vzduchu[0];
	  if(hum_akt < 0){
		  hum_akt = 0;
	  }
	  else if(hum_akt > 99){
		  hum_akt = 99;
	  }
	  lps25hb_get_pressure(tlak);
	  bar_akt = tlak[0];
	  lps25hb_get_temp(teplota_skuska);
	  if(bar_akt < -9999.99){
		  bar_akt = -9999.99;
	  }
	  else if(bar_akt > 9999.99){
		  bar_akt = 9999.99;
	  }
	  height = ((powf((1013.25/tlak[0]),1/5.257)-1)*(teplota[0]+273.15))/0.0065;
	  alt_akt = height;
	  if(alt_akt < -9999.9){
		  alt_akt = -9999.9;
	  }
	  else if(alt_akt > 9999.9){
		  alt_akt = 9999.9;
	  }

	  if(tlacidlo == 0){

		  char s_temp[] = "TEMP_";

		  sprintf(temp_val, "%.1f", teplota_akt);
		  strcat(s_temp, temp_val);

		  memset(retazec, 0, 10);
		  strcat(retazec, s_temp);
		  dlzka = strlen(retazec)-1;

	  }
	  else if(tlacidlo == 1){
		  char s_hum[] = "HUM_";

		  sprintf(hum_val, "%.0f", hum_akt);
		  strcat(s_hum, hum_val);

		  memset(retazec, 0, 10);
		  strcat(retazec, s_hum);
		  dlzka = strlen(retazec);
	  }
	  else if(tlacidlo == 2){
		  char s_bar[] = "BAR_";

		  sprintf(bar_val, "%.2f", bar_akt);
		  strcat(s_bar, bar_val);

		  memset(retazec, 0, 10);
		  strcat(retazec, s_bar);
		  dlzka = strlen(retazec)-1;
	  }
	  else if(tlacidlo == 3){
		  char s_alt[] = "ALT_";

		  sprintf(alt_val, "%.1f", alt_akt);
		  strcat(s_alt, alt_val);

		  memset(retazec, 0, 10);
		  strcat(retazec, s_alt);
		  dlzka = strlen(retazec)-1;
	  }

	  if(pom == 1){
	  		  if(disp_time > (saved_time + 1000)){

	  			  pole[3] = retazec[i];
	  			  if(pole[3] == '.'){
	  				  i--;
	  				  //dlzka = dlzka-1;
	  				  i_bodka = 0;
	  				  pole[3] = retazec[i];
	  				  i++;
	  			  }

	  			  pole[2] = retazec[i+1];
	  			  if(pole[2] == '.'){
	  				  i--;
	  				 // dlzka = dlzka-1;
	  				  i_bodka = 1;
	  				  pole[2] = retazec[i+1];
	  				  i++;
	  			  }

	  			  pole[1] = retazec[i+2];
	  			  if(pole[1] == '.'){
	  				  i--;
	  				  //dlzka = dlzka-1;
	  				  i_bodka = 2;
	  				  pole[1] = retazec[i+2];
	  				  i++;
	  			  }

	  			  pole[0] = retazec[i+3];
	  			  if(pole[0] == '.'){
	  				  i--;
	  				  //dlzka = dlzka-1;
	  				  i_bodka = 3;
	  				  pole[0] = retazec[i+3];
	  				  i++;
	  			  }

	  			  pole[4] = '\0';

	  			  i++;

	  			  saved_time = disp_time;
	  			  if(i >= (dlzka-4)){
	  				  pom = 0;
	  			  }
	  		  }
	  	  }

	  	  if(pom == 0){
	  		  if(disp_time > (saved_time + 1000)){

	  			pole[3] = retazec[i];
	  			if(pole[3] == '.'){
	  				i++;
	  				//dlzka = dlzka-1;
	  				i_bodka = 0;
	  				pole[3] = retazec[i];
	  				i--;
	  			}

	  			pole[2] = retazec[i+1];
	  			if(pole[2] == '.'){
	  				i++;
	  				//dlzka = dlzka-1;
	  				i_bodka = 1;
	  				pole[2] = retazec[i+1];
	  				i--;
	  			}

	  			pole[1] = retazec[i+2];
	  			if(pole[1] == '.'){
	  				i++;
	  				//dlzka = dlzka-1;
	  				i_bodka = 2;
	  				pole[1] = retazec[i+2];
	  				i--;
	  			}

	  			pole[0] = retazec[i+3];
	  			if(pole[0] == '.'){
	  				i++;
	  				//dlzka = dlzka-1;
	  				i_bodka = 3;
	  				pole[0] = retazec[i+3];
	  				i--;
	  			}

	  			pole[4] = '\0';
	  			i--;

	  			saved_time = disp_time;
	  			if(i <= 0){
	  				pom = 1;
	  				i_bodka = -1;
	  			}
	  		  }
	  	  }

  }


}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SYSTICK_EnableIT();
  LL_SetSystemCoreClock(8000000);
}

/* USER CODE BEGIN 4 */
uint8_t checkButtonState(GPIO_TypeDef* PORT, uint8_t PIN)
{
	  //type your code for "checkButtonState" implementation here:
	uint8_t button_state = 0, timeout = 0;
	button_state = LL_GPIO_IsInputPinSet(Tlacidlo_GPIO_Port, Tlacidlo_Pin);

	if(button_state){
		tlacidlo++;
		if(tlacidlo <= 3){

				if(tlacidlo == 0){
					char retazec_pom[] = "TEMP_00.0\0";
					dlzka = strlen(retazec_pom);
					i = 0;
					memset(retazec, 0, 13);
					strcat(retazec, retazec_pom);
					pom = 1;
				}
				if(tlacidlo == 1){
					char retazec_pom[] = "HUM_00\0";
					dlzka = strlen(retazec_pom);
					i = 0;
					memset(retazec, 0, 13);
					strcat(retazec, retazec_pom);
					pom = 1;
				}
				if(tlacidlo == 2){
					char retazec_pom[] = "BAR_0000.00\0";
					dlzka = strlen(retazec_pom);
					i = 0;
					memset(retazec, 0, 13);
					strcat(retazec, retazec_pom);
					pom = 1;
				}
				if(tlacidlo == 3){
					char retazec_pom[] = "ALT_0000.0\0";
					dlzka = strlen(retazec_pom);
					i = 0;
					memset(retazec, 0, 13);
					strcat(retazec, retazec_pom);
					pom = 1;
				}
			}
		if(tlacidlo > 3){
			tlacidlo = 0;
			if(tlacidlo == 0){
				char retazec_pom[] = "TEMP_00.0\0";
				dlzka = strlen(retazec_pom);
				i = 0;
				memset(retazec, 0, 13);
				strcat(retazec, retazec_pom);
				pom = 1;
			}
		}
		return 1;
	}
	else{

		return 0;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
