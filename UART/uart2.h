/*
 * UART1_Driver.h
 *
 *  Created on: Jul 26, 2019
 *      Author: GJF-Trabajo
 */

#ifndef DRIVER_UART_UART2_DRIVER_H_
#define DRIVER_UART_UART2_DRIVER_H_

#include "tipos.h"
#include <string.h>

#define		UART2_TAMANIO_COLA_RX					100
#define		UART2_TAMANIO_COLA_TX					100
#define		PIN_ENABLE485							0,0
#define 	NO_KEY									0xFFFF

typedef struct
{
	uint8_t						Datos_Validos;
	uint16_t					Tamanio;
	uint16_t					Buffer[UART2_TAMANIO_COLA_RX];
	uint16_t					Indice_in, Indice_out;
}STRUCT_RX2;

typedef struct
{
	uint8_t						Datos_Validos;
	uint16_t					Tamanio;
	uint16_t					Buffer[UART2_TAMANIO_COLA_TX];
	uint16_t					Indice_in, Indice_out;
}STRUCT_TX2;

typedef struct
{
	STRUCT_RX2					RX;
	STRUCT_TX2					TX;
}UART2_Struct;

void Inicializar_UART2(uint32_t baudrate);
void UART2_Send(uint16_t *Datos, uint32_t Tamanio);
void UART2_PushTx(uint16_t Dato);
int32_t UART2_PopTx( void );
void UART2_PushRx(uint16_t Dato);
int32_t UART2_PopRx( void );
void UART2_RestartIndexesTx( void );
void UART2_RestartIndexesRx( void );

int16_t UART2_LeerBufferRX( void );


#endif /* DRIVER_UART_UART2_DRIVER_H_ */
