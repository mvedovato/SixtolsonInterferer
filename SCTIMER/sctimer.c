/*
 * sctimer.c
 *
 *  Created on: 1 sep. 2021
 *      Author: mariano
 */

#include "sctimer.h"
#include "gpio.h"

const uint8_t vectorDutys[]={100,56,0,0,0,0,0,0,0,0,100,100,100,100,52,0,0,0,0,0,100,100,100,100,100,100,100,4,0,0,100,100,100,100,100,100,100,100,87,0,100,100,100,100,100,100,100,100,100,84,100,100,100,100,100,100,100,100,100,84,100,100,100,100,100,100,100,100,87,0,100,100,100,100,100,100,100,4,0,0,100,100,100,100,52,0,0,0,0,0,100,56,0,0,0,0,0,0,0,0};
//const uint8_t vectorDutys[]={100,100,100,100,100,100,100,100,100,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//const uint8_t vectorDutys[]={100, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void Inicializar_SCTimer( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7) | (1 << 8);			// 8= SCTIMER 7=SWM
	SYSCON->PRESETCTRL0 |= (1 << 8);						// 8= SCTIMER clear the timer reset

	SYSCON->SCTCLKSEL = 1;										// 1:Main clock 24MHz
	SYSCON->SCTCLKDIV = 1;										// divided by n


	SWM0->PINASSIGN.PINASSIGN7 &= (~(0xff << (24)));			// SCT_OUT0 = PWM PIO0.8 -> pin 21
	SWM0->PINASSIGN.PINASSIGN7 |= (8 << (24));

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (0)));				// SCT_OUT1 = PWM PIO0.9
	SWM0->PINASSIGN.PINASSIGN8 |= (9 << (0));					// PIO0.9 OUT1 -> pin 22

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (8)));				// SCT_OUT2 = PWM PIO0.13
	SWM0->PINASSIGN.PINASSIGN8 |= (13 << (8));					// PIO0.13 OUT2 -> pin 26

	SCT0->CONFIG |= (1 << 0) | (1 << 17);
	SCT0->SCTMATCH[0] = FREQ_PRINCIPAL/(PWM_FREQ*1);
	SCT0->SCTMATCHREL[0] = FREQ_PRINCIPAL/(PWM_FREQ*1);

	SCT0->EVENT[0].STATE = 	0xFFFFFFFF;
	SCT0->EVENT[0].CTRL = 	0 | (1 << 12);

	SCT0->OUTPUT = 0xC;										//Esto no tiene efecto luego
	SCT0->RES = 0b01010101;									//Habría que hacer pruebas
	SCT0->EVEN = 1;
	//SCT0->EVEN = 3;

	SCT0->EVENT[1].STATE = 	0xFFFFFFFF;
	SCT0->EVENT[1].CTRL = 	1 | (1 << 12);		//Referido a Match1 Combmode 1== Match only

	#ifdef	DUTYaCTIVOaLTO
		SCT0->OUT[0].SET = 1;
		SCT0->OUT[0].CLR = (1<<1);
	#else
		SCT0->OUT[0].SET = (1<<1);
		SCT0->OUT[0].CLR = 1;
	#endif

	//SCT0->SCTMATCH[1] = FREQ_PRINCIPAL/(PWM_FREQ*2);
	//SCT0->SCTMATCHREL[1] = FREQ_PRINCIPAL/(PWM_FREQ*2);

	SCT0->SCTMATCH[1] = 0;						//Duty pwm1
	SCT0->SCTMATCHREL[1] = 0;					//Duty pwm1

	//-------------------------------------------
	SCT0->SCTMATCH[2] = FREQ_PRINCIPAL/(PWM_FREQ*1);
	SCT0->SCTMATCHREL[2] = FREQ_PRINCIPAL/(PWM_FREQ*1);

	SCT0->EVENT[2].STATE = 	0xFFFFFFFF;
	SCT0->EVENT[2].CTRL = 	2 | (1 << 12);

	SCT0->EVENT[3].STATE = 	0xFFFFFFFF;
	SCT0->EVENT[3].CTRL = 	3 | (1 << 12);	//Referido a Match3 Combmode 1== Match only

	#ifdef	DUTYaCTIVOaLTO
		SCT0->OUT[1].SET = (1<<2);				//Actua en base a evento2
		SCT0->OUT[1].CLR = (1<<3);				//Actua en base a evento3
	#else
		SCT0->OUT[1].SET = (1<<3);				//Actua en base a evento3
		SCT0->OUT[1].CLR = (1<<2);				//Actua en base a evento2
	#endif

		//SCT0->SCTMATCH[3] = FREQ_PRINCIPAL/(PWM_FREQ*2);
	//SCT0->SCTMATCHREL[3] = FREQ_PRINCIPAL/(PWM_FREQ*2);

	SCT0->SCTMATCH[3] = 0;					//Duty pwm2
	SCT0->SCTMATCHREL[3] = 0;				//Duty pwm2

	//-------------------------------------------------
	SCT0->SCTMATCH[4] = FREQ_PRINCIPAL/(PWM_FREQ*1);
	SCT0->SCTMATCHREL[4] = FREQ_PRINCIPAL/(PWM_FREQ*1);

	SCT0->EVENT[4].STATE = 	0xFFFFFFFF;
	SCT0->EVENT[4].CTRL = 	4 | (1 << 12);

	SCT0->EVENT[5].STATE = 	0xFFFFFFFF;
	SCT0->EVENT[5].CTRL = 	5 | (1 << 12);		//Referido a Match5 Combmode 1== Match only

	#ifdef	DUTYaCTIVOaLTO
		SCT0->OUT[2].SET = (1<<4);					//Actua en base a evento4
		SCT0->OUT[2].CLR = (1<<5);					//Actua en base a evento5
	#else
		SCT0->OUT[2].SET = (1<<5);					//Actua en base a evento5
		SCT0->OUT[2].CLR = (1<<4);					//Actua en base a evento4
	#endif
	//SCT0->SCTMATCH[5] = FREQ_PRINCIPAL/(PWM_FREQ*2);
	//SCT0->SCTMATCHREL[5] = FREQ_PRINCIPAL/(PWM_FREQ*2);

	SCT0->SCTMATCH[5] = 0;						//Duty pwm3
	SCT0->SCTMATCHREL[5] = 0;					//Duty pwm3
	//-------------------------------------------------

	NVIC->ISER[0] = (1 << 9);

	SCT0->CTRL &= ~(1 << 2);					//Start SCTimer

	PWM1_set( 65 );		//6.5
	PWM2_set( 90 );		//9%
	PWM3_set( 100 );	//10%

}

