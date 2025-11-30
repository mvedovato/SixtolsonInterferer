/*
 * sctimer.c
 *
 *  Created on: 1 sep. 2021
 *      Author: mariano
 */

#include "sctimer.h"
#include "gpio.h"

const uint8_t vectorDutys[]={0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
//const uint8_t vectorDutys[]={75, 25};

void Inicializar_SCTimer( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7) | (1 << 8);			// 8= SCTIMER 7=SWM
	SYSCON->PRESETCTRL0 |= (1 << 8);						// 8= SCTIMER clear the timer reset

	SYSCON->SCTCLKSEL = 1;										// 1:Main clock 24MHz
	SYSCON->SCTCLKDIV = 1;										// divided by n

#ifdef RGBpWM
	SWM0->PINASSIGN.PINASSIGN7 &= (~(0xff << (24)));			// SCT_OUT0 = PWM PIO1.0
	SWM0->PINASSIGN.PINASSIGN7 |= (32 << (24));				//-> pin Green Led

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (0)));				// SCT_OUT1 = PWM PIO1-2
	SWM0->PINASSIGN.PINASSIGN8 |= (33 << (0));				// PIO1.2  OUT1 -> pin Blue Led

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (8)));				// SCT_OUT2 = PWM PIO0.13
	SWM0->PINASSIGN.PINASSIGN8 |= (13 << (8));					// PIO0.13 OUT2 -> pin 26
#else
	SWM0->PINASSIGN.PINASSIGN7 &= (~(0xff << (24)));			// SCT_OUT0 = PWM PIO0.8 -> pin 21
	SWM0->PINASSIGN.PINASSIGN7 |= (8 << (24));

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (0)));				// SCT_OUT1 = PWM PIO0.9
	SWM0->PINASSIGN.PINASSIGN8 |= (9 << (0));					// PIO0.9 OUT1 -> pin 22

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (8)));				// SCT_OUT2 = PWM PIO0.13
	SWM0->PINASSIGN.PINASSIGN8 |= (13 << (8));					// PIO0.13 OUT2 -> pin 26

#endif


	SCT0->CONFIG |= (1 << 0) ;		// Unify 32 bits (sin el or también funciona )
	SCT0->CTRL |= 	(1 << 18) | 	//Halt_H h counter doesn't run. Sin el or no funciona
					(1 << 4) |  	//BIDIR_L up-down, up to limit, down to limit or 0
					(1 << 1 )|
					(SCT_PRESCALER-1) << 5;    	//STOP_L counter doesn't run

	SCT0->SCTMATCH[0] = PWM_PERIOD - 1;
	SCT0->SCTMATCHREL[0] = PWM_PERIOD - 1;

	SCT0->EVENT[0].STATE = 	(1 << 0);		// event 0 happens in state 0
	SCT0->EVENT[0].CTRL |= 	(1 << 12);		//Sin el or funciona también. Comb mode only Match

	//SCT0->SCTMATCH[1] = FREQ_PRINCIPAL/(PWM_FREQ*4);					//Duty pwm1
	//SCT0->SCTMATCHREL[1] = FREQ_PRINCIPAL/(PWM_FREQ*4);					//Duty pwm1
	SCT0->SCTMATCH[1] = 0;					//Duty pwm1
	SCT0->SCTMATCHREL[1] = 0;					//Duty pwm1

	SCT0->EVENT[1].STATE = 	(1 << 0);	// event 1 happens in state 0
	SCT0->EVENT[1].CTRL |= 	(1 << 12) | ( 1 << 1) ;		//Referido a Match0 Combmode 1== Match only. Sin el or funciona también


	#ifdef	DUTYaCTIVOaLTO
		SCT0->OUT[0].SET = 1;
		//SCT0->OUT[0].CLR = (1<<1);
	#else
		//SCT0->OUT[0].SET = 1;
		SCT0->OUT[0].CLR = (1<<1);
	#endif


