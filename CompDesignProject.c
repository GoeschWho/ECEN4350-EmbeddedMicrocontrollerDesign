/* Auth: Megan Bird
 * File: CompDesignProject.c
 * Course: CEEN-4330 – Microprocessor System Design – University of Nebraska-Lincoln
 * Lab: Project
 * Date: 3/14/2017
 * Desc: 8051 program with ROM, RAM, and I/O
 */
 
#include <REGX55.H>
#include <stdio.h>

// P1
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;

// P3
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;

// Keypad
sbit kCol1  = P1^7;
sbit kCol2  = P1^6;
sbit kCol3  = P1^5;
sbit kCol4  = P1^4;
sbit kRow1  = P1^3;
sbit kRow2  = P1^2;
sbit kRow3  = P1^1;
sbit kRow4  = P1^0;
sbit cs_keypad = P3^1;		// latch
sbit oe_keypad = P3^2;

// Seven-Segment Display
sfr sevenSegPort = 0x90;
sbit cs_sevenSeg = P3^0;	// latch

// LCD
sbit cs_lcd = P3^3;				// latch
sbit rs_lcd = P3^4;				// reg select
sbit e_lcd  = P3^5;				// enable
// rw tied to ground to always enable read
sfr lcdPort = 0x90;

// ADC
sbit oe_adc = P3^3;				// latch output enable
sbit wr_adc = P3^4;				// WR line of ADC
sfr adcPort = 0x90;

// RTC
sbit rtc_data0 = P1^0;
sbit rtc_data1 = P1^1;
sbit rtc_data2 = P1^2;
sbit rtc_data3 = P1^3;
sbit rtc_add0 = P1^4;
sbit rtc_add1 = P1^5;
sbit rtc_add2 = P1^6;
sbit rtc_add3 = P1^7;
sfr rtcPort = 0x90;

// Mission Control
enum {ctrl_off,
			ctrl_ss_latch,
			ctrl_kp_oe,
			ctrl_kp_oelatch,
			ctrl_lcd_cmd_start,
			ctrl_lcd_cmd_finish,
			ctrl_lcd_data_start,
			ctrl_lcd_data_finish };

enum {ctrl_adc_start = 1,
			ctrl_rtc_rd,
			ctrl_adc_finish,
			ctrl_rtc_cs1,
			ctrl_rtc_cs0 = 6,
			ctrl_rtc_wr };

sbit dec0 = P3^0;
sbit dec1 = P3^1;		
sbit dec2 = P3^2;
sbit dec3 = P3^3;
sbit dec4 = P3^4;
sbit dec5 = P3^5;

// ======================= prototypes =========================== //

typedef unsigned char byte;

struct keypad_data {
	unsigned char k1;
	unsigned char k2;
	unsigned char k3;
	unsigned char k4;
	unsigned char k5;
	unsigned char k6;
	unsigned char k7;
	unsigned char k8;
	unsigned char k9;
	unsigned char k0;
	unsigned char kA;
	unsigned char kB;
	unsigned char kC;
	unsigned char kD;
	unsigned char kstar;
	unsigned char kpound;
};

struct time_data {
	byte seconds;
	byte minutes;
	byte hours;
	byte days;
	byte months;
	byte years;
	byte week;
};

void latchSevenSeg( void );
void latchKeypad( void );
void outputSevenSeg( char character );
struct keypad_data getKeysPressed( void );
void displayKeyPressed( struct keypad_data keypad );

void lcdCmd( byte cmd );
void lcdData( byte dat );
void lcdInit( void );
void lcdClear( void );
void lcdChar( byte character );
void lcdString( volatile char *string );
void lcdLine( int line );
void lcdHex( byte hex );

float getTemp( void );

void rtcInit( void );
void rtcBusy( void );
void rtcWrite( byte duhdata );
byte rtcRead( byte duhaddress );
void rtcRegWrite( byte duhstuff );
byte rtcRegRead( byte duhstuff );
void rtcSetTime( struct time_data time );
struct time_data rtcGetTime( void );
void rtcPrintTime( struct time_data *time );

void missionControl1( int dec );
void missionControl2( int dec );
void msDelay( unsigned msecs );

// ======================== main ================================ //