void SCTimer_Init( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7) | (1 << 8);			// 8= SCTIMER 7=SWM
		SYSCON->PRESETCTRL0 |= (1 << 8);			// 8= SCTIMER clear the timer reset

		SYSCON->SCTCLKSEL = 1;										// 1:Main clock 48MHz
		SYSCON->SCTCLKDIV = 1;										// divided by n


		SWM0->PINASSIGN.PINASSIGN7 &= (~(0xff << (24)));			// SCT_OUT0 = PWM PIO0.8 -> pin 21
		SWM0->PINASSIGN.PINASSIGN7 |= (8 << (24));

		SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (0)));				// SCT_OUT1 = PWM PIO0.9
		SWM0->PINASSIGN.PINASSIGN8 |= (9 << (0));					// PIO0.9 OUT1 -> pin 22

		SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (8)));				// SCT_OUT2 = PWM PIO0.13
		SWM0->PINASSIGN.PINASSIGN8 |= (13 << (8));					// PIO0.13 OUT2 -> pin 26

		SCT0->CONFIG |= (1 << 0) | (1 << 17);
		SCT0->SCTMATCH[0] = FREQ_PRINCIPAL/(PWM_FREQ*1);
		SCT0->SCTMATCHREL[0] = FREQ_PRINCIPAL/(PWM_FREQ*1);

		SCT0->EVENT[0].STATE = 	0xFFFFFFFF;
		SCT0->EVENT[0].CTRL = 	0 | (1 << 12);

		SCT0->OUTPUT = 0xC;
		SCT0->RES = 0b01010101;
		SCT0->EVEN = 1;

		SCT0->EVENT[1].STATE = 	0xFFFFFFFF;
		SCT0->EVENT[1].CTRL = 	1 | (1 << 12);		//Referido a Match1 Combmode 1== Match only
		SCT0->OUT[0].SET = 1;
		SCT0->OUT[0].CLR = (1<<1);

		//SCT0->SCTMATCH[1] = FREQ_PRINCIPAL/(PWM_FREQ*2);
		//SCT0->SCTMATCHREL[1] = FREQ_PRINCIPAL/(PWM_FREQ*2);

		SCT0->SCTMATCH[1] = 0;
		SCT0->SCTMATCHREL[1] = 0;


		NVIC->ISER[0] = (1 << 9);

		SCT0->CTRL &= ~(1 << 2);

		PWM1_set( 90 );	//9%
}


