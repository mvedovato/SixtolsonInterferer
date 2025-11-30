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

volatile uint32_t tickes = 10;	//!< Var for systick
extern const uint8_t vectorDutys[];
int main(void)
{

	uint8_t i = 0, span = 100, tecla, flagTecla = 0, modoRandom = 0;
	Inicializar();
	Display_LCD( (uint8_t *)"Interfer of" , 0 , 0 ) ;
	Display_LCD( (uint8_t *)"Sixtolson" , 1 , 0 ) ;



    while(1)
    {
    	tecla = GetKey();

    	if( tecla == 0 ){ 	//Tecla user
    		flagTecla++;
    		flagTecla %= 2;

    		if( flagTecla )
    			span = 10;
    		else
    			span = 100;
    	}

    	if( tecla == 1 ){	//Tecla ISP
    		modoRandom++;
    		modoRandom%=2;
    	}

    	if( !tickes ){
    		tickes = span;

    		if( !modoRandom ){
    			PWM1_set(vectorDutys[i]);
    		}
    		else{
    			PWM1_set(vectorDutys[RandomIndex()]);
    		}


			i++;
			if( i == CANTdUTYS )
			{
				i = 0;
			}
    	}
    }
    return 0 ;
}