void main(void) {
	
	struct keypad_data keypad;
	struct time_data time;

	char string1[] = "Hello world`";
	char string2[] = "M&M's`";
	
	char iStr[] = "-`";
	
	float degF = 0;

	byte i = 0;
	
	missionControl1( ctrl_off );
	missionControl2( ctrl_off );
	
	lcdInit();
	rtcInit();
	
	while (1) {
		
		keypad = getKeysPressed();
		displayKeyPressed( keypad );
		
		lcdLine(1);
		time = rtcGetTime();
		rtcPrintTime( &time );			   

		msDelay(100);
		
	} // end while

	while(1); // Stay off the streets
	
} // end main()

// ======================= functions ============================ //

void latchSevenSeg( void ) {
	
//	cs_sevenSeg = 1;
//	cs_sevenSeg = 0;
	
	missionControl1( ctrl_ss_latch );
	missionControl1( ctrl_off );
	
} // end latchSevenSeg()

// -------------------------------------------------------------- //

void latchKeypad( void ) {
	
//	cs_keypad = 1;
//	cs_keypad = 0;
	
	missionControl1( ctrl_kp_oelatch );
	missionControl1( ctrl_kp_oe );
	
} // end latchKeypad()

// -------------------------------------------------------------- //

//void latchLCD( void ) {
//	
//	cs_lcd = 1;
//	cs_lcd = 0;
//	
//} // end latchLCD()

// -------------------------------------------------------------- //

void outputSevenSeg( char character ) {
	
	switch( character ) {
		case '0': sevenSegPort = ~0x3F; break;
		case '1':	sevenSegPort = ~0x06; break;
		case '2': sevenSegPort = ~0x5B; break;
		case '3': sevenSegPort = ~0x4F; break;
		case '4': sevenSegPort = ~0x66; break;
		case '5': sevenSegPort = ~0x6D; break;
		case '6': sevenSegPort = ~0x7D; break;
		case '7': sevenSegPort = ~0x07; break;
		case '8': sevenSegPort = ~0x7F; break;
		case '9': sevenSegPort = ~0x67; break;
		case 'A': sevenSegPort = ~0x77; break;
		case 'b': sevenSegPort = ~0x7C; break;
		case 'C': sevenSegPort = ~0x39; break;
		case 'd': sevenSegPort = ~0x5E; break;
		case 'E': sevenSegPort = ~0x79; break;
		case 'F': sevenSegPort = ~0x71; break;
		case '-': sevenSegPort = 0xBF; 	break;
		case '.': sevenSegPort = 0x7F;	break;
		case 'o':	sevenSegPort = 0xFF;  break;  // off
		default:  sevenSegPort = 0xAA; 					// invalid
	}
	
	latchSevenSeg();
	
} // end outputSevenSeg()

// -------------------------------------------------------------- //

struct keypad_data getKeysPressed( void ) {
	
	struct keypad_data keypad;
	
	// enable keypad latch output
	//oe_keypad = 0;
	missionControl1( ctrl_kp_oe );
	
	// Set keypad columns as outputs & rows as inputs
	kCol1 = 0;
	kCol2 = 0;
	kCol3 = 0;
	kCol4 = 0;
	kRow1 = 1;
	kRow2 = 1;
	kRow3 = 1;
	kRow4 = 1;
	
	// scan by columns

	// column 1
	kCol1 = 0;
	kCol2 = 1;
	kCol3 = 1;
	kCol4 = 1;
	latchKeypad();
	
	if (kRow1 == 0) {
		keypad.k1 = 1;
	}
	else {
		keypad.k1 = 0;
	}
	if (kRow2 == 0) {
		keypad.k4 = 1;
	}
	else {
		keypad.k4 = 0;
	}
	if (kRow3 == 0) {
		keypad.k7 = 1;
	}
	else {
		keypad.k7 = 0;
	}
	if (kRow4 == 0) {
		keypad.kstar = 1;
	}
	else {
		keypad.kstar = 0;
	}
	kCol1 = 1;
	
	// column 2
	kCol2 = 0;
	latchKeypad();
	
	if (kRow1 == 0) {
		keypad.k2 = 1;
	}
	else {
		keypad.k2 = 0;
	}
	if (kRow2 == 0) {
		keypad.k5 = 1;
	}
	else {
		keypad.k5 = 0;
	}
	if (kRow3 == 0) {
		keypad.k8 = 1;
	}
	else {
		keypad.k8 = 0;
	}
	if (kRow4 == 0) {
		keypad.k0 = 1;
	}
	else {
		keypad.k0 = 0;
	}
	kCol2 = 1;
	
