/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "baremetal.h"       /* <= own header */

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
//#include "sAPI.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
uint8_t leerUART(void){
	uint8_t receivedByte = '&';
	if (Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR){
		receivedByte = Chip_UART_ReadByte(LPC_USART2);
	}
	return receivedByte;
}

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
//uint8_t i=0;
/*==================[internal functions definition]==========================*/
//void UART2_IRQHandler(void){
//	uint8_t byte;
//	byte= leerUART();
//	WORD[i]=byte;
//	if (byte==1){
//		Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
//	}
//	if (byte==2){
//		Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
//	}
//	if (byte==3){
//		Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
//	}
//	if ((byte!=1)||(byte!=2)||(byte!=3)){
//		while ((Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_THRE) == 0); /* Wait for space in FIFO */{
//				Chip_UART_SendByte(LPC_USART2, byte);
//		}
//	}
//	i++;
//	if(i==4){
//		i=0;
//	}

//}

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
   /* perform the needed initialization here */



	   /* Inicializar DigitalIO */
	Chip_GPIO_Init(LPC_GPIO_PORT);
			Chip_SCU_PinMux(
			            2,
			            10,
			            SCU_MODE_INACT | SCU_MODE_ZIF_DIS,
			            SCU_MODE_FUNC0
			         );
			Chip_GPIO_SetDir( LPC_GPIO_PORT, 0, ( 1 << 14 ), 1 );
			Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, 0);

	Chip_UART_Init(LPC_USART2);
		Chip_UART_SetBaud(LPC_USART2, 9600);  /* Set Baud rate */
		Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0); /* Modify FCR (FIFO Control Register)*/
		Chip_UART_TXEnable(LPC_USART2); /* Enable UART Transmission */
		Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1,FUNC6: UART2_TXD */
		Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2,FUNC6: UART2_RXD */

		/* Enable UART Rx Interrupt */
		   Chip_UART_IntEnable(LPC_USART2, UART_IER_RBRINT ); /* Receiver Buffer Register Interrupt */
		   /* Enable UART line status interrupt */
		  Chip_UART_IntEnable(LPC_USART2, UART_IER_RLSINT ); /* LPC43xx User manual page 1118 */
		  uint8_t WORD[4];
		  int i=0;
   while(1) {
      /* add your code here */
	   uint8_t byte;
	   byte= leerUART();

	   	if (byte==1){
	   		Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
	   	}
	   	if (byte==2){
	   		Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
	   	}
	   	if (byte==3){
	   		Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
	   	}
	   	if (((byte!=1)||(byte!=2)||(byte!=3))&&(byte!='&')){
	   		WORD[i]=byte;
	   		i++;
	   		while ((Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_THRE) == 0); /* Wait for space in FIFO */{
	   				Chip_UART_SendByte(LPC_USART2, byte);
	   		}
	   	}

	   	if(i==4){
	   		i=0;
	   	}
	   if(WORD[0]=='L'){
		   if(WORD[1]=='E'){
			   if(WORD[2]=='D'){
				   if(WORD[2]=='B'){
					   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, FALSE);
					   i=0;
				   }
			   }
		   }
	   }


   }
   return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

