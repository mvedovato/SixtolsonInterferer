/*
 * esp8266.c
 *
 *  Created on: 27 oct. 2019
 *      Author: juliancho
 */


#include <Inversor.h>


uint32_t Senoidal( int16_t valor)
{
	uint32_t pwm = 0;
	pwm = valor/GRADO;
	return pwm;
}
