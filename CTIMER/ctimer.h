/*
 * ctimer.h
 *
 *  Created on: 7 may. 2021
 *      Author: mariano
 */

#ifndef CTIMER_H_
#define CTIMER_H_

#include "gpio.h"
#include "io.h"
#include "tipos.h"
#include "Inversor.h"


//#define MATCH0		24		//IRQ=7,5us
//#define MATCH0		852	//IRQ=35,511us -> 64 samples 2,7272ms - 440Hz
#define MATCH0			2400UL	//100us

#define 	MINpWM	0
#define		PERIODOtIMER0	1200




#define	PIN_SERVO 	PIN_O3
#define	ON			1
#define	OFF			0


void Inicializar_CTimer0( void );
uint8_t GetFinPeriodo( void );
void SetFinPeriodo( uint8_t );

#endif /* CTIMER_H_ */
