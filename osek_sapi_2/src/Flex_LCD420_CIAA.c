//#include "chip.h"
#include "sAPI.h"
#include "Flex_LCD420_CIAA.h"
/*#define TICKRATE_HZ1 10
int32_t ticks=0;
void SysTick_Handler(void){

	ticks++;
}*/
//-------------------------------------
void delaym(void)
{
   long int i=0,x=0;
   for(i=0; i<9999; i++){x++;}//
}

void lcd_send_nibble( int8_t nibble )
{
// Note:  !! converts an integer expression
// to a boolean (1 or 0).
 digitalWrite( LCD_DB4, !!( nibble & 1 ) );
 digitalWrite( LCD_DB5, !!( nibble & 2 ) );
 digitalWrite( LCD_DB6, !!( nibble & 4 ) );
 digitalWrite( LCD_DB7, !!( nibble & 8 ) );

 delaym();
 digitalWrite( LCD_E, ON );

 delaym();
 digitalWrite( LCD_E, OFF );
}


//----------------------------------------
// Send a byte to the LCD.

void lcd_send_byte( int8_t address, int8_t n )
{
	digitalWrite( LCD_RS, OFF );


if( address )
	digitalWrite( LCD_RS, ON );
else
	digitalWrite( LCD_RS, OFF );
     
 //delay( DELAY_CYCLE );
	delaym();

 digitalWrite( LCD_E, OFF );

lcd_send_nibble( n >> 4 );
//delay( 10 );
	delaym();
lcd_send_nibble( n & 0x0f );
}
//----------------------------

void lcd_init( void )
{
	//delay( 100 );
	int j=0;
	while(j<10){
		delaym();
		j++;
	}


	int8_t i;

	lcd_line = 1;

	digitalWrite( LCD_RS, OFF );

	digitalWrite( LCD_E, OFF );

	// Some LCDs require 15 ms minimum delay after
	// power-up.  Others require 30 ms.  I'm going
	// to set it to 35 ms, so it should work with
	// all of them.
	//delay( 50 );
	j=0;
	while(j<5){
		delaym();
		j++;
	}
	j=0;
	for( i = 0 ;i < 3; i++ )
	{
		lcd_send_nibble( 0x03 );
		//delay( 10 );
		while(j<10){
			delaym();
			j++;
		}
		j=0;
	}

	lcd_send_nibble( 0x02 );
	//delay( 10 );
	j=0;
	while(j<2){
		delaym();
		j++;
	}

	for( i = 0; i < sizeof(LCD_INIT_STRING); i++ )
	{
		lcd_send_byte( 0, LCD_INIT_STRING[ i ] );
	}

}

//----------------------------

void lcd_gotoxy( int8_t x, int8_t y )
{
int8_t address;


switch( y )
  {
   case 1:
     address = LCD_LINE_1_ADDRESS;
     break;

   case 2:
     address = LCD_LINE_2_ADDRESS;
     break;

   case 3:
     address = LCD_LINE_3_ADDRESS;
     break;

   case 4:
     address = LCD_LINE_4_ADDRESS;
     break;

   default:
     address = LCD_LINE_1_ADDRESS;
     break;
     
  }

address += x - 1;
lcd_send_byte( 0, 0x80 | address );
}

//-----------------------------
void lcdWrite( char* c )
{
	uint8_t i;

	for( i = 0; i < strlen( c ) ; i++ ){

		switch( c[ i ] )
		{
		case '\f':
			lcd_send_byte(0,1);
			lcd_line = 1;

			break;

		case '\n':
			lcd_gotoxy( 1, ++lcd_line );

			break;

		case '\b':
			lcd_send_byte( 0,0x10 );

			break;

		default:
			lcd_send_byte( 1,c[ i ] );

			break;
		}
	}
}


/*----------------- INT TO ASCII---------------*/

char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}

/*----------------- FLOAT TO ASCII---------------*/

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



//------------------------------
