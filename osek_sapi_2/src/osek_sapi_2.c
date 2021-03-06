/* Copyright 2014, Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
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

/** \brief Blinking_echo example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Blinking Blinking_echo example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * PR           Pablo Ridolfi
 * JuCe         Juan Cecconi
 * GMuro        Gustavo Muro
 * ErPe         Eric Pernia
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150603 v0.0.3   ErPe change uint8 type by uint8_t
 *                        in line 172
 * 20141019 v0.0.2   JuCe add printf in each task,
 *                        remove trailing spaces
 * 20140731 v0.0.1   PR   first functional version
 */
/*
 * https://groups.google.com/forum/#!searchin/ciaa-firmware/boolean%7Csort:relevance/ciaa-firmware/SNLmTVZbIkk/iSPYr-l-EAAJ
 * DICE QUE En concreto, el problema con la nueva lpcopen es que define TRUE, FALSE y boolean de forma que chocan con las definiciones del RTOS.

	Hay tres soluciones.

*UNA DE ELLAS ES Eliminar las definiciones de TRUE/FALSE/boolean de lpcopen (no muy limpio pero aceptable)
*/
/*==================[inclusions]=============================================*/
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */
#include "osek_sapi_2.h"         /* <= own header */
#include "chip.h"
#include "sAPI.h"
#include "sAPI_Board.h"
#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"
#include "sAPI_DigitalIO.h"
//#include "Flex_LCD420_CIAA.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/out/0
 */
static int32_t fd_out;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

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
	 boardConfig();
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

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(INICIAL)
{
	digitalConfig( 0, ENABLE_DIGITAL_IO );
	digitalConfig( TEC1, INPUT );
    digitalConfig( TEC2, INPUT );
    digitalConfig( TEC3, INPUT );
    digitalConfig( TEC4, INPUT );
    digitalConfig( LEDR, OUTPUT );
    digitalConfig( LEDG, OUTPUT );
    digitalConfig( LEDB, OUTPUT );
    digitalConfig( LED1, OUTPUT );
    digitalConfig( LED2, OUTPUT );
    digitalConfig( LED3, OUTPUT );
    lcd_init();
    lcd_gotoxy(1,1);

    SetEvent(LED_1,tecla1);
    //digitalConfig( DIO15, OUTPUT );
   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every 250 ticks (250 ms)
    */
   //SetRelAlarm(ActivatePERIODICA2, 350, 250);

   /* terminate task */
   TerminateTask();
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
 */
TASK(LED_1)
{
	ClearEvent(tecla4);
	if(digitalRead(TEC1)==ON){
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, FALSE);
	   lcd_gotoxy(1,2);
	   lcdWrite("1");
   }
   else{
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
   }
   SetEvent(LED_2,tecla2);
   TerminateTask();
}

TASK(LED_2)
{
   if(digitalRead(TEC2)==ON){
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, FALSE);
	   lcd_gotoxy(1,2);
	   lcdWrite("2");
   }
   else{
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
   }
   SetEvent(LED_3,tecla3);
   ClearEvent(tecla2);
   TerminateTask();
}

TASK(LED_3)
{
   if(digitalRead(TEC3)==ON){
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, FALSE);
	   lcd_gotoxy(1,2);
	   lcdWrite("3");
   }
   else{
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
   }
   SetEvent(LED_4,tecla4);
   ClearEvent(tecla3);
   TerminateTask();
}

TASK(LED_4)
{
   if(digitalRead(TEC4)==ON){
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, FALSE);
	   lcd_gotoxy(1,2);
	   lcdWrite("4");
   }
   else{
	   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, TRUE);
   }
   SetEvent(LED_1,tecla1);
   ClearEvent(tecla3);
   TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