	// column 3
	kCol3 = 0;
	latchKeypad();
	
	if (kRow1 == 0) {
		keypad.k3 = 1;
	}
	else {
		keypad.k3 = 0;
	}
	if (kRow2 == 0) {
		keypad.k6 = 1;
	}
	else {
		keypad.k6 = 0;
	}
	if (kRow3 == 0) {
		keypad.k9 = 1;
	}
	else {
		keypad.k9 = 0;
	}
	if (kRow4 == 0) {
		keypad.kpound = 1;
	}
	else {
		keypad.kpound = 0;
	}
	kCol3 = 1;
	
	// column 4
	kCol4 = 0;
	latchKeypad();
	
	if (kRow1 == 0) {
		keypad.kA = 1;
	}
	else {
		keypad.kA = 0;
	}
	if (kRow2 == 0) {
		keypad.kB = 1;
	}
	else {
		keypad.kB = 0;
	}
	if (kRow3 == 0) {
		keypad.kC = 1;
	}
	else {
		keypad.kC = 0;
	}
	if (kRow4 == 0) {
		keypad.kD = 1;
	}
	else {
		keypad.kD = 0;
	}
	kCol4 = 1;
	latchKeypad();
	
	// disable keypad latch output
	//oe_keypad = 1;
	missionControl1( ctrl_off );
	
	return keypad; 
	
} // end getKeysPressed()

// -------------------------------------------------------------- //

void displayKeyPressed( struct keypad_data keypad ) {
	
	if ( keypad.k1 == 1 ) {
		outputSevenSeg('1');
	}
	else if ( keypad.k2 == 1 ) {
		outputSevenSeg('2');
	}
	else if ( keypad.k3 == 1 ) {
		outputSevenSeg('3');
	}
	else if ( keypad.k4 == 1 ) {
		outputSevenSeg('4');
	}
	else if ( keypad.k5 == 1 ) {
		outputSevenSeg('5');
	}
	else if ( keypad.k6 == 1 ) {
		outputSevenSeg('6');
	}
	else if ( keypad.k7 == 1 ) {
		outputSevenSeg('7');
	}
	else if ( keypad.k8 == 1 ) {
		outputSevenSeg('8');
	}
	else if ( keypad.k9 == 1 ) {
		outputSevenSeg('9');
	}
	else if ( keypad.kA == 1 ) {
		outputSevenSeg('A');
	}
	else if ( keypad.k0 == 1 ) {
		outputSevenSeg('0');
	}
	else if ( keypad.kB == 1 ) {
		outputSevenSeg('b');
	}
	else if ( keypad.kC == 1 ) {
		outputSevenSeg('C');
	}
	else if ( keypad.kD == 1 ) {
		outputSevenSeg('d');
	}
	else if ( keypad.kstar == 1 ) {
		outputSevenSeg('.');
	}
	else if ( keypad.kpound == 1 ) {
		outputSevenSeg('-');
	}
	else {
		outputSevenSeg('o');
	}
	
} // end displayKeyPressed()
	
// -------------------------------------------------------------- //

void lcdCmd( byte cmd ) {
	
	//rs_lcd = 0;			// reg select low for command
	// --- RW tied low for write --- //
	//e_lcd = 1;			// E high for pulse
	
	missionControl1( ctrl_lcd_cmd_start );
	
	lcdPort = cmd;
	//latchLCD();
	
	msDelay(1);			// Need Tpw > 140 ns
	//e_lcd = 0;			// E low to end pulse
	
	missionControl1( ctrl_lcd_cmd_finish );
	
} // end lcdCmd()

// -------------------------------------------------------------- //

void lcdData( byte dat ) {
	
	//rs_lcd = 1;			// reg select high for data
	// --- RW tied low for write --- //
	//e_lcd = 1;			// E high for pulse
	
	missionControl1( ctrl_lcd_data_start );
	
	lcdPort = dat;
	//latchLCD();
	
	msDelay(1);			// Need Tpw > 140 ns
	//e_lcd = 0;			// E low to end pulse
	
	missionControl1( ctrl_lcd_data_finish );
	
} // end lcdData()

// -------------------------------------------------------------- //

void lcdInit( void ) {	
	
	msDelay(50);
	lcdCmd(0x38);			// Function set
	msDelay(5);
	lcdCmd(0x38);			// Function set
	msDelay(1);
	lcdCmd(0x0F);			// Display ON/OFF control
	msDelay(1);
	lcdCmd(0x01);			// Clear display
	msDelay(2);
	
} // end lcdInit()

