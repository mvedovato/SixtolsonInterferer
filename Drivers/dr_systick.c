/*
 * TIMER_DRIVER.c
 *
 *  Created on: Jul 25, 2019
 *      Author: GJF-Trabajo
 */

#include "dr_systick.h"
#include "core_cm0plus.h"
#include "io.h"
#include "teclado.h"
#include "timers.h"
#include "sctimer.h"
#include "gpio.h"
#define	ON			1
#define	OFF			0

#define MAX_TICKS 	0xffffff

volatile uint16_t segundos = SEGUNDOS;
extern  uint32_t tickes;	//!< Var for systick
extern uint8_t flag1Segundo;


void SysTick_Handler(void)
{


	TECLADO_Barrido( );
	Debounce( );
	segundos--;
	if( tickes )
		tickes --;	//!< Var for systick
	if(!segundos)
	{
		segundos = SEGUNDOS;
		flag1Segundo = 1;

	}


}

uint32_t Inicializar_SysTick( uint32_t ticks )
{
	if (ticks > MAX_TICKS)
		return 1 ;          			//* Reload value impossible

	SysTick->LOAD = ticks - 1;   		//* set reload register


	//SysTick->LOAD = (SysTick->CALIB)/10 -1;   		//* set reload register

	SysTick->VAL = 0;                   //* Load the SysTick Counter Value

	SysTick->CTRL = 7;					//* Enable SysTick IRQ and SysTick Timer

	return 0;
}

