/*

 * UART_Driver.c
 *
 *  Created on: May 17, 2019
 *      Author: GJF-Trabajo
 */

#include <LPC845.h>
#include "uart3.h"
#include "tipos.h"
#include "gpio.h"


UART3_Struct		UART3;
uint8_t tramaRecibidaUART3[16];


/*****************************************************************************
** Function name:		UART0_IRQHandler
**
** Descriptions:		UART interrupt handler
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
//void UART3_IRQHandler (void)
void PININT6_IRQHandler (void )
{
	int32_t Temporal;

	uint32_t	Int = USART3->STAT;

	if(Int & (1 << 0))
	{
		//RX
		Temporal = (int32_t)USART3->RXDAT;

		UART3_PushRx((uint8_t)Temporal);

	}

	if(Int & (1 << 2))
	{
		//TX
		Temporal = UART3_PopTx();
		if(Temporal >= 0)
			USART3->TXDAT = (uint8_t)Temporal;
		else
		{
			USART3->INTENCLR = (1 << 2); //disable int TX
			UART3.TX.Datos_Validos = 0;
		}

	}


}


void Inicializar_UART3(uint32_t baudrate)
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 30);					// 30 = UART3
	SWM0->PINASSIGN.PINASSIGN11 = (0x14 << 24);				// TX3 = P0.20
	SWM0->PINASSIGN.PINASSIGN12 = (0x15 << 0);				// RX3 = P0.21
	USART3->CFG = 	(0)				// 0=DISABLE 1=ENABLE
					| (1 << 2)		// 0=7BITS 1=8BITS 2=9BITS
					| (0 << 4)		// 0=NOPARITY 2=PAR 3=IMPAR
					| (0 << 6)		// 0=1BITSTOP 1=2BITSTOP
					| (0 << 9)		// 0=NOFLOWCONTROL 1=FLOWCONTROL
					| (0 << 11)		// 0=ASINCRONICA 1=SINCRONICA
					| (0 << 14);	// 0=SLAVE 1=MASTER


	USART3->CTL = 0;

	USART3->INTENSET = (1 << 0);	//RX Y TX INTERRUPT

	UART3CLKSEL = 1;

	USART3->BRG = (FREQ_PRINCIPAL / baudrate) / 16;

	NVIC->ISER[0] = (1 << 30); 		/* enable interrupt UART3_IRQ */

	USART3->CFG |= 	(1);			// ENABLE USART3

	return;
}

void UART3_Send(uint8_t *Datos, uint32_t Tamanio)
{
	uint32_t i;

	/*if(0 == Tamanio)
		Tamanio = CADENAS_Strlen(Datos);
	*/
	for(i = 0 ; i < Tamanio ; i++)
		UART3_PushTx(Datos[i]);

	return;
}


void UART3_PushTx(uint8_t dato)
{
	UART3.TX.Buffer[UART3.TX.Indice_in] = dato;

	UART3.TX.Indice_in ++;
	UART3.TX.Indice_in %= UART3_TAMANIO_COLA_TX;

	if ( UART3.TX.Datos_Validos == 0 )
	{
		UART3.TX.Datos_Validos = 1;

		USART3->TXDAT = (uint8_t)UART3_PopTx();

		USART3->INTENSET = (1 << 2); // int tx
	}
}

int32_t UART3_PopTx( void )
{
	int32_t dato = -1;

	if ( UART3.TX.Indice_in != UART3.TX.Indice_out )
	{
		dato = (int32_t) UART3.TX.Buffer[UART3.TX.Indice_out];
		UART3.TX.Indice_out ++;
		UART3.TX.Indice_out %= UART3_TAMANIO_COLA_TX;
	}
	return dato;
}

void UART3_PushRx(uint8_t dato)
{
	UART3.RX.Buffer[UART3.RX.Indice_in] = dato;

	UART3.RX.Indice_in ++;
	UART3.RX.Indice_in %= UART3_TAMANIO_COLA_RX;
}

int32_t UART3_PopRx( void )
{
	int32_t dato = -1;

	if ( UART3.RX.Indice_in != UART3.RX.Indice_out )
	{
		dato = (int32_t) UART3.RX.Buffer[UART3.RX.Indice_out];
		UART3.RX.Indice_out ++;
		UART3.RX.Indice_out %= UART3_TAMANIO_COLA_RX;
	}
	return dato;
}



int8_t AnalizarTramaUart3( int8_t caracter )
{
		return 0;
}


uint8_t LeerBufferRXUART3( void )
{
	uint8_t caracter;

	caracter = UART3_PopRx();

	return caracter;
}

void RestartIndexesTxUART3( void )
{
	UART3.TX.Indice_in = 0;
	UART3.TX.Indice_out = 0;
}
void RestartIndexesRxUART3(void )
{
	UART3.RX.Indice_in = 0;
	UART3.RX.Indice_out = 0;
}

