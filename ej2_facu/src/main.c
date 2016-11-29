/*==================[inclusions]=============================================*/

#include "main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

#include "funciones.h"		//incluyo
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** \brief Main function
 *
  *	Esta funcion es el punto de entrada del software
 * \retorna 0
 *
 * \Aclaracion: Esta funcion nunca retorna. El valor de retorno solo se añade
 *          para evitar errores o advertencias del compilador.
 */


 /* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
//void inicializar();
int main(void)
{
   /* Variable para almacenar el valor de tecla leido */
   bool_t valor;  //la dejo por las dudas..no creo que sirva
   /* ------------- INICIALIZACIONES ------------- */
   	/* Inicializar la placa */
   	boardConfig();
   	/* Inicializar DigitalIO */
   	digitalConfig( 0, ENABLE_DIGITAL_IO);
   	digitalConfig( TEC1, INPUT );
   	digitalConfig( TEC2, INPUT );
   	digitalConfig( TEC3, INPUT );
   	digitalConfig( TEC4, INPUT );
   	/* DESDE MAPA DE PERIFERICOS   GPIO0 = DIO32*/
   	digitalConfig( DIO32, INPUT_PULLUP ); //PARA CONECTAR CON PULLUP
   	digitalConfig( LEDR, OUTPUT );
   	digitalConfig( LEDG, OUTPUT );
   	digitalConfig( LEDB, OUTPUT );
   	digitalConfig( LED1, OUTPUT );
   	digitalConfig( LED2, OUTPUT );
   	digitalConfig( LED3, OUTPUT );
   	cont=0; 							//inicializacion de contador
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		maquina_estado();
	}
	return 0 ;
}

/*==================[end of file]============================================*/
