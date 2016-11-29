/**
*	\brief 
*	\details Funcion que implementa la lectura analogica sobre canal 1 del ADC0
*	\		En caso de que la lectura sea aproximadamente 2 o 5 [V]
*	\		se establece una salida sobre el DAC igual a 3.3[V] o  4[V].
*/
#include "sAPI.h"
#include "dsp7seg.h"
#include "FUNC_EJ_4.h" 

//Implementacion Switch-Case

/**
*	\fn void maquina_estado()
*	\brief Implementacion Switch-Case
*/
void maquina_estado()
{
		static int estado = LEO_POTENCIOMETRO;

		switch(estado)
		{
			case LEO_POTENCIOMETRO:
			
				if(MAYOR_2())
				{
					DAC_3_3();
					estado = SALIDA_3_3;
		
				}
				if(MAYOR_4())
				{
					DAC_4();
					estado = SALIDA_4;
		
				}

				break;
			
			case SALIDA_3_3:
			
				if(NINGUNO())
				{
					APAGAR_DAC();
					estado = LEO_POTENCIOMETRO;
		
				}
				if(MAYOR_4())
				{
					DAC_4();
					estado = SALIDA_4;
		
				}

				break;
			
			case SALIDA_4:
			
				if(NINGUNO())
				{
					APAGAR_DAC();
					estado = LEO_POTENCIOMETRO;
		
				}
				if(MENOR_4())
				{
					DAC_3_3();
					estado = SALIDA_3_3;
		
				}

				break;
			
			default: estado = LEO_POTENCIOMETRO;
		}


}

//Funciones asociadas a los eventos

/**
*	\fn int MAYOR_2(void)
*	\brief Si la lectura del ADC es mayor a 2[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int MAYOR_2(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(medida>2){
		res=1;
	}
	else{
		res=0;
	}

	return res;

}

/**
*	\fn int NINGUNO(void)
*	\brief Si la lectura del ADC no es mayor a 2[V]
*	\ ni tampoco mayor a 4[V], retorna 1.
*	\ en caso contrario retorna 0.
*/
int NINGUNO(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if((medida<2)){
		res=1;
		return res;
	};
	if((medida>2.1)||(medida<3.9)){
		res=1;
		return res;
	}
	if(medida>4.1){
		res=1;
		return res;
	}
	res=0;
		return res;

	//return res;

}

/**
*	\fn int MAYOR_4(void)
*	\brief Si la lectura del ADC es mayor a 4[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int MAYOR_4(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(medida>4){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int MENOR_4(void)
*	\brief Si la lectura del ADC es menor a 4[V] retorna 1.
*	\ en caso contrario retorna 0.
*/
int MENOR_4(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	uint16_t muestra = 0;  // variable donde se almacena valor leido del ADC CH 1
	float medida=0;
	muestra = analogRead( AI0 );
	medida=(5.0*muestra)/(1024);
	if(medida<4){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

//Funciones asociadas a las acciones

/**
*	\fn void DAC_3_3(void)
*	\brief Establece una salida sobre el DAC igual a 3.3[V]
*/
void DAC_3_3(void)
{
	uint16_t salida = 0;  // variable donde se almacena valor leido del ADC CH 1
	//Codigo propio de la funcion
	salida=670;
	analogWrite( AO, salida );
}

/**
*	\fn void APAGAR_DAC(void)
*	\brief Establece una salida sobre el DAC igual a 0[V]
*/
void APAGAR_DAC(void)
{
	//Codigo propio de la funcion
	uint16_t salida = 0;  // variable donde se almacena valor leido del ADC CH 1
		//Codigo propio de la funcion
		salida=819;
		analogWrite( AO, salida );
}

/**
*	\fn void DAC_4(void)
*	\brief Establece una salida sobre el DAC igual a 4[V]
*/
void DAC_4(void)
{
	//Codigo propio de la funcion
	uint16_t salida = 0;  // variable donde se almacena valor leido del ADC CH 1
	//Codigo propio de la funcion
	salida=819;
	analogWrite( AO, salida );
}

