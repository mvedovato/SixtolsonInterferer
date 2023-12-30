/*
 * sctimer.h
 *
 *  Created on: 1 sep. 2021
 *      Author: mariano
 */

#ifndef SCTIMER_H_
#define SCTIMER_H_

#include <LPC845.h>
#define	DUTYaCTIVOaLTO
#define DACMATCH0				48000		//1ms -> clk system 48MHz
#define	STEPSpWM				1000
#define PWM						14
#define OUT0					0
#define PWM_FREQ				50
#define PWM_PERIOD				(FREQ_PRINCIPAL / (PWM_FREQ * 2))	//
#define PWM_STEP				(PWM_PERIOD / STEPSpWM)		// PWM resolution in PWM_STEP steps
#define	FULLpWM					PWM_FREQ
#define	CANTdUTYS				10
#define DOScOMAcINCOmILIS		60000
#define UNOcOMAcINCOmILIS		36000
#define UNmILIS					24000
#define DOSmILIS				48000
#define	SIETEcOMACINCOpORCIENTO	75
#define	DOCEcOMACINCOpORCIENTO	125
#define	CINCOpORCIENTO			50
#define	DIEZpORCIENTO			100



#define pwm_val1	(400000)
#define pwm_val2	(500000)
#define pwm_val3	(100000)
#define pwm_val4	(900000)
#define pwm_cycle	(1000000)



void SCTimer_Init( void );
void PWM1_set(uint32_t );
void PWM2_set(uint32_t );
void PWM3_set(uint32_t );
void Inicializar_SCTimer( void );
void ReloadSctimer( void );
void SCT_Init(void);

#endif /* SCTIMER_H_ */
