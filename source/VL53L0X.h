/*
 * VL53L0X.h
 *
 *  Created on: 02/11/2019
 *      Author: AlondraItzel
 */

#ifndef VL53L0X_H_
#define VL53L0X_H_

#include "I2C.h"
#include "DataTypeDefinitions.h"
#include "UART.h"

/*Constant used to set the high address byte*/
#define SLAVE_ADDRESS_W 0x52
#define SLAVE_ADDRESS_R 0x53

#define TEST_ADDRESS 0xC0


uint16 VL53L0X_read(void);






#endif /* VL53L0X_H_ */
