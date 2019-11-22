/*
 * PWM_motors.h
 *
 *  Created on: 01/11/2019
 *      Author: AlondraItzel
 */

#ifndef PWM_MOTORS_H_
#define PWM_MOTORS_H_
#include "PIT.h"
#include "FlexTimer.h"

#define STEPSIZE 5.0F
#define INIT_COUNT 0x00



void Motors_init(void);
void time_step_on(void);
void Motors_test(uint16_t COUNT);


#endif /* PWM_MOTORS_H_ */

