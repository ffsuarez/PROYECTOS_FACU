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

#include "osek_eventos_3.h"         /* <= own header */

#include "sAPI.h"

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
int count=500;
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

	if(digitalRead(TEC1)==OFF){
		ActivateTask(BLINKS1);
		SetEvent(BLINKS1,tiempo);
		TerminateTask();
	}
    //SetEvent(LED_1,tecla1);
    //digitalConfig( DIO15, OUTPUT );
   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every 250 ticks (250 ms)
    */
   //SetRelAlarm(ActivatePERIODICA2, 350, 250);

   /* terminate task */
   ChainTask(INICIAL);
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
 */
TASK(BLINKS1)
{
	WaitEvent(tiempo);
	digitalWrite(LED3,OFF);
	digitalWrite(LEDB,OFF);
	digitalWrite(LED1,ON);
	digitalWrite(LED2,ON);
	ClearEvent(tiempo);
	//activo una alarma que expire en 500 ms o segun valga count
	SetRelAlarm(SetEventtiempo,count,0);
	WaitEvent(tiempo);
	digitalWrite(LED1,OFF);
	digitalWrite(LED2,OFF);
	ClearEvent(tiempo);
	ActivateTask(BLINKS2);
	SetRelAlarm(SetEventtiempo2,count,0);
	TerminateTask();
}


TASK(BLINKS2)
{
	WaitEvent(tiempo2);
	digitalWrite(LED1,OFF);
	digitalWrite(LED2,OFF);
	digitalWrite(LED3,ON);
	digitalWrite(LEDB,ON);
	ClearEvent(tiempo2);
	//activo una alarma que expire en 500 ms
	SetRelAlarm(SetEventtiempo2,500,0);
	WaitEvent(tiempo2);
	digitalWrite(LED3,OFF);
	digitalWrite(LEDB,OFF);
	ClearEvent(tiempo2);
	ActivateTask(BLINKS1);
	SetRelAlarm(SetEventtiempo,500,0);
	TerminateTask();
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