// -------------------------------------------------------------- //

void lcdClear( void ) {
	
	lcdCmd(0x01);			// Clear display
	msDelay(2);
	
} // end lcdClear()

// -------------------------------------------------------------- //

void lcdChar( byte character ) {
	
	lcdData(character);		// send character
	
} // end lcdChar()

// -------------------------------------------------------------- //

void lcdString( volatile char *string ) {
	
	int i = 0;
	while( string[i] != '`') {
		lcdChar( string[i] );
		i++;
	}
	
} // end lcdString()

// -------------------------------------------------------------- //

void lcdLine( int line ) {
	
	switch (line) {
		case 1: {
			lcdCmd(0x80);
			break;
		}
		case 2: {
			lcdCmd(0xC0);
			break;
		}
		case 3: {
			lcdCmd(0x94);
			break;
		}
		case 4: {
			lcdCmd(0xD4);
			break;
		}
		default:
			lcdCmd(0x80);
		
	} // end switch
	
} // end lcdLine()

// -------------------------------------------------------------- //

void lcdHex( byte hex ) {

	char hexStr[] = "-`";

  	hex += 0x30;
	sprintf( hexStr, "%c`", hex );
	lcdString( &hexStr );

} // end lcdHex()

// -------------------------------------------------------------- //

float getTemp( void ) {
	
	//------------ IDEA ------------------------------------------//
	// change to pass in C or F and returns corresponding value.  //
	
	int i = 0;
	byte sample = 0;
	float voltage = 0;
	float degC = 0;
	float degF = 0;
	int degCint = 0;
//	char tempCStr[] = "+00.0 C`";
//	char tempFStr[] = "+00.0 F`";
//	char voltStr[] = "+0.0 V`";
//	char sampStr[] = "55555555`";
	
		missionControl2( ctrl_adc_start );
		missionControl2( ctrl_adc_finish );
		sample = adcPort;
		missionControl2( ctrl_off );
		
		// voltage reading in 0.3V higher than measured on board
		voltage = sample * 5 / 256;
		//voltage = voltage - 0.25;
		degC = (voltage - 0.5) * 100;
		degF = degC * (9.0/5.0) + 32.0;
		
		return degF;
		
//		sprintf( sampStr, "%c`", sample );
//		sprintf( voltStr, "%+4.1f V`", voltage );
//		sprintf( tempCStr, "%+5.1f C`", degC );
//		sprintf( tempFStr, "%+5.1f F`", degF );
		
//		lcdLine(1);
//		lcdString( &sampStr );
//		lcdLine(2);
//		lcdString( &voltStr );
//		lcdLine(3);
//		lcdString( &tempCStr );
//		lcdLine(4);
//		lcdString( &tempFStr );
	
} // end getDegF()

// -------------------------------------------------------------- //

void rtcInit( void ) {
	
	struct time_data time;
	byte tester;

	time.week = 0;
	time.years = 17;
	time.months = 3;
	time.days = 26;
	time.hours = 12;
	time.minutes = 21;
	time.seconds = 0;
		
	// (A)  Start the counter
	//		 	Inititalize the control registers
	rtcWrite( 0xF4 );		// Set the CF register to 0100b = 4h
	rtcWrite( 0xD4 );		// Set the CD register to 0100b = 4h
	
	// (B)	Check the status of the BUSY bit
	rtcBusy();	
	
	// (C)	STOP and RESET the counter
	rtcWrite( 0xF7 );		// Set the CF register to 0111b = 7h
	
	// Set the current time in the registers
	//		(initizlize the S1 to W registers)
	rtcSetTime( time ); 
	
	// (A)	Start the counter and release the HOLD status
	rtcWrite( 0xF4 );		// Set the CF register to 0100b = 4h
	rtcWrite( 0xD5 );		// Set the CD register to 0101b = 5h

	// debugging
	tester = rtcRead( 0x0D );
	lcdHex( tester );
	
} // end rtcInit()

// -------------------------------------------------------------- //