void SCT_Init(void)
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7) | (1 << 8);				// enable the SWM and SCT clock

	//Las siguientes dos lineas no tienen efecto
	//SYSCON->SCTCLKSEL = 2;										// 1:Main clock 48MHz
	//SYSCON->SCTCLKDIV = 20;										// divided by n


	SWM0->PINASSIGN.PINASSIGN7 &= (~(0xff << (24)));			// SCT_OUT0 = PWM PIO0.8
	SWM0->PINASSIGN.PINASSIGN7 |= (8 << (24));					// PIO0.8 OUT0 -> pin 21

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (0)));				// SCT_OUT1 = PWM PIO0.9
	SWM0->PINASSIGN.PINASSIGN8 |= (9 << (0));					// PIO0.9 OUT1 -> pin 22

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (8)));				// SCT_OUT2 = PWM PIO0.10
	SWM0->PINASSIGN.PINASSIGN8 |= (10 << (8));					// PIO0.10 OUT2 -> pin 23

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (16)));			// SCT_OUT3 = PWM PIO0.11
	SWM0->PINASSIGN.PINASSIGN8 |= (11 << (16));					// PIO0.11 OUT3 -> pin 24

	SCT0->CONFIG |= (1 << 0) | (1 << 17);// unified timer, auto limit
	SCT0->SCTMATCH[0] = pwm_cycle;
	SCT0->SCTMATCHREL[0] = pwm_val1;
	SCT0->SCTMATCH[1] = pwm_val1;
	SCT0->SCTMATCHREL[1] = pwm_val2;
	SCT0->SCTMATCH[2] = pwm_val2;
	SCT0->SCTMATCHREL[2] = pwm_val3;
	SCT0->SCTMATCH[3] = pwm_val3;
	SCT0->SCTMATCHREL[3] = pwm_val4;
	SCT0->SCTMATCH[4] = pwm_val4;// match 0 on PWM cycle
	SCT0->SCTMATCHREL[4]= pwm_cycle;

	SCT0->EVENT[0].STATE = 0xFFFFFFFF; // event 0 happens in all states
	SCT0->EVENT[0].CTRL= (0 << 0) | (1 << 12); // match 0 (pwm_cycle) only condition


	SCT0->EVENT[1].STATE = 0xFFFFFFFF; // event 1 happens in all states
	SCT0->EVENT[1].CTRL = (1 << 0) | (1 << 12); // match 1 (pwm_val1) only condition


	SCT0->EVENT[2].STATE = 0xFFFFFFFF; // event 2 happens in all states
	SCT0->EVENT[2].CTRL = (2 << 0) | (1 << 12); // match 2 (pwm_val2) only condition

	SCT0->EVENT[3].STATE = 0xFFFFFFFF; // event 3 happens in all states
	SCT0->EVENT[3].CTRL = (3 << 0) | (1 << 12); // match 3 (pwm_val3) only condition

	SCT0->EVENT[4].STATE = 0xFFFFFFFF; // event 4 happens in all states
	SCT0->EVENT[4].CTRL = (4 << 0) | (1 << 12); // match 4 (pwm_val4) only condition

	SCT0->EVENT[5].STATE = 0xFFFFFFFF; // event 5 happens in all states
	SCT0->EVENT[5].CTRL = (0 << 10) | (2 << 12); // IN_0 LOW only condition

	SCT0->OUT[0].SET = (1 << 0); // event 0 sets OUT0 (PWM1)
	SCT0->OUT[0].CLR = (1 << 1) | (1 << 5 ); // event 1 and 5 clear OUT0 (PWM1)

	SCT0->OUT[1].SET = (1 << 0); // event 0 sets OUT1 (PWM2)
	SCT0->OUT[1].CLR = (1 << 2) | (1 << 5 ); // event 2 and 5 clear OUT2 (PWM2)

	SCT0->OUT[2].SET = (1 << 3) | (1 << 5 ); // event 3 and 5  sets OUT2 (PWM3)
	SCT0->OUT[2].CLR = (1 << 0); // event 0 clear OUT2 (PWM3)

	SCT0->OUT[3].SET = (1 << 4) | (1 << 5); // event 4 and 5 sets OUT3 (PWM4)
	SCT0->OUT[3].CLR = (1 << 0); // event 0 and 5 clear OUT3 (PWM4)

	SCT0->OUTPUT = 0x0000000C; // default clear OUT0/1 and set OUT2/3

	SCT0->RES = 0x0000005A; // conflict: Inactive state takes precedence
							// SCT2_OUT0/1: Inactive state low
							// SCT2_OUT2/3: Inactive state high

	SCT0->HALT = ( 1 << 5); // event 5 will halt the timer
	SCT0->LIMIT = ( 1 << 5); // event 5 will limit the timer
	SCT0->EVEN = (1 << 0) | ( 1 << 5); // event 0 and 5 will generate an irq

	NVIC->ISER[0] = (1 << 9); 					// enable interrupt ISE_SCT_IRQ EVFLAG SCT event

	SCT0->CTRL &= ~(1 << 2);									// start timer
}
void PWM1_set(uint32_t value)
{

	if (value == 0)
		SCT0->SCTMATCHREL[1] = 0;								// check val between 0% and 100%
	else
	{
		if ( value >= CINCOpORCIENTO && value <= DIEZpORCIENTO)
		{
			SCT0->SCTMATCHREL[1] = (value*DOScOMAcINCOmILIS)/DOCEcOMACINCOpORCIENTO;
		}
		else
		{
			SCT0->SCTMATCHREL[1] = FREQ_PRINCIPAL/(PWM_FREQ*1 - 1);				// set to 100% duty cycle
		}
	}

}

