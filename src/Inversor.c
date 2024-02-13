/*
===============================================================================
 Name        : ServoSG90.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <Inversor.h>

volatile int32_t tickes = 100;	//!< Var for systick

int main(void)
{


	Inicializar();
	Display_LCD( (uint8_t *)"Inversor" , 0 , 0 ) ;
	Display_LCD( (uint8_t *)"Bombinho" , 1 , 0 ) ;


    while(1)
    {

    }
    return 0 ;
}
