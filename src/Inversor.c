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

volatile uint32_t bufferPWM = MATCH0/2;

volatile int32_t tickes = 100;	//!< Var for systick
uint32_t cicloActividad = 0;
int main(void)
{


	Inicializar();
	Display_LCD( (uint8_t *)"Inversor" , 0 , 0 ) ;
	Display_LCD( (uint8_t *)"Bombinho" , 1 , 0 ) ;
	//PWM_set(cicloActividad);

    while(1)
    {

/*    	if(tickes < 0)
    	{
    		tickes = 100;
    		cicloActividad++;
    		PWM_set(cicloActividad);
    		if( (cicloActividad*PWM_STEP) >= PWM_PERIOD - 1)
    			cicloActividad = 0;
    	}*/
    }
    return 0 ;
}