void rtcBusy( void ) {
	
	byte duhdata;
	
	rtcWrite( 0xD5 );						// Hold bit <- 1
	duhdata = rtcRead( 0x0D );	// Read from D to get BUSY// Read the BUSY bit

	// If BUSY bit = 0, cont., else HOLD bit <- 0
	while( duhdata & 0x02 == 2 ) {
		rtcWrite( 0xD4 );						// HOLD bit <- 0
		rtcWrite( 0xD5 );						// HOLD bit <- 1
		duhdata = rtcRead( 0x0D );	// Read from D to get BUSY// Read the BUSY bit
	}	
	
} // end rtcBusy()

// -------------------------------------------------------------- //

void rtcWrite( byte duhdata ) {
	
	missionControl2( ctrl_rtc_cs1 );	// set CS1 high
	rtcPort = duhdata;					// send duhdata
	missionControl2( ctrl_rtc_cs0 );	// set CS0 low
	missionControl2( ctrl_rtc_wr );		// set WR low
	missionControl2( ctrl_rtc_cs0 );	// set WR high
	missionControl2( ctrl_rtc_cs1 );	// set CS0 high
	missionControl2( ctrl_off );		// set CS1 low
	
} // end rtcWrite()

// -------------------------------------------------------------- //

byte rtcRead( byte duhaddress ) {
	
	byte duhdata = 0x00;
	
	duhaddress = duhaddress << 4;
	duhaddress = duhaddress | 0x0F;
	
	missionControl2( ctrl_rtc_cs1 );	// set CS1 high
	rtcPort = duhaddress;				// send duhaddress
	missionControl2( ctrl_rtc_cs0 );	// set CS0 low
	missionControl2( ctrl_rtc_rd );		// set RD low
	duhdata = rtcPort;					// read duhdata
	duhdata &= 0x0F;					// mask upper nibble of value read in
	missionControl2( ctrl_rtc_cs0 );	// set RD high
	missionControl2( ctrl_rtc_cs1 );	// set CS0 high
	missionControl2( ctrl_off );		// set CS1 low
	
	return duhdata;
	
} // end rtcRead()

// -------------------------------------------------------------- //

void rtcRegWrite( byte duhstuff ) {
	
	rtcBusy();
	rtcWrite( duhstuff );
	// HOLD bit <- 0 by rtcWrite when CS1 is cleared
	
} // end rtcRegWrite()

// -------------------------------------------------------------- //

byte rtcRegRead( byte duhstuff ) {
	
	byte duhdata;

	rtcBusy();
	duhdata = rtcRead( duhstuff );
	// HOLD bit <- 0 by rtcWrite when CS1 is cleared
	return duhdata;
	
} // end rtcRegWrite()

// -------------------------------------------------------------- //

void rtcSetTime( struct time_data time ) {
	
	byte s1, s10, mi1, mi10, h1, h10, d1, d10, mo1, mo10, y1, y10;
	
	// 1-second
	s1 = time.seconds % 10;
	rtcRegWrite( 0x00 | s1 );
	
	// 10-second
	s10 = time.seconds / 10;
	rtcRegWrite( 0x10 | s10 );
	
	// 1-minute
	mi1 = time.minutes % 10;
	rtcRegWrite( 0x20 | mi1 );
	
	// 10-minute
	mi10 = time.minutes / 10;
	rtcRegWrite( 0x30 | mi10 );
	
	// 1-hour
	h1 = time.hours % 10;
	rtcRegWrite( 0x40 | h1 );
	
	// 10-hour
	h10 = time.hours / 10;
	rtcRegWrite( 0x50 | h10 );
	
	// 1-day
	d1 = time.days % 10;
	rtcRegWrite( 0x60 | d1 );
	
	// 10-day
	d10 = time.days / 10;
	rtcRegWrite( 0x70 | d10 );
	
	// 1-month
	mo1 = time.months % 10;
	rtcRegWrite( 0x80 | mo1 );
	
	// 10-month
	mo10 = time.months / 10;
	rtcRegWrite( 0x90 | mo10 );
	
	// 1-year
	y1 = time.years % 10;
	rtcRegWrite( 0xA0 | y1 );
	
	// 10-year
	y10 = time.years / 10;
	rtcRegWrite( 0xB0 | y10 );
	
	// Day of the week
	rtcRegWrite( 0xC0 | time.week );
	
} // end rtcSetTime()

// -------------------------------------------------------------- //

struct time_data rtcGetTime( void ) {
	
	struct time_data time;
	byte s1, s10, mi1, mi10, h1, h10, d1, d10, mo1, mo10, y1, y10, w;
	
