/*==================[inclusions]=============================================*/
#include "EJ_4_BM.h"       /* <= own header */

#include "sAPI.h"
#include "FUNC_EJ_4.h"
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
/** \brief Main function
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
   /* perform the needed initialization here */
	boardConfig();
	tickConfig( 1, 0 );  //necesario para utiizar delay de libreria sapi
	digitalConfig(0,ENABLE_DIGITAL_IO);
	analogConfig( ENABLE_ANALOG_INPUTS );
	analogConfig( ENABLE_ANALOG_OUTPUTS );
	digitalConfig( LEDR, OUTPUT );
	digitalConfig( LEDG, OUTPUT );
	digitalConfig( LEDB, OUTPUT );
	digitalConfig( LED1, OUTPUT );
	digitalConfig( LED2, OUTPUT );
	digitalConfig( LED3, OUTPUT );
	digitalConfig( DIO11, OUTPUT );  // inicializacion salida GPIO8

	inicializacion();				// inicializacion de pines de display 7 segmentos

   while(1) {
		maquina_estado();			//invocacion a funcion maquina_estado
   }
   return 0;
}

/*==================[end of file]============================================*/

