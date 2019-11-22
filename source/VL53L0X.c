/*
 * VL53L0X.c
 *
 *  Created on: 02/11/2019
 *      Author: AlondraItzel
 */
#include "VL53L0X.h"
static BooleanType g_eeprom_error = TRUE;
uint16 message;

uint16 VL53L0X_read(void)
{
	uint8_t i = 0;
	/*Starts transmission*/
	I2C_start();
	/*Selects peripheral to write*/
	I2C_write_byte(SLAVE_ADDRESS_W);
	I2C_wait();
	/*Verify transmission status*/
	g_eeprom_error &= I2C_get_ack();

	/*Sets high address byte*/
	I2C_write_byte(TEST_ADDRESS);
	I2C_wait();
	/*Verify transmission status*/
	g_eeprom_error &= I2C_get_ack();

	I2C_repeted_start();
	/*Setup to read peripheral*/
	I2C_write_byte(SLAVE_ADDRESS_R); //para leer el dato siguiente
	I2C_wait();
	delay(1);
	/*Verifies transmission status*/
	g_eeprom_error &= I2C_get_ack();
	/*Change the set to receiver mode*/
	I2C_tx_rx_mode(0);
	/*Configures to send ACK*/
	I2C_ack();
	/*Dummy read to clean the buffer*/
	message =  I2C_read_byte();
	I2C_wait();
	delay(1000);
	/*Stops transmission*/
	I2C_stop();
	return message;
}


