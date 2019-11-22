/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    main.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "stdint.h"
#include "FlexTimer.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Switches.h"
#include "PWM_motors.h"

#include "I2C.h"
#include "Delay.h"
#include "VL53L0X.h"


#define MAX_COUNT 0xFF
#define MAX_Toggle 0x04
/*Constant used to define System Clock rate*/
#define SYSYEM_CLOCK 21000000


BooleanType sw2,sw3;

//uint16 COUNT=0x05FF; //53hz
uint16 COUNT=0x0669;

uint16 COUNT2=0x004F; //temp


uint16 men;
int main()
{
	/*Initializes and configures I2C0*/
	I2C_init(I2C_0, SYSYEM_CLOCK);
	SW_setup();
	Motors_init();

		NVIC_enableInterruptAndPriotity(FTM0_IRQ,PRIORITY_5);
		EnableInterrupts;

float num=.05;
while(1){

		sw2=GPIO_get_sw2_intr();
		sw3=GPIO_get_sw3_intr();

			if(sw2 == 1)
			{
				GPIO_clear_sw2_intr();
				//Motors_test(0x04FF);
				FTM_counter(FTM_0, COUNT);
				FTM_duty_cycle_value(FTM_0,Canal_0,COUNT*.05);
				delay(5);

			}
			if(sw3 ==  1) //+15%
			{
				GPIO_clear_sw3_intr();
				num=num+.01;
				if(num>=.1){num=.1;}
				FTM_duty_cycle_value(FTM_0,Canal_0,COUNT*num);
			}
			/*if(sw3 ==  1) //+15%
						{
			men=VL53L0X_read();
			int i=0;
			i++;
						}
		/*if(sw2 == 1)
		{
			GPIO_clear_sw2_intr();
			//Motors_test(0x04FF);
			FTM_counter(FTM_0, COUNT2);
			FTM_duty_cycle_value(FTM_0,Canal_0,COUNT2*.11);
			delay(5);

		}
		if(sw3 ==  1) //+15%
		{
			GPIO_clear_sw3_intr();
			FTM_counter(FTM_0, COUNT2);
			FTM_duty_cycle_value(FTM_0,Canal_0,COUNT2*.9);
		}*/


		}

}
