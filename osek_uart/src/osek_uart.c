/*==================[inclusions]=============================================*/
#include "os.h"               /* <= operating system header */
#include "osek_uart.h"         /* <= own header */
#include "sAPI.h"
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaak.h"            /* <= ciaa kernel header */
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint8_t data;
/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
	StartOS(AppMode1);
   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

uint8_t leerUART(void){
	uint8_t receivedByte = 1;
	if (Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR){
		receivedByte = Chip_UART_ReadByte(LPC_USART2);
	}
	return receivedByte;
}

ISR(UART2_IRQHandler)
{
	uint8_t byte;
	char letra;
	byte=leerUART();
	data=byte;
	letra=byte;
	//lcd_init();
	//lcd_gotoxy(9,1);
	lcd_putc(letra);
	while ((Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_THRE) == 0); /* Wait for space in FIFO */{
		//data=byte;
		Chip_UART_SendByte(LPC_USART2, byte);
	}
	//ActivateTask(recepcion);
	SetEvent(recepcion,palabra);
}

TASK (Inicializar){
	boardConfig();
	lcd_init_port();
	lcd_init();
	lcd_gotoxy(1,1);
	printf_lcd("Palabra:");
	uartConfig(UART_USB,9600);
	uartWriteString(UART_USB,"Palabra\n");
	//lcd_gotoxy(1,9);
	EnableAllInterrupts();
	ActivateTask(recepcion);
	WaitEvent(palabra);
	TerminateTask();
}

TASK (recepcion){
	//lcd_init();
	lcd_gotoxy(1,1);
	printf_lcd("Palabra:");
	WaitEvent(palabra);
	SetEvent(recepcion,palabra);
	if(data=='L'){
		uartWriteString(UART_USB,"\nMe llego");
	}
	ChainTask(recepcion);
}
/*==================[end of file]============================================*/

