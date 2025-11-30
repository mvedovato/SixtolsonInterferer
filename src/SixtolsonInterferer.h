/*
 * ServoSG90.h
 *
 *  Created on: 15 ago. 2021
 *      Author: mariano
 */

#ifndef SIXTOLSONINTERFERER_H_
#define SIXTOLSONINTERFERER_H_


#include <cr_section_macros.h>
#include "tipos.h"
#include "dr_pll.h"
#include "dr_systick.h"
#include "gpio.h"
#include "io.h"
#include "lcd.h"
#include "ctimer.h"
#include "uart0.h"
#include "uart1.h"
#include "teclado.h"
#include "timers.h"
#include "sctimer.h"



#define		PERIODOpWM				MATCH0		//24MHz / 20KHz = 1200
#define 	NOVENTAgRADOS			30000
#define 	CEROgRADOS				0
#define 	MENOSnOVENTAgRADOS		90000
#define		SPAN					(NOVENTAgRADOS - MENOSnOVENTAgRADOS)	//12500 (1 ms)
#define		GRADO					SPAN/180	//69,44 (5,55 us por grado)
#define 	REPETICIONgRADOS		9

#define 	FREE					0
#define 	SWEEP					1
#define 	RANDOM					2

#define 	CANTmODOS				3

void Inicializar( void );

#endif /* SIXTOLSONINTERFERER_H_ */
