/*
 * display.c
 *
 *  Created on: Nov 23, 2020
 *      Author: Stancoj
 */

#include "display.h"

display_data_ dDisplayData = {0};
uint64_t disp_time = 0, disp_time_saved = 0;
char pole[4];
extern int start;
int pom_i = 0;
void updateDisplay(char pole[]);
void setDigit(uint8_t pos);

/*Reset (turn-off) all the segments of display*/
void resetSegments(void)
{
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_3);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
	//LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_3);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
}

/*Set (turn-on) all the segments of display*/
void setSegments(void)
{
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
	//LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
}

/* Reset (turn-off) all digits*/
void resetDigits(void)
{
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_7);

}

/* Reset (turn-on) all digits*/
void setDigits(void)
{
	DIGIT_1_ON;
	DIGIT_2_ON;
	DIGIT_3_ON;
	DIGIT_4_ON;
	DIGIT_TIME_ON;
}

void setDecimalPoint(void)
{
	LL_GPIO_ResetOutputPin(SEGMENTDP_PORT, SEGMENTDP_PIN);
}

/* Functions to display numbers 0 - 9 */
void setOne(void)
{
	// B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
}

void setTwo(void)
{
	// A,B,G,E,D
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void setThree(void)
{
	// A,B,G,C,D
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void setFour(void)
{
	// F,B,G,C
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
}

void setFive(void)
{
	// A,F,G,C,D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
}

void setSix(void)
{
	// A,F,G,E,C,D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
}

void setSeven(void)
{
	// A,B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
}

void setEight(void)
{
	// A,B,C,D,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}

void setNine(void)
{
	// A,B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setZero(void)
{
	// A,B,C,D,E,F
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}

////////

void setA(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}

void seta(void)
{
	// A,B,C,D,E,G
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}

void setb(void)
{
	// C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
}

void setC(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void setc(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void setd(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	
}

void setE(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	
}

void setF(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setG(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setH(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void seth(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setI(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setJ(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
}

void setL(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setn(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setO(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void seto(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setP(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setq(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setr(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setS(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void sett(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setU(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setu(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
}

void sety(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setK(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setM(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setV(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setW(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setX(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void setZ(void)
{
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

void set_(void)
{
	// D
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void setbodka(void)
{
	// D
	LL_GPIO_ResetOutputPin(SEGMENTDP_PORT, SEGMENTDP_PIN);
}

void setminus(void)
{
	// D
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}

/**
 * Pre-process number before it is displayed. Extract digits of the number
 */

/*
 * Turns required digit ON
 */
void setDigit(uint8_t pos)
{
	switch(pos)
	{
		case 0:
			DIGIT_4_ON;
			break;
		case 1:
			DIGIT_3_ON;
			break;
		case 2:
			DIGIT_2_ON;
			break;
		case 3:
			DIGIT_1_ON;
			break;
	}
}

/**
 * Display data in dDisplayData.
 * Sets every digit to display its value and decimal point.
 */
void updateDisplay(char pole[])
{
	for(uint8_t i = 0; i < 4; i++)
	{
		if((pole[i-1]) == '.'){
			setDigit(i);
			setbodka();
			//i=i+1;
		}
		if(pole[i] == '.'){
			pom_i = i+1;
		}
		else{
			pom_i = i;
		}
		switch(pole[pom_i])
		{
			case '0':
			  setDigit(i);
			  setZero();
			  break;
			case '1':
			  setDigit(i);
			  setOne();
			  break;
			case '2':
			  setDigit(i);
			  setTwo();
			  break;
			case '3':
			  setDigit(i);
			  setThree();
			  break;
			case '4':
			  setDigit(i);
			  setFour();
			  break;
			case '5':
			  setDigit(i);
			  setFive();
			  break;
			case '6':
			  setDigit(i);
			  setSix();
			  break;
			case '7':
			  setDigit(i);
			  setSeven();
			  break;
			case '8':
			  setDigit(i);
			  setEight();
			  break;
			case '9':
			  setDigit(i);
			  setNine();
			  break;
			case 'A':
				setDigit(i);
				setA();
				break;
			case 'a':
				setDigit(i);
				seta();
				break;
			case 'b':
				setDigit(i);
				setb();
				break;
			case 'B':
				setDigit(i);
				setb();
				break;
			case 'C':
				setDigit(i);
				setC();
				break;
			case 'c':
				setDigit(i);
				setc();
				break;
			case 'd':
				setDigit(i);
				setd();
				break;
			case 'D':
				setDigit(i);
				setd();
				break;
			case 'E':
				setDigit(i);
				setE();
				break;
			case 'e':
				setDigit(i);
				setE();
				break;
			case 'F':
				setDigit(i);
				setF();
				break;
			case 'f':
				setDigit(i);
				setF();
				break;
			case 'G':
				setDigit(i);
				setG();
				break;
			case 'g':
				setDigit(i);
				setG();
				break;
			case 'H':
				setDigit(i);
				setH();
				break;
			case 'h':
				setDigit(i);
				seth();
				break;
			case 'I':
				setDigit(i);
				setI();
				break;
			case 'i':
				setDigit(i);
				setI();
				break;
			case 'J':
				setDigit(i);
				setJ();
				break;
			case 'j':
				setDigit(i);
				setJ();
				break;
			case 'L':
				setDigit(i);
				setL();
				break;
			case 'l':
				setDigit(i);
				setL();
				break;
			case 'n':
				setDigit(i);
				setn();
				break;
			case 'N':
				setDigit(i);
				setn();
				break;
			case 'O':
				setDigit(i);
				setO();
				break;
			case 'o':
				setDigit(i);
				seto();
				break;
			case 'P':
				setDigit(i);
				setP();
				break;
			case 'p':
				setDigit(i);
				setP();
				break;
			case 'q':
				setDigit(i);
				setq();
				break;
			case 'Q':
				setDigit(i);
				setq();
				break;
			case 'r':
				setDigit(i);
				setr();
				break;
			case 'R':
				setDigit(i);
				setr();
				break;
			case 'S':
				setDigit(i);
				setS();
				break;
			case 's':
				setDigit(i);
				setS();
				break;
			case 't':
				setDigit(i);
				sett();
				break;
			case 'T':
				setDigit(i);
				sett();
				break;
			case 'U':
				setDigit(i);
				setU();
				break;
			case 'u':
				setDigit(i);
				setu();
				break;
			case 'y':
				setDigit(i);
				sety();
				break;
			case 'Y':
				setDigit(i);
				sety();
				break;
			case 'K':
				setDigit(i);
				setK();
				break;
			case 'k':
				setDigit(i);
				setK();
				break;
			case 'M':
				setDigit(i);
				setM();
				break;
			case 'm':
				setDigit(i);
				setM();
				break;
			case 'V':
				setDigit(i);
				setV();
				break;
			case 'v':
				setDigit(i);
				setV();
				break;
			case 'W':
				setDigit(i);
				setW();
				break;
			case 'w':
				setDigit(i);
				setW();
				break;
			case 'X':
				setDigit(i);
				setX();
				break;
			case 'x':
				setDigit(i);
				setX();
				break;
			case 'Z':
				setDigit(i);
				setZ();
				break;
			case 'z':
				setDigit(i);
				setZ();
				break;
			case '_':
				setDigit(i);
				set_();
				break;
			case '-':
				setDigit(i);
				setminus();
				break;
				/*
			case '.':
				if(i != 3){
					setDigit(i);
					setbodka();
				}
				break;
			*/
			/*
			case '-':
				setDigit(i);
				setminus();
				break;
				*/
				/*
				if(i == 3){
					LL_GPIO_SetOutputPin(SEGMENTDP_PORT, SEGMENTDP_PIN);
				}
				*/
		}

		/*
		if(dDisplayData.resolution == i)
		{
			setDecimalPoint();
		}
		*/
		disp_time_saved = disp_time;
		while((disp_time_saved + 2) > disp_time){};
		resetDigits();
		resetSegments();
		LL_GPIO_SetOutputPin(SEGMENTDP_PORT, SEGMENTDP_PIN);

	}

}

//Update displayed data and keep display ON
void TIM2_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_UPDATE(TIM2))
	{
		updateDisplay(pole);
	}

	LL_TIM_ClearFlag_UPDATE(TIM2);
}

