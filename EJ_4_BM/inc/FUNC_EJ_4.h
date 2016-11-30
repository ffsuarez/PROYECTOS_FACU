/**
*	\file FUNC_EJ_4.h
*	\brief Archivo cabecera de "FUNC_EJ_4.c"
*/

//Declaracion de estados
//#define TRUE  1	--> Previamente declarado sobre Firmware
//#define FALSE  0	--> Previamente declarado sobre Firmware
#define 	LEO_POTENCIOMETRO	0
#define 	SALIDA_3_3	1
#define 	SALIDA_4	2

//Prototipos de los eventos
int MAYOR_2(void);
int NINGUNO(void);
int MAYOR_4(void);
int MENOR_4(void);

//Prototipos de las acciones
void DAC_2(void);
void APAGAR_DAC(void);
void DAC_3(void);