	s1 = rtcRegRead( 0x00 );
	s10 = rtcRegRead( 0x01 );
	time.seconds = s1 + ( s10 * 10 );

	mi1 = rtcRegRead( 0x02 );
	mi10 = rtcRegRead( 0x03 );
	time.minutes = mi1 + ( mi10 * 10 );

	h1 = rtcRegRead( 0x04 );
	h10 = rtcRegRead( 0x05 );
	time.hours = h1 + ( h10 * 10 );

	d1 = rtcRegRead( 0x06 );
	d10 = rtcRegRead( 0x07 );
	time.days = d1 + ( d10 * 10 );

	mo1 = rtcRegRead( 0x08 );
	mo10 = rtcRegRead( 0x09 );
	time.months = mo1 + ( mo10 * 10 );

	y1 = rtcRegRead( 0x0A );
	y10 = rtcRegRead( 0x0B );
	time.years = y1 + ( y10 * 10 );

	w = rtcRegRead( 0x0C );
	time.week = w;

	return time;
	
} // end rtcSetTime()

// -------------------------------------------------------------- //

void rtcPrintTime( struct time_data *time ) {

	char timeStr[] = "0 00/00/00 00:00:00`";

	sprintf( timeStr, "%d %02d/%02d/%02d %02d:%02d:%02d`", 
			(int)time->week, 
			(int)time->months, (int)time->days, (int)time->years, 
			(int)time->hours, (int)time->minutes, (int)time->seconds );
	lcdString( &timeStr );

} // end rtcPrintTime()

// -------------------------------------------------------------- //

void missionControl1( int dec ) {
	
	switch ( dec ) {
		
		// The MSB is changed first to avoid false triggers of the LCD enable
		// line as the enable line never goes high when the MSB is low.
		case ctrl_off: {
			dec2 = 0;
			dec1 = 0;
			dec0 = 0;
			break;
		}
		case ctrl_ss_latch: {
			dec2 = 0;
			dec1 = 0;
			dec0 = 1;
			break;
		}
		case ctrl_kp_oe: {
			dec2 = 0;
			dec1 = 1;
			dec0 = 0;
			break;
		}
		case ctrl_kp_oelatch: {
			dec2 = 0;
			dec1 = 1;
			dec0 = 1;
			break;
		}
		case ctrl_lcd_cmd_start: {
			dec2 = 1;
			dec1 = 0;
			dec0 = 0;
			break;
		}
		case ctrl_lcd_cmd_finish: {
			dec2 = 1;
			dec1 = 0;
			dec0 = 1;
			break;
		}
		case ctrl_lcd_data_start: {
			dec2 = 1;
			dec1 = 1;
			dec0 = 0;
			break;
		}
		case ctrl_lcd_data_finish: {
			dec2 = 1;
			dec1 = 1;
			dec0 = 1;
			break;
		}		
	} // end switch
	
} // end missionControl1()

// -------------------------------------------------------------- //

void missionControl2( int dec ) {
	
	switch ( dec ) {
		case ctrl_off: {
			dec4 = 0;
			dec3 = 0;
			dec5 = 0;
			break;
		}
		case ctrl_adc_start: {
			dec4 = 0;
			dec3 = 1;
			dec5 = 0;
			break;
		}
		case ctrl_rtc_rd: {
			dec4 = 1;
			dec3 = 0;
			dec5 = 0;
			break;
		}
		case ctrl_adc_finish: {
			dec4 = 1;
			dec3 = 1;
			dec5 = 0;
			break;
		}
		case ctrl_rtc_cs1: {
			dec4 = 0;
			dec3 = 0;
			dec5 = 1;
			break;
		}
		// not used
//		case ctrl_rtc_cs0: {
//			dec5 = 1;
//			dec4 = 0;
//			dec3 = 1;
//			break;
//		}
		case ctrl_rtc_cs0: {
			dec4 = 1;
			dec3 = 0;
			dec5 = 1;
			break;
		}
		case ctrl_rtc_wr: {
			dec4 = 1;
			dec3 = 1;
			dec5 = 1;
			break;
		}		
	} // end switch
	
} // end missionControl2()

// -------------------------------------------------------------- //

void msDelay( unsigned msecs ) {
	
	unsigned i;
	unsigned char j;
	
	msecs = msecs * 3.23;
	
	for(i=0;i<msecs;i++){
		for(j=0;j<100;j++);
	}
	
} // end msDelay()

// -------------------------------------------------------------- //

