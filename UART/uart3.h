/*
 * UART1_Driver.h
 *
 *  Created on: Jul 26, 2019
 *      Author: GJF-Trabajo
 */

#ifndef UART3_H_
#define UART3_H_

#include "tipos.h"
#include <string.h>

#define		UART3_TAMANIO_COLA_RX					100
#define		UART3_TAMANIO_COLA_TX					100




typedef struct
{
	uint8_t						Datos_Validos;
	uint16_t					Tamanio;
	uint8_t						Buffer[UART3_TAMANIO_COLA_RX];
	uint16_t					Indice_in, Indice_out;
}STRUCT_RX3;

typedef struct
{
	uint8_t						Datos_Validos;
	uint16_t					Tamanio;
	uint8_t						Buffer[UART3_TAMANIO_COLA_TX];
	uint16_t					Indice_in, Indice_out;
}STRUCT_TX3;

typedef struct
{
	STRUCT_RX3					RX;
	STRUCT_TX3					TX;
}UART3_Struct;

void Inicializar_UART3(uint32_t);
void UART3_Send(uint8_t *, uint32_t );
void UART3_PushTx(uint8_t );
int32_t UART3_PopTx( void );
void UART3_PushRx(uint8_t Dato);
int32_t UART3_PopRx( void );
void RestartIndexesTxUART3( void );
void RestartIndexesRxUART3( void );

uint8_t LeerBufferRXUART3( void );
int8_t AnalizarTramaUart3(int8_t);



#endif /* DRIVER_UART_UART3_DRIVER_H_ */
