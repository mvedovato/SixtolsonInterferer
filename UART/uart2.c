/*

 * UART_Driver.c
 *
 *  Created on: May 17, 2019
 *      Author: GJF-Trabajo
 */

#include "uart2.h"

#include <LPC845.h>
#include "tipos.h"
#include "gpio.h"
#include <stdio.h>

UART2_Struct	UART2;



/*****************************************************************************
** Function name:		UART1_IRQHandler
**
** Descriptions:		UART interrupt handler
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void UART2_IRQHandler (void)
{
	int32_t Temporal;

	uint32_t	Int = USART2->STAT;

	if(Int & (1 << 0))
	{
		//RX
		Temporal = (int32_t)USART2->RXDAT;

		UART2_PushRx((uint16_t)Temporal);

	}

	if(Int & (1 << 2))
	{
		//TX
		Temporal = UART2_PopTx();
		if(Temporal >= 0)
			USART2->TXDAT = (uint16_t)Temporal;
		else
		{
			USART2->INTENCLR = (1 << 2); //disable int TX
			UART2.TX.Datos_Validos = 0;
		}

	}


}


void Inicializar_UART2(uint32_t baudrate)
{
	/*
	IOCON_config_t	Temporal;

	Temporal.open_drain = 0;
	Temporal.mode = PULL_UP;
	Temporal.clk_sel = IOCON_CLK_DIV_0;
	Temporal.iic_mode = 0;
	Temporal.dac_mode = 0;
	Temporal.sample_mode = 0;


	IOCON_config_io(IOCON_INDEX_PIO0_0, &Temporal);
	GPIO_Dir( PIN_ENABLE485, 1 );
	GPIO_Set( PIN_ENABLE485, 0 );							//ENABLE 485
	 */
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 16);							// 16 = UART2

	//SWM0->PINASSIGN.PINASSIGN1 = (0x24 << 16) | (23 << 24);			// TX1 = P1.4	RX1 = P0.23
	SWM0->PINASSIGN.PINASSIGN2 = (0x12 << 16) | (0x13 << 24);			// TX2 = P0.18	RX2 = P0.19 TX2 pin3 - RX2 pin4
	USART2->CFG = 	(0)				// 0=DISABLE 1=ENABLE
					| (2 << 2)		// 0=7BITS 1=8BITS 2=9BITS
					| (0 << 4)		// 0=NOPARITY 2=PAR 3=IMPAR
					| (0 << 6)		// 0=1BITSTOP 1=2BITSTOP
					| (0 << 9)		// 0=NOFLOWCONTROL 1=FLOWCONTROL
					| (0 << 11)		// 0=ASINCRONICA 1=SINCRONICA
					| (0 << 14);	// 0=SLAVE 1=MASTER


	USART2->CTL = 0;

	USART2->INTENSET = (1 << 0);	//RX Y TX INTERRUPT

	UART2CLKSEL = 1;

	USART2->BRG = (FREQ_PRINCIPAL / baudrate) / 16;

	NVIC->ISER[0] = (1 << 5); /* enable interrupt USART2 */

	USART2->CFG |= 	(1);			// ENABLE USART2

	return;
}

void UART2_Send(uint16_t *Datos, uint32_t Tamanio)
{
	uint32_t i;

	/*if(0 == Tamanio)
		Tamanio = CADENAS_Strlen(Datos);
	*/
	for(i = 0 ; i < Tamanio ; i++)
		UART2_PushTx(Datos[i]);

	return;
}


void UART2_PushTx(uint16_t dato)
{
	UART2.TX.Buffer[UART2.TX.Indice_in] = dato;

	UART2.TX.Indice_in ++;
	UART2.TX.Indice_in %= UART2_TAMANIO_COLA_TX;

	if ( UART2.TX.Datos_Validos == 0 )
	{
		UART2.TX.Datos_Validos = 1;

		USART2->TXDAT = (uint16_t)UART2_PopTx();

		USART2->INTENSET = (1 << 2); // int tx
	}
}

int32_t UART2_PopTx( void )
{
	int32_t dato = -1;

	if ( UART2.TX.Indice_in != UART2.TX.Indice_out )
	{
		dato = (int32_t) UART2.TX.Buffer[UART2.TX.Indice_out];
		UART2.TX.Indice_out ++;
		UART2.TX.Indice_out %= UART2_TAMANIO_COLA_TX;
	}
	return dato;
}

void UART2_PushRx(uint16_t dato)
{
	UART2.RX.Buffer[UART2.RX.Indice_in] = dato;

	UART2.RX.Indice_in ++;
	UART2.RX.Indice_in %= UART2_TAMANIO_COLA_RX;
}

int32_t UART2_PopRx( void )
{
	int32_t dato = -1;

	if ( UART2.RX.Indice_in != UART2.RX.Indice_out )
	{
		dato = (int32_t) UART2.RX.Buffer[UART2.RX.Indice_out];
		UART2.RX.Indice_out ++;
		UART2.RX.Indice_out %= UART2_TAMANIO_COLA_RX;
	}
	return dato;
}

int16_t UART2_LeerBufferRX( void )
{
	int16_t caracter;

	caracter = UART2_PopRx();

		if ( caracter < 0 )
			return -1;

	return caracter;
}

void UART2_RestartIndexesTx( void )
{
	UART2.TX.Indice_in = 0;
	UART2.TX.Indice_out = 0;
}
void UART2_RestartIndexesRx(void )
{
	UART2.RX.Indice_in = 0;
	UART2.RX.Indice_out = 0;
}



