/*******************************************************************************************************************************//**
 *
 * @file		DR_Timers.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		9 de jun. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DRIVERINFOTRONIC_DR_TIMERS_H_
#define DRIVERINFOTRONIC_DR_TIMERS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	N_TIMERS				10


/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

#define 	DEC			0
#define 	SEG			1
#define 	MIN			2


#define 	DECIMAS			1
#define 	SEGUNDOS		1000
#define 	MINUTOS			60

#define 	EV_PWM1			0
#define 	EV_PWM2			1
#define 	EV_PWM3			2

#define 	VEINTEmILIS			200
#define		DUTYaCTIVEhIGH

#define 	RUN			0
#define 	PAUSE		1
typedef void (*Timer_Handler)(void);


extern volatile 	uint32_t Tmr_Run[ N_TIMERS ];
extern volatile 	uint8_t  TMR_Events[ N_TIMERS ];
extern void 	 	(* TMR_handlers [N_TIMERS]) (void);
extern volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];
extern volatile 	uint8_t  Tmr_Base[ N_TIMERS ];

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void AnalizarTimers(void);
void TimerEvent(void);
void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base );
void SetTimer( uint8_t event, uint32_t time );
uint32_t GetTimer( uint8_t event );
void StandByTimer( uint8_t event , uint8_t accion);
void TimerStop(uint8_t event);
void TimerClose(void);
void EV_parpadeo (void);
void EV_DAC( void );
uint32_t GetTiempoDAC( void );
void pwm1( void );
void pwm2( void );
void pwm3( void );



#endif /* DRIVERINFOTRONIC_DR_TIMERS_H_ */
