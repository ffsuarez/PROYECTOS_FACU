/**
*	\file funciones.c
*	\brief: Archivo que contiene las funciones que utiliza la maquina de
*	\estado para establecer la secuencia de luces.
*/



#include "funciones.h" 
#include "sAPI.h"         /* <= sAPI header */
//Implementacion Switch-Case

/**
*	\fn void maquina_estado()
*	\brief Implementacion Switch-Case
*/
void maquina_estado()
{
		static int estado = INICIAL;

		switch(estado)
		{
			case INICIAL:
			
				if(PRESS())
				{
					LED_R();
					estado = ROJO;
				}
				break;
			
			case ROJO:
				if(PRESS())
				{
					P_LED_1();
					estado = LED_1;
				}
				break;
			
			case LED_1:
			
				if(PRESS())
				{
					P_LED_2();
					estado = LED_2;
				}

				break;
			
			case LED_2:
			
				if(PRESS())
				{
					P_LED_3();
					estado = LED_3;
				}

				break;
			
			case LED_3:
			
				if(PRESS_7())
				{
					LED_G();
					estado = ROJO;
				}
				if(PRESS_4())
				{
					LED_B();
					estado = ROJO;
				}
				if(PRESS_10())
				{
					LED_R();
					BORROW();
					estado = ROJO;
		
				}

				break;
			
			default: estado = INICIAL;
		}


}

//Funciones asociadas a los eventos

/**
*	\fn int PRESS(void)
*	\brief Establece la lectura de una entrada digital
*	sobre tecla "TEC1" de la placa.
*/
int PRESS(void)
{
	int res = 0 ;
	//int i=0;
	//Codigo propio de la funcion
	if(digitalRead(TEC1)==OFF){
		res=1;
		cont++;  //incremento contador
		while(digitalRead(TEC1)==OFF){
		}
	}
	return res;
}

/**
*	\fn int PRESS_4(void)
*	\brief Si el usuario "realiza primer pasada sobre los 4 leds" se prende led R
*/
int PRESS_4(void)
{
	int res = 0 ;
	//int i=0;
	//Codigo propio de la funcion
	if(digitalRead(TEC1)==OFF){
			//res=1;
			cont++;  //incremento contador
			while(digitalRead(TEC1)==OFF){
			}
	}
	if(cont==5){
		res=1;
	}
	return res;
}

/**
*	\fn int PRESS_7(void)
*	\brief Si el usuario "realiza segunda pasada sobre los 4 leds" se prende led B
*/
int PRESS_7(void)
{
	int res = 0 ;
	//int i=0;
	//Codigo propio de la funcion
	if(digitalRead(TEC1)==OFF){
			//res=1;
			cont++;  //incremento contador
			while(digitalRead(TEC1)==OFF){
					}
	}
	if (cont==9){
		res=1;
	}
	return res;
}

/**
*	\fn int PRESS_10(void)
*	\brief Si el usuario "realiza tercer pasada sobre los 4 leds" se prende led G
*/
int PRESS_10(void)
{
	int res = 0 ;
	//int i=0;
	//Codigo propio de la funcion
	if(digitalRead(TEC1)==OFF){
			//res=1;
			cont++;  //incremento contador
			while(digitalRead(TEC1)==OFF){
					}
	}
	if(cont==13){
		res=1;
	}
	return res;

}

//Funciones asociadas a las acciones

/**
*	\fn void LED_R(void)
*	\brief Encendido de LEDR sobre la placa
*/
void LED_R(void)
{
	//Codigo propio de la funcion
	digitalWrite(LEDR,ON);
	digitalWrite(LEDB,OFF);
	digitalWrite(LEDG,OFF);
	digitalWrite(LED1,OFF);
	digitalWrite(LED2,OFF);
	digitalWrite(LED3,OFF);
}

/**
*	\fn void LED1(void)
*	\brief Encendido de LED1 sobre la placa
*/
void P_LED_1(void)
{
	//Codigo propio de la funcion
	digitalWrite(LEDR,OFF);
	digitalWrite(LEDB,OFF);
	digitalWrite(LEDG,OFF);
	digitalWrite(LED1,ON);
	digitalWrite(LED2,OFF);
	digitalWrite(LED3,OFF);
}

/**
*	\fn void LED2(void)
*	\brief Encendido de LED2 sobre la placa
*/
void P_LED_2(void)
{
	//Codigo propio de la funcion
	digitalWrite(LEDR,OFF);
	digitalWrite(LEDB,OFF);
	digitalWrite(LEDG,OFF);
	digitalWrite(LED1,OFF);
	digitalWrite(LED2,ON);
	digitalWrite(LED3,OFF);
}

/**
*	\fn void LED3(void)
*	\brief Encendido de LED3 sobre la placa
*/
void P_LED_3(void)
{
	//Codigo propio de la funcion
	digitalWrite(LEDR,OFF);
	digitalWrite(LEDB,OFF);
	digitalWrite(LEDG,OFF);
	digitalWrite(LED1,OFF);
	digitalWrite(LED2,OFF);
	digitalWrite(LED3,ON);
}

/**
*	\fn void LED_G(void)
*	\brief Encendido de LEDG sobre la placa
*/
void LED_G(void)
{
	//Codigo propio de la funcion
	digitalWrite(LEDG,ON);
	digitalWrite(LEDR,OFF);
	digitalWrite(LEDB,OFF);
	digitalWrite(LED1,OFF);
	digitalWrite(LED2,OFF);
	digitalWrite(LED3,OFF);
}

/**
*	\fn void LED_B(void)
*	\brief Encendido de LEDB sobre la placa
*/
void LED_B(void)
{
	//Codigo propio de la funcion
	digitalWrite(LEDB,ON);
	digitalWrite(LEDR,OFF);
	digitalWrite(LEDG,OFF);
	digitalWrite(LED1,OFF);
	digitalWrite(LED2,OFF);
	digitalWrite(LED3,OFF);
}


/**
*	\fn void BORROW(void)
*	\brief Renueva contador
*/
void BORROW(void)
{
	//Codigo propio de la funcion
	cont=1;
}

