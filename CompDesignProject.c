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

// ======================= prototypes =========================== //

typedef unsigned char byte;

void latchSevenSeg();
void outputSevenSeg( char character );
void msDelay( unsigned );

// ======================== main ================================ //

void main(void) {
	
	while (1) {

		outputSevenSeg('0');
		msDelay(2000);
		
		outputSevenSeg('1');
		msDelay(2000);
		
		outputSevenSeg('2');
		msDelay(2000);
		
		outputSevenSeg('3');
		msDelay(2000);
		
		outputSevenSeg('4');
		msDelay(2000);
		
		outputSevenSeg('5');
		msDelay(2000);
		
		outputSevenSeg('6');
		msDelay(2000);
		
		outputSevenSeg('7');
		msDelay(2000);
		
		outputSevenSeg('8');
		msDelay(2000);
		
		outputSevenSeg('9');
		msDelay(2000);
		
		outputSevenSeg('A');
		msDelay(2000);
		
		outputSevenSeg('b');
		msDelay(2000);
		
		outputSevenSeg('C');
		msDelay(2000);
		
		outputSevenSeg('d');
		msDelay(2000);
		
		outputSevenSeg('E');
		msDelay(2000);
		
		outputSevenSeg('F');
		msDelay(2000);
		
		outputSevenSeg('-');
		msDelay(2000);
		
		outputSevenSeg('o');
		msDelay(2000);
	}
	
	while(1); // Stay off the streets
	
} // end main()

// ======================= functions ============================ //

void latchSevenSeg( void ) {
	
	P3_0 = 1;
	P3_0 = 0;
	
} // end latchSevenSeg()

// -------------------------------------------------------------- //

void outputSevenSeg( char character ) {
	
	switch( character ) {
		case '0': P1 = ~0x3F; break;
		case '1':	P1 = ~0x06; break;
		case '2': P1 = ~0x5B; break;
		case '3': P1 = ~0x4F; break;
		case '4': P1 = ~0x66; break;
		case '5': P1 = ~0x6D; break;
		case '6': P1 = ~0x7D; break;
		case '7': P1 = ~0x07; break;
		case '8': P1 = ~0x7F; break;
		case '9': P1 = ~0x67; break;
		case 'A': P1 = ~0x77; break;
		case 'b': P1 = ~0x7C; break;
		case 'C': P1 = ~0x39; break;
		case 'd': P1 = ~0x5E; break;
		case 'E': P1 = ~0x79; break;
		case 'F': P1 = ~0x71; break;
		case '-': P1 = 0xBF; 	break;
		case 'o':	P1 = 0xFF;  break;  // off
		default:  P1 = 0xAA; 					// invalid
	}
	
	latchSevenSeg();
	
} // end outputSevenSeg()

// -------------------------------------------------------------- //

void msDelay( unsigned msecs ) {
	
	unsigned i;
	unsigned char j;
	
	for(i=0;i<msecs;i++){
		for(j=0;j<100;j++);
	}
	
} // end msDelay()