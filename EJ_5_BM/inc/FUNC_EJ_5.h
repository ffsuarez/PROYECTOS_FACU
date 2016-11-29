/**
*	\file funciones.h
*	\brief Resumen del archivo
*	\details Descripcion detallada del archivo
*	\author FACU
*	\date 29-11-2016 14:47:43
*/

//Declaracion de estados
//#define TRUE  1
//#define FALSE  0
#define 	RECEPCION	0
#define 	CICLO_125	1
#define 	CICLO_200	2
#define 	CICLO_0	3
#define 	CINCO_U_MAS 	4
#define 	CINCO_U_MENOS	5

//Prototipos de los eventos
int UNMENOS(void);
int UNMAS(void);
int UN125(void);
int UN200(void);
int UNCERO(void);
int RECIBI(void);

//Prototipos de las acciones
void DISMINUYO5(void);
void SUMO5(void);
void CONF_125(void);
void CONF_200(void);
void CONF_0(void);

//Prototipo de las funciones

/* C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
*/
char* itoa(int value, char* result, int base);
//-------------------------------
//void uartWriteByte(uint8_t byte);
//void uartWrite(uint8_t * str);
//uint8_t uartReadByte(void);
