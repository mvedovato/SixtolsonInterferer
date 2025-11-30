/*
 * Inicializacion.c
 *
 *  Created on: 16 ago. 2021
 *      Author: mariano
 */
#include <Inversor.h>

void Inicializar( void )
{

	Inicializar_PLL( );
	Inicializar_SysTick( FREQ_PRINCIPAL / FREQ_SYSTICK );
    Inicializar_GPIO( );
    //Inicializar_CTimer0();
    //Inicializar_Teclado( );
    //Inicializar_IO();
    Inicializar_UART1(9600);
    //Inicializar_LCD(  );
    SCT_Init( );
    //SCTimer_Init();
    //Inicializar_SCTimer( );


}