//---------------OUT 1---------------------------
	SCT0->SCTMATCH[2] = 0;
	SCT0->SCTMATCHREL[2] = 0;

	SCT0->EVENT[2].STATE = 	(1 << 0);		// event 2 happens in state 0
	SCT0->EVENT[2].CTRL = 	(1 << 12) | ( 1 << 0) ;		//Referido a Match0 Combmode 1== Match only. Sin el or funciona también

	SCT0->EVENT[3].STATE = 	(1 << 0);	// event 3 happens in state 0
	SCT0->EVENT[3].CTRL = 	(1 << 12) | ( 1 << 0) ;		//Referido a Match0 Combmode 1== Match only. Sin el or funciona también



	#ifdef	DUTYaCTIVOaLTO
		//SCT0->OUT[1].SET = (1<<2);				//Actua en base a evento2
		SCT0->OUT[1].CLR = (1<<3);				//Actua en base a evento3
	#else
		//SCT0->OUT[1].SET = (1<<3);				//Actua en base a evento3
		SCT0->OUT[1].CLR = (1<<2);				//Actua en base a evento2
	#endif


	//SCT0->SCTMATCH[3] = FREQ_PRINCIPAL/(PWM_FREQ*4);
	//SCT0->SCTMATCHREL[3] = FREQ_PRINCIPAL/(PWM_FREQ*4);
	SCT0->SCTMATCH[3] = 0;
	SCT0->SCTMATCHREL[3] = 0;
//--------------------------------------------------------------

	SCT0->LIMIT = 1;
	SCT0->OUTPUT = 0;

	SCT0->OUTPUTDIRCTRL = ( 1 << 1);
	SCT0->EVEN = (1 << 0);


	NVIC->ISER[0] = (1 << 9);

	SCT0->CTRL &= ~(1 << 2);					//Start SCTimer


}

void SCTimer_Init( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7) | (1 << 8);			// 8= SCTIMER 7=SWM
	SYSCON->PRESETCTRL0 |= (1 << 8);			// 8= SCTIMER clear the timer reset

	SYSCON->SCTCLKSEL = 1;										// 1:Main clock 48MHz
	SYSCON->SCTCLKDIV = 1;										// divided by n

#ifdef RGBpWM
	SWM0->PINASSIGN.PINASSIGN7 &= (~(0xff << (24)));			// SCT_OUT0 = Led
	SWM0->PINASSIGN.PINASSIGN7 |= (21 << (24));					// PIO1.1 -> pin

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (0)));				// SCT_OUT1 = Led
	SWM0->PINASSIGN.PINASSIGN8 |= (22 << (0));					// PIO1.2 -> pin

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (8)));				// SCT_OUT2 = PWM PIO0.13
	SWM0->PINASSIGN.PINASSIGN8 |= (13 << (8));					// PIO0.13 OUT2 -> pin 26
#else
	SWM0->PINASSIGN.PINASSIGN7 &= (~(0xff << (24)));			// SCT_OUT0 = PWM PIO0.8 -> pin 21
	SWM0->PINASSIGN.PINASSIGN7 |= (8 << (24));

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (0)));				// SCT_OUT1 = PWM PIO0.9
	SWM0->PINASSIGN.PINASSIGN8 |= (9 << (0));					// PIO0.9 OUT1 -> pin 22

	SWM0->PINASSIGN.PINASSIGN8 &= (~(0xff << (8)));				// SCT_OUT2 = PWM PIO0.13
	SWM0->PINASSIGN.PINASSIGN8 |= (13 << (8));					// PIO0.13 OUT2 -> pin 26
