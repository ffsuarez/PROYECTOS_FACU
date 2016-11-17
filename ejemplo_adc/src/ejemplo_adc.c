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
#include "os.h"               /* <= operating system header */
#include "ejemplo_adc.h"       /* <= own header */
#include "sAPI.h"
#include "sAPI_Board.h"
#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"
#include "sAPI_DigitalIO.h"
#include "sAPI_AnalogIO.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
int i=0;
/*==================[internal functions definition]==========================*/
char* ftoa(float f_number,char *buffer, uint8_t places)
{
    int pos = 0,
    		ix,
			dp,
			num;


    if ( f_number < 0 )
    {
        buffer[ pos++ ]='-';
        f_number = - f_number;
    }
    dp = 0;

    while ( f_number >= 10.0 )
    {
        f_number = f_number / 10.0;
        dp++;
    }
  //  for ( ix = 1 ;ix < 8; ix++ )
    for ( ix = 1 ;ix < places + 2; ix++ )
    {
            num = f_number;
            f_number = f_number - num;
            if ( num > 9 )
                buffer[ pos++ ] = '#';
            else
                buffer[ pos++ ] = '0' + num;
            if ( dp == 0 )
            	buffer[ pos++ ] = '.';
            f_number = f_number * 10.0;
            dp--;
    }
    return buffer;
}

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

	StartOS(AppMode1);
}

void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

TASK (INICIALIZACION) {
	lcd_init_port();
	lcd_init();
	lcd_gotoxy(1,1);
	printf_lcd("ADC por tecla1");
	lcd_gotoxy(1,2);
	digitalConfig(0,ENABLE_DIGITAL_IO);
	analogConfig(ENABLE_ANALOG_INPUTS);
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
	analogConfig( ENABLE_ANALOG_INPUTS );
	ActivateTask(MUESTRA);
	TerminateTask();
}

TASK (MEDICION) {
	float medida;
	char string[4];
	WaitEvent(tomar_medida);
	ClearEvent(tomar_medida);
	GetResource(res_adc);
	medida=analogRead(AI0);
	medida=(5.0*medida)/(1024);
	ftoa(medida,string,2);
	lcd_gotoxy(1,2);
	printf_lcd("V entr: ");
	printf_lcd(string);
	printf_lcd(" V");
	ReleaseResource(res_adc);
	ChainTask(JUEGO);

}
TASK (JUEGO) {
	if(i==0){
		SetRelAlarm(Blinkeo,500,0);
		digitalWrite(LED1,ON);
		digitalWrite(LED2,OFF);
		digitalWrite(LED3,OFF);
		i++;
		TerminateTask();
	}
	if(i==1){
		SetRelAlarm(Blinkeo,500,0);
		digitalWrite(LED1,OFF);
		digitalWrite(LED2,ON);
		digitalWrite(LED3,OFF);
		i++;
		TerminateTask();
	}
	if(i==2){
		SetRelAlarm(Blinkeo,500,0);
		digitalWrite(LED1,OFF);
		digitalWrite(LED2,OFF);
		digitalWrite(LED3,ON);
		i++;
		TerminateTask();
	}

	i=0;
	ActivateTask(MUESTRA);
	TerminateTask();

}
TASK (MUESTRA){

	if(digitalRead(TEC1)==OFF){
		ActivateTask(MEDICION); //como muestra tiene una prioridad mayor no se deberia ir a medicion
		SetEvent(MEDICION,tomar_medida);
		TerminateTask();

	}
	ChainTask(MUESTRA);
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

