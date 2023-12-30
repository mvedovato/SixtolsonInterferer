/*
 * ctimer.c
 *
 *  Created on: 7 may. 2021
 *      Author: mariano
 */
#include "ctimer.h"
#include "sctimer.h"

extern volatile uint32_t bufferPWM;
uint8_t volatile finPeriodo;
//const uint32_t duty[10] = {37400, 108510, 169000, 212970, 236070, 236070, 212970, 169000, 108510, 37400};
//const uint32_t duty[10] = {1157, 4521, 7042, 8873, 9836, 9836, 8873, 7042, 4521, 1157};


void CTIMER0_IRQHandler(void)
{
	CTIMER0->IR |= (1 << 0);					// Reset flag MROint
	AnalizarTimers( );

}

void Inicializar_CTimer0( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 25);		// 25= CTIMER0
	SYSCON->PRESETCTRL0 |= (1 << 25);			// 25= CTIMER0 clear the timer reset
	//CTIMER0->PR = 4;						    // Prescaler system clock --> 6MHz
	CTIMER0->MR[0] = MATCH0;					// MR0
	CTIMER0->MCR |= (1 << 0);					//Interrupt on MATCH0
	CTIMER0->MCR |= (1 << 1);					//Reset timer on interrupt MATCH0
	CTIMER0->TCR = (1 << 1);					// Reset timer
	CTIMER0->IR = 1;
	CTIMER0->TCR = 1;
	NVIC->ISER[0] = (1 << 23); 					// enable interrupt ISE_CT32B0_IRQ

}

uint8_t GetFinPeriodo( void )
{
	return finPeriodo;
}

 void SetFinPeriodo( uint8_t valor  )
{
	finPeriodo = valor;
}
