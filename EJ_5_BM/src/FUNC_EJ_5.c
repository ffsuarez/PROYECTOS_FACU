/**
*	\file funciones.c
*	\brief 
*	\details Descripcion detallada del archivo
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
#include "sAPI.h"
#include "FUNC_EJ_5.h"
uint8_t dutycicle = 0;
//Implementacion Switch-Case

/**
*	\fn void maquina_estado()
*	\brief Implementacion Switch-Case
*	\details 
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
void maquina_estado()
{
		static int estado = RECEPCION;

		switch(estado)
		{
			case RECEPCION:
			
				if(UNMENOS())
				{
					DISMINUYO5();
					estado = CINCO_U_MENOS;
		
				}
				if(UNMAS())
				{
					SUMO5();
					estado = CINCO_U_MAS ;
		
				}
				if(UN125())
				{
					CONF_125();
					estado = CICLO_125;
		
				}
				if(UN200())
				{
					CONF_200();
					estado = CICLO_200;
		
				}
				if(UNCERO())
				{
					CONF_0();
					estado = CICLO_0;
		
				}

				break;
			
			case CICLO_125:
			
				if(UNMENOS())
				{
					DISMINUYO5();
					estado = CINCO_U_MENOS;
		
				}
				if(UNMAS())
				{
					SUMO5();
					estado = CINCO_U_MAS ;
		
				}

				break;
			
			case CICLO_200:
			
				if(UNMENOS())
				{
					DISMINUYO5();
					estado = CINCO_U_MENOS;
		
				}
				if(UNMAS())
				{
					SUMO5();
					estado = CINCO_U_MAS ;
		
				}

				break;
			
			case CICLO_0:
			
				if(RECIBI())
				{
					
					estado = RECEPCION;
		
				}

				break;
			
			case CINCO_U_MAS :
			
				if(UNMAS())
				{
					SUMO5();
					estado = CINCO_U_MAS ;
		
				}

				break;
			
			case CINCO_U_MENOS:
			
				if(UNMENOS())
				{
					DISMINUYO5();
					estado = CINCO_U_MENOS;
		
				}

				break;
			
			default: estado = RECEPCION;
		}


}

//Funciones asociadas a los eventos

/**
*	\fn int UNMENOS(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
int UNMENOS(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint8_t data;
	data=uartReadByte(UART_USB);
	if(data=='-'){
		res=1;
	}
	else{
		res=0;
	}
	return res;
}

/**
*	\fn int UNMAS(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
int UNMAS(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint8_t data;
	data=uartReadByte(UART_USB);
	if(data=='+'){
		res=1;
	}
	else{
		res=0;
	}
	return res;


	return res;

}

/**
*	\fn int UN125(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
int UN125(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint8_t data[3];
	int i=0;
	for(;(Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR);i++){
		data[i]=Chip_UART_ReadByte(LPC_USART2);
	}
	i=0;
	if(data[0]=='1'){
		i++;
	}
	if(data[1]=='2'){
		i++;
	}
	if(data[2]=='5'){
		i++;
	}
	if(i==3){
		res=1;
	}
	else{
		res=0;
	}
	return res;
}

/**
*	\fn int UN200(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
int UN200(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint8_t data[3];
	int i=0;
	for(;(Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR);i++){
		data[i]=Chip_UART_ReadByte(LPC_USART2);
	}
	i=0;
	if(data[0]=='2'){
		i++;
	}
	if(data[1]=='0'){
		i++;
	}
	if(data[2]=='0'){
		i++;
	}
	if(i==3){
		res=1;
	}
	else{
		res=0;
	}
	return res;
}

/**
*	\fn int UNCERO(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
int UNCERO(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint8_t data;
	data=uartReadByte(UART_USB);
	if(data=='0'){
		res=1;
	}
	else{
		res=0;
	}
	return res;
}

/**
*	\fn int RECIBI(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
int RECIBI(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint8_t data;
	data=uartReadByte(UART_USB);
	if(data!='/0'){
		res=1;
	}
	else{
		res=0;
	}
	return res;
}

//Funciones asociadas a las acciones

/**
*	\fn void DISMINUYO5(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
void DISMINUYO5(void)
{
	//Codigo propio de la funcion
   uint8_t pwmVal = 0; /* 0 a 255 */
   pwmVal = pwmRead( PWM7 );
   dutycicle = dutycicle-5;
   if(dutycicle==255){
	   dutycicle=0;
   }
   pwmWrite( PWM7, dutycicle );
}

/**
*	\fn void SUMO5(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
void SUMO5(void)
{
	//Codigo propio de la funcion
	   uint8_t pwmVal = 0; /* 0 a 255 */
	   pwmVal = pwmRead( PWM7 );
	   dutycicle = dutycicle+5;
	   if(dutycicle==0){
		   dutycicle=255;
	   }
	   pwmWrite( PWM7, dutycicle );
}

/**
*	\fn void CONF_125(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
void CONF_125(void)
{
	//Codigo propio de la funcion
	   uint8_t pwmVal = 0; /* 0 a 255 */
	   pwmVal = pwmRead( PWM7 );
	   dutycicle = 125;
	   pwmWrite( PWM7, dutycicle );
}

/**
*	\fn void CONF_200(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
void CONF_200(void)
{
	//Codigo propio de la funcion
	   uint8_t pwmVal = 0; /* 0 a 255 */
	   pwmVal = pwmRead( PWM7 );
	   dutycicle = 200;
	   pwmWrite( PWM7, dutycicle );

}

/**
*	\fn void CONF_0(void)
*	\brief Resumen
*	\details Detalles
*	\author FACU
*	\date 29-11-2016 14:47:43
*/
void CONF_0(void)
{
	//Codigo propio de la funcion
   uint8_t pwmVal = 0; /* 0 a 255 */
   pwmVal = pwmRead( PWM7 );
   dutycicle = 0;
   pwmWrite( PWM7, dutycicle );
}
/*void uartWriteByte(uint8_t byte){

   while ((Chip_UART_ReadLineStatus(UART_USB) & UART_LSR_THRE) == 0); /* Wait for space in FIFO */
   //Chip_UART_SendByte(UART_USB, byte);
//}

/*void uartWrite(uint8_t * str){

   while(*str != 0){
	  uartWriteByte(*str);
	  *str++;
   }
}*/

/*uint8_t uartReadByte(void){

	uint8_t receivedByte = 0;

	if (Chip_UART_ReadLineStatus(UART_USB) & UART_LSR_RDR) {
	  receivedByte = Chip_UART_ReadByte(UART_USB);
}
   return receivedByte;
}*/