#endif

	SCT0->CONFIG |= (1 << 0) | (1 << 17);
	SCT0->CTRL |= 	(SCT_PRESCALER-1) << 5;    	//

	SCT0->SCTMATCH[0] = PWM_PERIOD - 1;
	SCT0->SCTMATCHREL[0] = PWM_PERIOD - 1;		//delay
	SCT0->SCTMATCH[1] = 0;		//match_green_off
	SCT0->SCTMATCHREL[1] = 0;		//match_green_off
	SCT0->SCTMATCH[2] = 0;
	SCT0->SCTMATCHREL[2] = 0;
	SCT0->SCTMATCH[3] = 0;		//match_blue_off
	SCT0->SCTMATCHREL[3] = 0;		//match_blue_off
	SCT0->SCTMATCH[4] = 0;
	SCT0->SCTMATCHREL[4] = 0;

	SCT0->EVENT[0].STATE = 	(1<<0);			// event 0 happens in state 0 (U_ENTRY)
	SCT0->EVENT[0].CTRL = 	(0<<0) 		|	//related to match_cycle
							(1<<12) 	|
							(1<<14) 	|
							(1<<15) ;


	SCT0->EVENT[1].STATE = 	(1<<0);
	SCT0->EVENT[1].CTRL = 	(3<<0) | (1 << 12);

	SCT0->EVENT[2].STATE = 	(1<<0);
	SCT0->EVENT[2].CTRL = 	(4<<0) | (1 << 12);

	SCT0->EVENT[3].STATE = 	(1<<1);			// event 0 happens in state 0 (U_ENTRY)
	SCT0->EVENT[3].CTRL = 	(0<<0) 		|	//related to match_cycle
							(1<<12) 	|
							(1<<14) 	|
							(0<<15) ;

	SCT0->EVENT[4].STATE = 	(1<<1);
	SCT0->EVENT[4].CTRL = 	(2<<0) | (1 << 12);

	SCT0->EVENT[5].STATE = 	(1<<1);
	SCT0->EVENT[5].CTRL = 	(1<<0) | (1 << 12);


	SCT0->OUT[0].CLR = (1 << 3) | (1 << 5);
	SCT0->OUT[0].SET = (1<<4);
	SCT0->OUT[1].CLR = (1 << 1) | (1 << 3);
	SCT0->OUT[1].SET = (1<<2);

	SCT0->OUTPUT = 0;
	SCT0->EVEN = 1;

	NVIC->ISER[0] = (1 << 9);

	SCT0->CTRL &= ~(1 << 2);

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

	SCT0->CONFIG |=  ( 1 << 0 ) | (1 << 17);// Unify, auto limit at match 0
	SCT0->CTRL	 |=  (SCT_PRESCALER-1) << 5;	//Bidir prescaler = 1

	SCT0->EVEN = 1;

	SCT0->SCTMATCH[0] = PWM_PERIOD - 1;
	SCT0->SCTMATCHREL[0] = PWM_PERIOD - 1;

	SCT0->SCTMATCH[1] = 0;								//100%
	SCT0->SCTMATCHREL[1] = 0;


	SCT0->EVENT[0].STATE = 0xFFFFFFFF; // event 0 happens in all states
	SCT0->EVENT[0].CTRL= (0 << 0) | (1 << 12); // match 0 only condition

	SCT0->EVENT[1].STATE = 0xFFFFFFFF; // event 0 happens in all states
	SCT0->EVENT[1].CTRL= (1 << 0) | (1 << 12); // match 1 only condition


	SCT0->OUT[0].SET = (1 << 0); // event 0 set OUT0 (PWM1)
	SCT0->OUT[0].CLR = (1 << 1); // event 1 clear OUT0 (PWM1)

	NVIC->ISER[0] = (1 << 9); 					// enable interrupt ISE_SCT_IRQ EVFLAG SCT event

	SCT0->CTRL &= ~(1 << 2);									// start timer
}

void PWM1_set(uint32_t value)
{

	SCT0->CTRL |= (1 << 2);									// Stop timer
	if (value == 0)
	{
		SCT0->SCTMATCHREL[1] = 0;								// check val between 0% and 100%
		SCT0->SCTMATCH[1] = 0;								//

	}
	else
	{
		if ( value > 0 && value < 100)
		{
			SCT0->SCTMATCHREL[1] = (value * FULLpWM )/100;
		}
		else
		{
			#ifdef DUTYaCTIVOaLTO
	            SCT0->OUTPUT |= (1UL << 0);
	        #else
	            SCT0->OUTPUT &= ~(1UL << 0);
	        #endif
			SCT0->SCTMATCH[1] = FULLpWM;
			SCT0->SCTMATCHREL[1] = FULLpWM;				// set to 100% duty cycle
		}

	}
	SCT0->CTRL &= ~(1 << 2);									// start timer
}

void PWM2_set(uint32_t value)
{
	SCT0->CTRL |= (1 << 2);									// Stop timer

	if (value == 0)
	{
		SCT0->SCTMATCH[3] = 0;								// check val between 0% and 100%
		SCT0->SCTMATCHREL[3] = 0;								// check val between 0% and 100%
	}
	else
	{
		if ( value > 0 && value < 100)
		{
			SCT0->SCTMATCHREL[3] = (value * FULLpWM )/100;
		}
		else
		{
			#ifdef DUTYaCTIVOaLTO
				SCT0->OUTPUT |= (1UL << 1);
			#else
				SCT0->OUTPUT &= ~(1UL << 1);
			#endif
			SCT0->SCTMATCH[3] = FULLpWM + 2;			// set to 100% duty cycle
			SCT0->SCTMATCHREL[3] = FULLpWM + 2;			// set to 100% duty cycle
		}
	}
	SCT0->CTRL &= ~(1 << 2);									// start timer
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
	uint32_t flagEvent;
	flagEvent = SCT0->EVFLAG;


	if( flagEvent & 1 )
		SCT0->EVFLAG |= ( 1 << 0);			// Reset interrupt event0 flag





}



void ReloadSctimer( void )
{
	SCT0->CTRL |= (1<<2);						// Set bit 2 halt to halt timer
	Inicializar_SCTimer( );

}

uint8_t RandomIndex( void ){
	return 0;
}
