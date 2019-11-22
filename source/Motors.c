/*
 * Motors.c
 *
 *  Created on: 08/11/2018
 *      Author: AlondraItzel

#include "Motors.h"
BooleanType sw2, sw3;
uint8_t pitIntrStatus = FALSE;

uint8_t g_BASE_LEFT=FALSE;
uint8_t g_BASE_RIGHT=FALSE;
uint8_t g_SHOULDER_UP=FALSE;
uint8_t g_SHOULDER_DOWN=FALSE;
uint8_t g_ELBOW_UP=FALSE;
uint8_t g_ELBOW_DOWN=FALSE;
uint8_t g_WRIST_UP=FALSE;
uint8_t g_WRIST_DOWN=FALSE;
uint8_t g_PIN_OPEN=FALSE;
uint8_t g_PIN_CLOSE=FALSE;
uint8_t g_LED_ON_OFF=FALSE;


static uint8_t data=0;


void Motors_Init(void)
{

	gpio_pin_control_register_t pinControlRegisterPORTB = GPIO_MUX1;
	GPIO_clock_gating(GPIO_B);
	GPIO_pin_control_register(GPIO_B,BIT2,&pinControlRegisterPORTB); //enable 0
	GPIO_pin_control_register(GPIO_B,BIT3,&pinControlRegisterPORTB); //enable 1
	GPIO_pin_control_register(GPIO_B,BIT10,&pinControlRegisterPORTB); //LED



	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,BIT2);
	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,BIT3);
	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,BIT10);


	GPIO_clear_pin(GPIO_B,BIT2);
	GPIO_clear_pin(GPIO_B,BIT3);
	GPIO_clear_pin(GPIO_B,BIT10);



	//GPIO_set_pin(GPIO_D,BIT0);


	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_D);

	PORTC->PCR[1]   = PORT_PCR_MUX(0x4); //enable out M0
	PORTC->PCR[2]   = PORT_PCR_MUX(0x4); //enable out M0N

	PORTC->PCR[3]   = PORT_PCR_MUX(0x4); //enable out M1
	PORTC->PCR[4]   = PORT_PCR_MUX(0x4); //enable out M1N

	PORTD->PCR[4]   = PORT_PCR_MUX(0x4); //enable out M2 && M3
	PORTD->PCR[5]   = PORT_PCR_MUX(0x4); //enable out M2N && M3N

	PORTD->PCR[6]   = PORT_PCR_MUX(0x4); //enable out M4
	PORTD->PCR[7]   = PORT_PCR_MUX(0x4); //enable out M4N


	/*Configuration structure for FTM0-CH0
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
		const FTM_config_t g_ftm0_ch3_config_M1N =
								{
										FTM_0,
										WP_DIS,
										Canal_3,
										INIT_COUNT,
										INIT_COUNT/2,
										FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
										FLEX_TIMER_PS_128,
										FLEX_TIMER_CLKS_1
								};
		FlexTimer_Init(&g_ftm0_ch3_config_M1N);
		const FTM_config_t g_ftm0_ch4_config_M2 =
										{
												FTM_0,
												WP_DIS,
												Canal_4,
												INIT_COUNT,
												INIT_COUNT/2,
												FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
												FLEX_TIMER_PS_128,
												FLEX_TIMER_CLKS_1
										};
		FlexTimer_Init(&g_ftm0_ch4_config_M2);
		const FTM_config_t g_ftm0_ch5_config_M2N =
												{
													FTM_0,
													WP_DIS,
													Canal_5,
													INIT_COUNT,
													INIT_COUNT/2,
													FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
													FLEX_TIMER_PS_128,
													FLEX_TIMER_CLKS_1
												};
				FlexTimer_Init(&g_ftm0_ch5_config_M2N);
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
						const FTM_config_t g_ftm3_ch5_config_M3N =
									{
												FTM_3,
												WP_DIS,
												Canal_5,
												INIT_COUNT,
												INIT_COUNT/2,
												FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
												FLEX_TIMER_PS_128,
												FLEX_TIMER_CLKS_1
																						};
							FlexTimer_Init(&g_ftm3_ch5_config_M3N);
							const FTM_config_t g_ftm3_ch6_config_M4 =
															{
										FTM_0,
										WP_DIS,
										Canal_6,
										INIT_COUNT,
										INIT_COUNT/2,
										FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
										FLEX_TIMER_PS_128,
										FLEX_TIMER_CLKS_1
														};
							FlexTimer_Init(&g_ftm3_ch6_config_M4);
							const FTM_config_t g_ftm3_ch7_config_M4N =
											{
									FTM_0,
									WP_DIS,
									Canal_7,
									INIT_COUNT,
								INIT_COUNT/2,
								FLEX_TIMER_MSB | FLEX_TIMER_ELSB,
								FLEX_TIMER_PS_128,
								FLEX_TIMER_CLKS_1
								};
								FlexTimer_Init(&g_ftm3_ch7_config_M4N);


}



void Motors_move(void)
{   data=0;
	data=read_UART(UART_4);

	if(g_BASE_LEFT&&g_BASE_RIGHT)
		{
		FTM0->COMBINE=0x12;
		//to make the pwm 0 complementary of 1 and adding a
		//dead time to avoid a short circuiting to channel 0 & 1
		}
	else if(g_SHOULDER_UP&&g_SHOULDER_DOWN)
			{
			FTM0->COMBINE=0x1200;
			//to make the pwm 2 complementary of 3 and adding a
			//dead time to avoid a short circuiting to channel 2 & 3
			}
	else if(g_ELBOW_UP&&g_ELBOW_DOWN)
			{
			FTM0->COMBINE=0x120000; //to make the pwm 4 complementary of 5 and adding a
			//dead time to avoid a short circuiting to channel 4 & 5
			}
	else if(g_WRIST_UP&&g_WRIST_DOWN)
				{
	FTM0->COMBINE=0x120000; //to make the pwm 0 complementary of 1 and adding a
				//dead time to avoid a short circuiting to channel 4 & 5
	}
	else if(g_PIN_OPEN&&g_PIN_CLOSE)
					{
	FTM0->COMBINE=0x12000000; //to make the pwm 0 complementary of 1 and adding a
					//dead time to avoid a short circuiting to channel 4 & 5
		}
	else
		{FTM_clean(FTM_0);}


	//if UART receive something would evaluate data to turn on the Motor corresponding of the data selected

	if (UART4_mail_flag())
			{UART4_clear_flag();
			UART4_clear_Data();

				switch (data)
				{
							case (BASE_LEFT):
						g_BASE_LEFT=TRUE;
							 M0_on();

					break;
							case (BASE_RIGHT):
						g_BASE_RIGHT=TRUE;
							 M0N_on();

					break;
							case (SHOULDER_UP):
								g_SHOULDER_UP=TRUE;
							 M1_on();

					break;
							case (SHOULDER_DOWN):
								g_SHOULDER_DOWN=TRUE;
							 M1N_on();

					break;
							case (ELBOW_UP):
								g_ELBOW_UP=TRUE;
					GPIO_clear_pin(GPIO_B,BIT3);//Turn the enable on for the indicated h bridge and clear the other
					GPIO_set_pin(GPIO_B,BIT2);
								M2_on();

					break;

							case (ELBOW_DOWN):
								g_ELBOW_DOWN=TRUE;
					GPIO_clear_pin(GPIO_B,BIT3);//Turn the enable on for the indicated h bridge
					GPIO_set_pin(GPIO_B,BIT2);
								M2N_on();



					break;
							case (WRIST_UP):
								g_WRIST_UP=TRUE;
					GPIO_clear_pin(GPIO_B,BIT2);//Turn the enable on for the indicated h bridge
					GPIO_set_pin(GPIO_B,BIT3);
								M3_on();


					break;
							case (WRIST_DOWN):
								g_WRIST_DOWN=TRUE;
					GPIO_clear_pin(GPIO_B,BIT2);//Turn the enable on for the indicated h bridge
					GPIO_set_pin(GPIO_B,BIT3);
								M3N_on();


					break;
							case (PIN_OPEN):
									g_PIN_OPEN=TRUE;
								M4_on();

					break;
							case (PIN_CLOSE):
								g_PIN_CLOSE=TRUE;
								M4N_on();
					break;
							case (LED_ON_OFF):
									if(!g_LED_ON_OFF)
									{
										g_LED_ON_OFF=TRUE;
										GPIO_set_pin(GPIO_B,BIT10);
									}
									else
									{
										g_LED_ON_OFF=FALSE;
										GPIO_clear_pin(GPIO_B,BIT10);
									}
							break;

					default:
						break;
			}

		}

}

void Motors_stop(void){
	if(PIT0_get_interrupt_glag_status()){
		PIT0_clear_interrupt_flag();
			PIT_stop(PIT_0);
			FTM_counter(FTM_0, INIT_COUNT);

			FTM_duty_cycle_value(FTM_0,Canal_0,INIT_COUNT);
			FTM_duty_cycle_value(FTM_0,Canal_1,INIT_COUNT);
			FTM_duty_cycle_value(FTM_0,Canal_2,INIT_COUNT);
			FTM_duty_cycle_value(FTM_0,Canal_3,INIT_COUNT);
			FTM_duty_cycle_value(FTM_0,Canal_4,INIT_COUNT);
			FTM_duty_cycle_value(FTM_0,Canal_5,INIT_COUNT);
			FTM_duty_cycle_value(FTM_0,Canal_6,INIT_COUNT);
			FTM_duty_cycle_value(FTM_0,Canal_7,INIT_COUNT);

			g_BASE_LEFT=FALSE;
			g_BASE_RIGHT=FALSE;
			g_SHOULDER_UP=FALSE;
			g_SHOULDER_DOWN=FALSE;
			g_ELBOW_UP=FALSE;
			g_ELBOW_DOWN=FALSE;
			g_WRIST_UP=FALSE;
			g_WRIST_DOWN=FALSE;
			g_PIN_OPEN=FALSE;
			g_PIN_CLOSE=FALSE;

			}


							}
void time_step_on(void){
							PIT_enable_interrupt(PIT_0);
							PIT_delay(PIT_0,SYSTEM_CLOCK,STEPSIZE);
}

void M0_on(void){
						time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_0,(COUNT/2));
}

void M0N_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_1,(COUNT/2));
}
void M1_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_2,(COUNT/2));
}
void M1N_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_3,(COUNT/2));
}
void M2_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_4,(COUNT/2));

}
void M2N_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_5,(COUNT/2));

}
void M3_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_4,(COUNT/2));

}
void M3N_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_5,(COUNT/2));

}
void M4_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_6,(COUNT/2));

}
void M4N_on(void){
	time_step_on();
						FTM_counter(FTM_0, COUNT);
						FTM_duty_cycle_value(FTM_0,Canal_7,(COUNT/2));
}


*/

