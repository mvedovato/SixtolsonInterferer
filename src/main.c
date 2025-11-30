/*
===============================================================================
 Name        : ServoSG90.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <SixtolsonInterferer.h>
#include <stdlib.h>
#include <stdio.h>

volatile uint32_t tickes = 10;	//!< Var for systick
extern const uint8_t vectorDutys[];
uint8_t flag1Segundo;
int main(void)
{

	uint8_t i = 0, span = 100, tecla, flagTecla = 0, modo = 0, dutyFree = 50;
	uint8_t buffer[40];
	Inicializar();
	Display_LCD( (uint8_t *)"Interfer of" , 0 , 0 ) ;
	Display_LCD( (uint8_t *)"Sixtolson" , 1 , 0 ) ;


	PWM1_set(dutyFree);

    while(1)
    {
    	tecla = GetKey();

    	if( tecla == 1 ){	//Tecla ISP
    		modo++;
    		modo%=CANTmODOS;
    	}



    	switch( modo ){
    	case FREE:

        	if( tecla == 0 ){ 	//Tecla user
        		dutyFree++;
        		dutyFree %= 101;
        		PWM1_set(dutyFree);
        	}
    		break;

    	case SWEEP:
        	if( tecla == 0 ){ 	//Tecla user
        		flagTecla++;
        		flagTecla %= 2;

        		if( flagTecla )
        			span = 10;
        		else
        			span = 100;
        	}

        	if( !tickes ){
        		tickes = span;
       			PWM1_set(vectorDutys[i]);
    			i++;
    			if( i == CANTdUTYS )
    			{
    				i = 0;
    			}
        	}
    		break;

    	case RANDOM:
        	if( tecla == 0 ){ 	//Tecla user
        		flagTecla++;
        		flagTecla %= 2;

        		if( flagTecla )
        			span = 10;
        		else
        			span = 100;
        	}

        	if( !tickes ){
        		tickes = span;
        		PWM1_set(vectorDutys[RandomIndex()]);
        	}
    		break;

    	default:
    		modo = FREE;
    		break;
    	}

    	if( flag1Segundo ){
    		flag1Segundo = 0;
    		sprintf((char *)buffer,"duty: %d span: %d vecDutys: %d \n", dutyFree, span, vectorDutys[i]);
    		UART1_Send(buffer, strlen((char *)buffer));
    	}

    }
    return 0 ;
}
