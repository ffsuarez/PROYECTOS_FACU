/**
*	\brief 
*	\details Funcion que implementa la lectura analogica sobre canal 1 del ADC0
*	\		En caso de que la lectura sea aproximadamente 1,2,3,4 o 5 [V]
*	\		se realiza la muestra del correspondiente digito sobre display 7
*	\		segmentos.
*/


#include "sAPI.h"
#include "FUNC_EJ_3.h" 
#include "dsp7seg.h"
//Implementacion Switch-Case

/**
*	\fn void maquina_estado()
*	\brief Implementacion Switch-Case
*/
void maquina_estado()
{
		static int estado = INTERMEDIO;

		switch(estado)
		{
			case UN_VOLT:
				digitalWrite(LED1,ON);
				digitalWrite(LED2,OFF);
				digitalWrite(LED3,OFF);
				digitalWrite(LEDB,OFF);
				digitalWrite(DIO11,OFF);
				displayuno();
				if(NOES1())
				{
					
					estado = INTERMEDIO;
		
				}

				break;
			
			case DOS_VOLT:
				digitalWrite(LED1,ON);
				digitalWrite(LED2,ON);
				digitalWrite(LED3,OFF);
				digitalWrite(LEDB,OFF);
				digitalWrite(DIO11,OFF);
				displaydos();
				if(NOES2())
				{
					
					estado = INTERMEDIO;
		
				}

				break;
			
			case TRES_VOLT:
				digitalWrite(LED1,ON);
				digitalWrite(LED2,ON);
				digitalWrite(LED3,ON);
				digitalWrite(LEDB,OFF);
				digitalWrite(DIO11,OFF);
				displaytres();
				if(NOES3())
				{
					
					estado = INTERMEDIO;
		
				}

				break;
			
			case CUATRO_VOLT:
				digitalWrite(LED1,ON);
				digitalWrite(LED2,ON);
				digitalWrite(LED3,ON);
				digitalWrite(LEDB,ON);
				digitalWrite(DIO11,OFF);
				displaycuatro();
				if(NOES4())
				{
					
					estado = INTERMEDIO;
		
				}

				break;
			
			case CINCO_VOLT:
				digitalWrite(LED1,ON);
				digitalWrite(LED2,ON);
				digitalWrite(LED3,ON);
				digitalWrite(LEDB,ON);
				digitalWrite(DIO11,ON);
				displaycinco();
				if(NOES5())
				{
					
					estado = INTERMEDIO;
		
				}

				break;
			
			case INTERMEDIO:
				digitalWrite(LED1,OFF);
				digitalWrite(LED2,OFF);
				digitalWrite(LED3,OFF);
				digitalWrite(LEDB,OFF);
				digitalWrite(DIO11,OFF);
				displayraya();
				if(LEYO_1())
				{
					
					estado = UN_VOLT;
		
				}
				if(LEYO_2())
				{
					
					estado = DOS_VOLT;
		
				}
				if(LEYO_3())
				{
					
					estado = TRES_VOLT;
		
				}
				if(LEYO_4())
				{
					
					estado = CUATRO_VOLT;
		
				}
				if(LEYO_5())
				{
					
					estado = CINCO_VOLT;
		
				}
				if(NOESNINGUNO())
				{
					
					estado = INTERMEDIO;
		
				}

				break;
			
			default: estado = INTERMEDIO;
		}


}

//Funciones asociadas a los eventos

/**
*	\fn int LEYO_1(void)
*	\brief Si la lectura del ADC es aproximadamente 1[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int LEYO_1(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if((medida>0.9)&&(medida<1.1)){
		res=1;
	}
	else{
		res=0;
	}

	return res;

}

/**
*	\fn int LEYO_2(void)
*	\brief Si la lectura del ADC es aproximadamente 2[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int LEYO_2(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if((medida>1.9)&&(medida<2.1)){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int LEYO_3(void)
*	\brief Si la lectura del ADC es aproximadamente 3[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int LEYO_3(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if((medida>2.9)&&(medida<3.1)){
		res=1;
	}
	else{
		res=0;
	}
	return res;
}

/**
*	\fn int LEYO_4(void)
*	\brief Si la lectura del ADC es aproximadamente 4[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int LEYO_4(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if((medida>3.9)&&(medida<4.1)){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int LEYO_5(void)
*	\brief Si la lectura del ADC es aproximadamente 5[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int LEYO_5(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if((medida>4.8)){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int NOES1(void)
*	\brief Si la lectura del ADC es distinta de 1[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int NOES1(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(!((medida>0.95)&&(medida<1.15))){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int NOES2(void)
*	\brief Si la lectura del ADC es distinta de 2[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int NOES2(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(!((medida>1.95)&&(medida<2.15))){
		res=1;
	}
	else{
		res=0;
	}


	return res;

}

/**
*	\fn int NOES3(void)
*	\brief Si la lectura del ADC es distinta de 3[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int NOES3(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(!((medida>2.95)&&(medida<3.15))){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int NOES4(void)
*	\brief Si la lectura del ADC es distinta de 4[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int NOES4(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(!((medida>3.95)&&(medida<4.15))){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int NOES5(void)
*	\brief Si la lectura del ADC es distinta de 5[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int NOES5(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(!((medida>4.95))){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int NINGUNA(void)
*	\brief Si la lectura del ADC es distinta de 1[V],2[V]
*	\ 3[V],4[V] o 5[V] retorna 1.
*	\ En caso contrario retorna 0.
*/
/*int NINGUNA(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(!((medida>0.95)&&(medida<1.15))){
		if(!((medida>1.95)&&(medida<2.15))){
			if(!((medida>2.95)&&(medida<3.15))){
				if(!((medida>3.95)&&(medida<4.15))){
					if(!((medida>4.95))){
						res=1;
					}
				}
			}
		}
	}
	else{
		res=0;
	}
	return res;
}*/

/**
*	\fn int NOESNINGUNO(void)
*	\brief Si la lectura del ADC es distinta de 1[V],2[V]
*	\ 3[V],4[V] o 5[V] retorna 1.
*	\ En caso contrario retorna 0.
*/
int NOESNINGUNO(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(!((medida>0.9)&&(medida<1.1))){
		if(!((medida>1.9)&&(medida<2.1))){
			if(!((medida>2.9)&&(medida<3.1))){
				if(!((medida>3.9)&&(medida<4.1))){
					if(!((medida>4.9))){
						res=1;
					}
				}
			}
		}
	}
	else{
		res=0;
	}
	return res;

}

//Funciones asociadas a las acciones

