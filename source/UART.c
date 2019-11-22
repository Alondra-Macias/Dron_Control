/*
 * UART.c
 *
 *  Created on: 22/10/2018
 *      Author: AlondraItzel
 */
#include "UART.h"
#define  UART_module_clock 21000000
uint16 BRFD=0;
UART_MailBoxType UART0_MailBox;
uint8 brfa=0x00;

void UART0_Status_IRQHandler(void){
	if(UART0->S1&UART_S1_RDRF_MASK){
	UART0_MailBox.mailBox=UART0->D;
	UART0_MailBox.flag=1;}
}

void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
uint16 uartBaudRate;
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	UART0->C2 &= ~(UART_C2_RE_MASK);
	UART0->C2 &= ~(UART_C2_TE_MASK);
	//brfa =
	BRFD = brfa/32;
	uartBaudRate = systemClk / (16 * (baudRate + BRFD));
	UART0->BDH=UART_BDH_SBR_MASK&uartBaudRate;
	UART0->BDL=UART_BDL_SBR_MASK&uartBaudRate;
	UART0->C4=UART_C4_BRFA_MASK&brfa;

}


void UART0_interruptEnable(UART_ChannelType uartChannel){
	switch(uartChannel)
						{
							case (UART_0):
								UART0->C2|=UART_C2_RIE_MASK;
								break;

							case (UART_1):
								UART1->C2|=UART_C2_RIE_MASK;
								break;

							case (UART_2):
								UART2->C2|=UART_C2_RIE_MASK;
								break;
							case (UART_3):
							   UART3->C2|=UART_C2_RIE_MASK;
								break;
							case (UART_4):
								UART4->C2|=UART_C2_RIE_MASK;
								break;
							case (UART_5):
								UART5->C2|=UART_C2_RIE_MASK;
								break;

							default:
								break;
						}
	}




void UART_putChar (UART_ChannelType uartChannel, uint8 character)
{           switch(uartChannel){
						case (UART_0):
		if(!UART0->S1&&UART_S1_TDRE_MASK){
			UART0->D=character;

		}
							break;

						case (UART_1):
		if(!UART1->S1&&UART_S1_TDRE_MASK){
			UART1->D=character;

		}
							break;

						case (UART_2):
		if(!UART2->S1&&UART_S1_TDRE_MASK){
			UART2->D=character;

		}
							break;
						case (UART_3):
		if(!UART3->S1&&UART_S1_TDRE_MASK){
			UART3->D=character;

		}
							break;
						case (UART_4):
		if(!UART4->S1&&UART_S1_TDRE_MASK){
			UART4->D=character;

		}
							break;
						case (UART_5):
		if(!UART5->S1&&UART_S1_TDRE_MASK){
			UART5->D=character;

		}
							break;

						default:
							break;
					}
}
void UART_putString(UART_ChannelType uartChannel, sint8* string)
{	uint8 character;
	for(int i=0;i>0;i++){
	if(&string[i]!='\0'){
	character=&string[i];
	UART_putChar(uartChannel,character);
						}
	else{break;}
					}
}
