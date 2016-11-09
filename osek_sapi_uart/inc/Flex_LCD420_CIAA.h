/*
 * Flex_LCD420_CIAA.h
 *
 *  Created on: 5 de jul. de 2016
 *      Author: benitezjuandedios
 */

#ifndef FLEX_LCD420_CIAA_H_
#define FLEX_LCD420_CIAA_H_

// Flex_LCD420.c

/*
 * Estos son los pines para utilizar con la EDU_CIAA de acuerdo al archivo sAPI_Periphereal.h
 * Estos pines estan ruteados a los pines exteriores LCD1, LCD2, LCD3, LCD4, LCDRS y GPIO01 que
 * corresponde al LCD_E.
 *
 */
/* configuracion de los puertos para usar lo que tiene el sAPI_DigitalIO.c
 con esto puedo configuro los GPIO para usar el LCD*/
#define LCD_DB4 DIO16  // LCD1
#define LCD_DB5 DIO17  // LCD2
#define LCD_DB6 DIO18  // LCD3
#define LCD_DB7 DIO20  // LCD4

#define LCD_RS DIO19   // LCDRS
#define LCD_E DIO15	   // GPIO01

// These are the line addresses for most 4x20 LCDs.

#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x40
#define LCD_LINE_3_ADDRESS 0x14
#define LCD_LINE_4_ADDRESS 0x54

// These are the line addresses for LCD's which use
// the Hitachi HD66712U controller chip.
/*
#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x20
#define LCD_LINE_3_ADDRESS 0x40
#define LCD_LINE_4_ADDRESS 0x60
*/
/*---------- DEFINICION DE LOS DELAYS QUE SE USAN EN EL CODIGO ---------------*/

#define DELAY_CYCLE 1
#define DELAY_US 1

/*------------DEFINICION DEL TIPO DE LCD QUE SE USA---------------------------*/

#define LCD_TYPE 2   // 0=5x7, 1=5x10, 2=2 lines(or more)


 /*-----------DECLARACIÓN DE VARIABLES GLOBALES ------------------------------*/

int8_t lcd_line;

int8_t const LCD_INIT_STRING[4] =
{
 0x20 | (LCD_TYPE << 2),  	// Set mode: 4-bit, 2+ lines, 5x8 dots
0x10, 						//pongo el display en OFF
 1,                      	// Clear display
 6                       	// Increment cursor
 };

/*-------------- PROTOTIPOS DE LAS FUNCIONES QUE SE USAN --------------------- */

void lcd_send_nibble(int8_t nibble); 			// CONVIERTE EL DATO EN 4 BITS Y LO SACA POR LOS GPIO


void lcd_send_byte(int8_t address, int8_t n);	 //ENVÍA UN DATO TIPO BYTE POR MEDIO DE 2 NIBBLE

void lcd_init(void); 							// INICIALIZACIÓN DEL LCD

void lcd_gotoxy(int8_t x, int8_t y);			//POSICIONA EL CURSOR EN UNA FILA Y COLUMNA



void lcdWrite( char* c );							// SACA UN CARACTER POR EL LCD


char* itoa(int value, char* result, int base);    // convierte de un int a un cadena de char

char* ftoa(float f_number,char *buffer, uint8_t places);     // convierte de un float a una cadena de char




#endif /* FLEX_LCD420_CIAA_H_ */
