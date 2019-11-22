/*
 * PWM_motors.c
 *
 *  Created on: 01/11/2019
 *      Author: AlondraItzel
 */
#include "PWM_motors.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"

void Motors_init(void){
	gpio_pin_control_register_t pinControlRegisterPORTB = GPIO_MUX1;
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_D);


	PORTC->PCR[1]   = PORT_PCR_MUX(0x4); //M0
	PORTC->PCR[2]   = PORT_PCR_MUX(0x4); //M1

	PORTC->PCR[3]   = PORT_PCR_MUX(0x4); //M2
	PORTC->PCR[4]   = PORT_PCR_MUX(0x4); //M3

	PORTD->PCR[4]   = PORT_PCR_MUX(0x4);

	const FTM_config_t g_ftm0_ch0_config_M0 =
	{
			FTM_0,
			WP_DIS,
			Canal_0,
			INIT_COUNT,
			INIT_COUNT/2,
			FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
			FLEX_TIMER_PS_128,
			FLEX_TIMER_CLKS_1
	};
	FlexTimer_Init(&g_ftm0_ch0_config_M0);
			const FTM_config_t g_ftm0_ch1_config_M0N =
					{
							FTM_0,
							WP_DIS,
							Canal_1,
							INIT_COUNT,
							INIT_COUNT/2,
							FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
							FLEX_TIMER_PS_128,
							FLEX_TIMER_CLKS_1
					};
			FlexTimer_Init(&g_ftm0_ch1_config_M0N);
			const FTM_config_t g_ftm0_ch2_config_M1 =
							{
									FTM_0,
									WP_DIS,
									Canal_2,
									INIT_COUNT,
									INIT_COUNT/2,
									FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
									FLEX_TIMER_PS_128,
									FLEX_TIMER_CLKS_1
							};
			FlexTimer_Init(&g_ftm0_ch2_config_M1);



			const FTM_config_t g_ftm3_ch4_config_M3 =
											{
												FTM_3,
												WP_DIS,
												Canal_4,
												INIT_COUNT,
												INIT_COUNT/2,
												FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
												FLEX_TIMER_PS_128,
												FLEX_TIMER_CLKS_1
															};
					FlexTimer_Init(&g_ftm3_ch4_config_M3);

}
void time_step_on(void){
							PIT_enable_interrupt(PIT_0);
							PIT_delay(PIT_0,SYSTEM_CLOCK,STEPSIZE);
}

void Motors_test(uint16 COUNT){
	FTM_counter(FTM_0, COUNT);
	FTM_duty_cycle_value(FTM_0,Canal_0,(COUNT/2));
}