void PWM2_set(uint32_t value)
{

	if (value == 0)
		SCT0->SCTMATCHREL[3] = 0;								// check val between 0% and 100%
	else
	{
		if ( value >= CINCOpORCIENTO && value <= DIEZpORCIENTO)
		{
			SCT0->SCTMATCHREL[3] = (value*DOScOMAcINCOmILIS)/DOCEcOMACINCOpORCIENTO;
		}
		else
		{
			SCT0->SCTMATCHREL[3] = FREQ_PRINCIPAL/(PWM_FREQ*1 - 1);				// set to 100% duty cycle
		}
	}

}

void PWM3_set(uint32_t value)
{

	if (value == 0)
		SCT0->SCTMATCHREL[5] = 0;								// check val between 0% and 100%
	else
	{
		if ( value >= CINCOpORCIENTO && value <= DIEZpORCIENTO)
		{
			SCT0->SCTMATCHREL[5] = (value*DOScOMAcINCOmILIS)/DOCEcOMACINCOpORCIENTO;
		}
		else
		{
			SCT0->SCTMATCHREL[5] = FREQ_PRINCIPAL/(PWM_FREQ*1 - 1);				// set to 100% duty cycle
		}
	}

}


void SCT_IRQHandler(void)
{
	static uint8_t i = 0, semiciclo = 0;
	uint32_t flagEvent;
	flagEvent = SCT0->EVFLAG;


	if( flagEvent & 1 )
		SCT0->EVFLAG |= ( 1 << 0);							// Reset interrupt event0 flag

	if( i == 100 )
	{
		semiciclo = 1;
	}

	if( semiciclo )
	{
		PWM1_set(vectorDutys[i-100]);		//i de 100 a 200
		PWM2_set(0);
	}
	else
	{
		PWM2_set(vectorDutys[i]);
		PWM1_set(0);
	}

	i++;
	if( i == CANTdUTYS )
	{
		i = 0;
		semiciclo = 0;
	}
}



void ReloadSctimer( void )
{
	SCT0->CTRL |= (1<<2);						// Set bit 2 halt to halt timer
	Inicializar_SCTimer( );

}
