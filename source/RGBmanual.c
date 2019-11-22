/*
 * RGBmanual.c
 *
 *  Created on: 12/10/2018
 *      Author: AlondraItzel
 */


#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "NVIC.h"
#include "FlexTimer.h"
#include "Switches.h"


void delay(uint16 delay)
{
	volatile int counter, counter2;

	for(counter2=16; counter2 > 0; counter2--)
	{
		for(counter=delay; counter > 0; counter--);

	}
}



