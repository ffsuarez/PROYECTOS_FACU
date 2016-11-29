/**
*	\file FUNC_EJ_3.h
*	\brief Archivo cabecera de "FUNC_EJ_3.c"
*/

//Declaracion de estados
//#define TRUE  1   --> Previamente declarado sobre Firmware
//#define FALSE  0	--> Previamente declarado sobre Firmware
#define 	UN_VOLT	0
#define 	DOS_VOLT	1
#define 	TRES_VOLT	2
#define 	CUATRO_VOLT	3
#define 	CINCO_VOLT	4
#define 	INTERMEDIO	5

//Prototipos de los eventos
int LEYO_1(void);
int LEYO_2(void);
int LEYO_3(void);
int LEYO_4(void);
int LEYO_5(void);
int NOES1(void);
int NOES2(void);
int NOES3(void);
int NOES4(void);
int NOES5(void);
int NINGUNA(void);
int NOESNINGUNO(void);

//Prototipos de las acciones
