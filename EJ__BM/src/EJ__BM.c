/*==================[inclusions]=============================================*/
#include "EJ__BM.h"       /* <= own header */

#include "sAPI.h"
#include "FUNC__BM.h"
#include "dsp7seg.h"
#ifndef CPU
#error CPU shall be defined
#endif
//#if (lpc4337 == CPU)
//#include "chip.h"
//#elif (mk60fx512vlq15 == CPU)
//#else
//#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Funcion main
 *
 *	Esta funcion es el punto de entrada del software
 * \retorna 0
 *
 * \Aclaracion: Esta funcion nunca retorna. El valor de retorno solo se a�ade
 *          para evitar errores o advertencias del compilador.
 */

int main(void)
{
	/* Inicializar la placa */
	boardConfig();
	tickConfig( 1, 0 );  //necesario para utiizar delay de libreria sapi
	/* Inicializar DigitalIO */
	digitalConfig( 0, ENABLE_DIGITAL_IO);

	/* Configuración de pines de entrada para
	   Teclas de la CIAA-NXP */
	digitalConfig( TEC1, INPUT );
	digitalConfig( TEC2, INPUT );
	digitalConfig( TEC3, INPUT );
	digitalConfig( TEC4, INPUT );

	/* Configuración de pines de salida para
	   Leds de la CIAA-NXP */
	digitalConfig( LEDR, OUTPUT );
	digitalConfig( LEDG, OUTPUT );
	digitalConfig( LEDB, OUTPUT );
	digitalConfig( LED1, OUTPUT );
	digitalConfig( LED2, OUTPUT );
	digitalConfig( LED3, OUTPUT );
	inicializacion();
	while(1) {
		maquina_estado();		//invocacion a funcion maquina_estado
	}
	return 0;
}

/*==================[end of file]============================================*/

