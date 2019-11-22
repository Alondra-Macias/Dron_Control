/**
	\file
	\brief
		This is the source file for the I2C device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the I2C peripheral.
	\authors  Margarita Jauregui, Alondra Macias
	\date	30/09/2018
 */


#include "I2C.h"


void I2C_clock_gating (void)
{
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
}

BooleanType I2C_busy(void)
 {
	 if (I2C0->S & I2C_S_TCF_MASK)
			 return TRUE;
		 else
			 return FALSE;
 }


 void I2C_mst_or_slv_mode(uint8_t mst_or_slv)
 {
	 if(mst_or_slv)
	 {
		 I2C0->C1|= I2C_C1_MST_MASK;
	 }
	 else
		 I2C0->C1 &= ~I2C_C1_MST_MASK;
 }


 void I2C_tx_rx_mode(uint8_t tx_or_rx)
 {
	 if(tx_or_rx)
	 {
		 I2C0->C1|= I2C_C1_TX_MASK;
	 }
	 else
		 I2C0->C1 &= ~I2C_C1_TX_MASK;
 }


 void I2C_nack(void)
 {
	 I2C0->C1|=I2C_C1_TXAK_MASK;//Not ACKnowledge
 }

 void I2C_ack(void)
 {
	 I2C0->C1 &= ~(I2C_C1_TXAK_MASK);//Not ACKnowledge
 }

 void I2C_repeted_start(void)
 {
	 I2C0->C1|= I2C_C1_RSTA_MASK;
 }


void I2C_write_byte(uint8_t data)
{
	I2C0->D = data;
}


uint8_t  I2C_read_byte(void)
{
	return I2C0->D;
}

void I2C_wait(void)
{
	  while((I2C0->S & I2C_S_IICIF_MASK) == FALSE);
	  I2C0->S |= I2C_S_IICIF_MASK;
}


uint8_t I2C_get_ack(void)
{
	return (I2C0->S & I2C_S_RXAK_MASK);
}


void I2C_start(void)
{
	I2C_mst_or_slv_mode(1);//Generates the start signal. When MST bit is changed from 0 to 1
	I2C_tx_rx_mode(1); //change to transmitter mode
}


void I2C_stop(void)
{
	I2C_mst_or_slv_mode(0);// Generates the stop signal. When this bit changes from 1 to 0
	I2C_tx_rx_mode(0);// change to receiver mode
}

void I2C_init(i2c_channel_t channel, uint32_t system_clock)
{
	I2C_clock_gating();
	GPIO_clock_gating(GPIO_B);
	I2C0->C1|=I2C_C1_IICEN_MASK;//enable module operation
	PORTB->PCR[2] = GPIO_MUX2;
	PORTB->PCR[3] = GPIO_MUX2;
	I2C0->F = I2C_MULT_2 | I2C_SCL_26; //Sets ICR and mult
	I2C_tx_rx_mode(I2C_TX_MODE);	//Configures as Tx
	I2C_mst_or_slv_mode(I2C_MASTER_MODE);	//Configures as master
}


