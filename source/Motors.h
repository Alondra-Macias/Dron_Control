/*
 * Motors.h
 *
 *  Created on: 08/11/2018
 *      Author: AlondraItzel
 */

#ifndef MOTORS_H_
#define MOTORS_H_
#include "PIT.h"
#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "FlexTimer.h"
#include "Switches.h"
#include "GPIO.h"
#include "Bluetooth.h"
#include "Control_UART.h"
#include "Delay.h"

#define STEPSIZE 5.0F
#define INIT_COUNT 0x00
#define COUNT 0xFFFF

/*!
 	 \brief	 The configuration for GPIO, FTM0(all channels) and PIT0
 	 \param[in] void
 	 \return void
 */
void Motors_Init(void);
/*!
 	 \brief	 If the UART0 flag is high i would compare the data to turn on a specific motor
 	 \param[in] void
 	 \return void
 */
void Motors_move(void);
/*!
 	 \brief	 When PIT0 interruption occurs it would turn off all the motors
 	 \param[in] void
 	 \return void
 */
void Motors_stop(void);
/*!
 	 \brief	 Turn on the PIT0 to give time for the step size
 	 \param[in] void
 	 \return void
 */
void time_step_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M0
 	 \param[in] void
 	 \return void
 */
void M0_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M0N
 	 \param[in] void
 	 \return void
 */
void M0N_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M1
 	 \param[in] void
 	 \return void
 */
void M1_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M1N
 	 \param[in] void
 	 \return void
 */
void M1N_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M2
 	 \param[in] void
 	 \return void
 */
void M2_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M2N
 	 \param[in] void
 	 \return void
 */
void M2N_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M3
 	 \param[in] void
 	 \return void
 */
void M3_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M3N
 	 \param[in] void
 	 \return void
 */
void M3N_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M4
 	 \param[in] void
 	 \return void
 */
void M4_on(void);
/*!
 	 \brief	 Turn on the FTM signal for M4N
 	 \param[in] void
 	 \return void
 */
void M4N_on(void);


#endif /* MOTORS_H_ */
