/**
*	\file funciones.c
*	\brief 
*	\details Descripcion detallada del archivo
*	\author A
*	\date 29-11-2016 20:05:07
*/


#include "sAPI.h"
#include "FUNC__BM.h"

//Implementacion Switch-Case

/**
*	\fn void maquina_estado()
*	\brief Implementacion Switch-Case
*	\details 
*	\author A
*	\date 29-11-2016 20:05:07
*/
int i=0;  //contador del display
void maquina_estado()
{
		static int estado = INICIAL;

		switch(estado)
		{
			case INICIAL:
			
				if(NO_APRETO())
				{
					
					estado = INICIAL;
		
				}
				if(APRETO1())
				{
					
					estado = ESTADO1;
		
				}
				if(APRETO2())
				{
					
					estado = ESTADO2;
		
				}

				break;
			
			case ESTADO1:

		         digitalWrite( LEDB, ON );
		         displaycero();
		         delay(500);
		         digitalWrite( LEDB, OFF );
		         digitalWrite(LED1,ON);
		         displayuno();
		         delay (500);
		         digitalWrite(LED1, OFF);
		         digitalWrite(LED2, ON);
		         displaydos();
		         delay(500);
		         digitalWrite(LED2, OFF);
		         digitalWrite(LED3, ON);
		         displaytres();
		         delay(500);
		         digitalWrite(LED3, OFF);

		         digitalWrite( LEDR, ON );
		         displaycuatro();
		         delay(500);
		         digitalWrite( LEDR, OFF );
		         digitalWrite(LED1,ON);
		         displaycinco();
		         delay (500);
		         digitalWrite(LED1, OFF);
		         digitalWrite(LED2, ON);
		         displayseis();
		         delay(500);
		         digitalWrite(LED2, OFF);
		         digitalWrite(LED3, ON);
		         displaysiete();
		         delay(500);
		         digitalWrite(LED3, OFF);

		         digitalWrite( LEDG, ON );
		         displayocho();
		         delay(500);
		         digitalWrite( LEDG, OFF );
		         digitalWrite(LED1,ON);
		         displaynueve();
		         delay (500);
		         digitalWrite(LED1, OFF);
		         digitalWrite(LED2, ON);
		         displayraya();
		         delay(500);
		         digitalWrite(LED2, OFF);
		         digitalWrite(LED3, ON);
		         //displayuno();
		         delay(500);
		         digitalWrite(LED3, OFF);
					
				estado = INICIAL;

				break;
			
			case ESTADO2:
				i++;
				if(i==1){
					displayuno();
				}
				if(i==2){
					displaydos();
				}
				if(i==3){
					displaytres();
				}
				if(i==4){
					displaycuatro();
				}
				if(i==5){
					displaycinco();
				}
				if(i==6){
					displayseis();
				}
				if(i==7){
					displaysiete();
				}
				if(i==8){
					displayocho();
				}
				if(i==9){
					displaynueve();
				}
				if(i==10){
					displayraya();
				}
				if(i>10){
					i=0;
				}
				estado = INICIAL;

				break;
			
			default: estado = INICIAL;
		}


}

//Funciones asociadas a los eventos

/**
*	\fn int NO_APRETO(void)
*	\brief Resumen
*	\details Detalles
*	\author A
*	\date 29-11-2016 20:05:07
*/
int NO_APRETO(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	if((digitalRead(TEC1)==ON)||(digitalRead(TEC2)==ON)){
		res=1;
	}
	else{
		res=0;
	}
	return res;

}

/**
*	\fn int APRETO1(void)
*	\brief Resumen
*	\details Detalles
*	\author A
*	\date 29-11-2016 20:05:07
*/
int APRETO1(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	if(digitalRead(TEC1)==OFF){
		res=1;
	}
	while(digitalRead(TEC1)==OFF){
	}
	return res;

}

/**
*	\fn int APRETO2(void)
*	\brief Resumen
*	\details Detalles
*	\author A
*	\date 29-11-2016 20:05:07
*/
int APRETO2(void)
{
	int res = 0 ;

	//Codigo propio de la funcion
	if(digitalRead(TEC2)==OFF){
		res=1;
	}
	while(digitalRead(TEC2)==OFF){
	}
	return res;

}


