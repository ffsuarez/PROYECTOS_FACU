#include <dsp7seg.h>
//------------------DIAGRAMA----------------------------
//		A------------>GPIO0
//		B------------>GPIO1
//		C------------>GPIO2
//		D------------>GPIO3
//		E------------>GPIO4
//		F------------>GPIO5
//		G------------>GPIO6
//      G2--->330ohm--->GND     
//------------------------------------------------------
void inicializacion(void){
	digitalConfig( 0, ENABLE_DIGITAL_IO );
	digitalConfig( DIO32, OUTPUT );		//gpio0 EDU-CIAA
	digitalConfig( DIO15, OUTPUT );		//gpio1 EDU-CIAA
	digitalConfig( DIO31, OUTPUT );		//gpio2 EDU-CIAA
	digitalConfig( DIO14, OUTPUT );		//gpio3 EDU-CIAA
	digitalConfig( DIO30, OUTPUT );		//gpio4 EDU-CIAA
	digitalConfig( DIO13, OUTPUT );		//gpio5 EDU-CIAA
	digitalConfig( DIO29, OUTPUT );		//gpio6 EDU-CIAA
	digitalConfig( DIO12, OUTPUT );		//gpio7 EDU-CIAA
}
void displaycero(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, ON );		//D 1
	digitalWrite( DIO30, ON );		//E 1
	digitalWrite( DIO13, ON );		//F 1
	digitalWrite( DIO29, OFF );		//G 0	
}
void displayuno(void){
	digitalWrite( DIO32, OFF );		//A 0
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, OFF );		//D 0
	digitalWrite( DIO30, OFF );		//E 0
	digitalWrite( DIO13, OFF );		//F 0
	digitalWrite( DIO29, OFF );		//G 0	
}
void displaydos(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, OFF );		//C 0
	digitalWrite( DIO14, ON );		//D 1
	digitalWrite( DIO30, ON );		//E 1
	digitalWrite( DIO13, OFF );		//F 0
	digitalWrite( DIO29, ON );		//G 1	
}
void displaytres(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, ON );		//D 1
	digitalWrite( DIO30, OFF );		//E 0
	digitalWrite( DIO13, OFF );		//F 0
	digitalWrite( DIO29, ON );		//G 1	
}
void displaycuatro(void){
	digitalWrite( DIO32, OFF );		//A 0
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, OFF );		//D 0
	digitalWrite( DIO30, OFF );		//E 0
	digitalWrite( DIO13, ON );		//F 1
	digitalWrite( DIO29, ON );		//G 1	
}
void displaycinco(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, OFF );		//B 0
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, ON );		//D 1
	digitalWrite( DIO30, OFF );		//E 0
	digitalWrite( DIO13, ON );		//F 1
	digitalWrite( DIO29, ON );		//G 1	
}
void displayseis(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, OFF );		//B 0
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, ON );		//D 1
	digitalWrite( DIO30, ON );		//E 1
	digitalWrite( DIO13, ON );		//F 1
	digitalWrite( DIO29, ON );		//G 1	
}
void displaysiete(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, OFF );		//D 0
	digitalWrite( DIO30, OFF );		//E 0
	digitalWrite( DIO13, OFF );		//F 0
	digitalWrite( DIO29, OFF );		//G 0	
}
void displayocho(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, ON );		//D 1
	digitalWrite( DIO30, ON );		//E 1
	digitalWrite( DIO13, ON );		//F 1
	digitalWrite( DIO29, ON );		//G 1	
}
void displaynueve(void){
	digitalWrite( DIO32, ON );		//A 1
	digitalWrite( DIO15, ON );		//B 1
	digitalWrite( DIO31, ON );		//C 1
	digitalWrite( DIO14, OFF );		//D 0
	digitalWrite( DIO30, OFF );		//E 0
	digitalWrite( DIO13, ON );		//F 1
	digitalWrite( DIO29, ON );		//G 1	
}
void displayraya(void){
	digitalWrite( DIO32, OFF );		//A 0
	digitalWrite( DIO15, OFF );		//B 0
	digitalWrite( DIO31, OFF );		//C 0
	digitalWrite( DIO14, OFF );		//D 0
	digitalWrite( DIO30, OFF );		//E 0
	digitalWrite( DIO13, OFF );		//F 1
	digitalWrite( DIO29, ON );		//G 0
}
