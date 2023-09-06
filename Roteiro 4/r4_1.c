#include <reg51.h>

void c51_int0 (void);
unsigned char state = 0;

void main (void) {

	unsigned char aux = 0; // utilizar unsigned char pois sao 8 bits, conta ate FFh, da overflow, e volta a 0
	unsigned short x;
	
	EX0 = 1;
	IT0 = 1; // interrupção por borda de descida

	EA = 1; // interrupção habilitada
	
	while (1) { 
		while(state);
		P1=aux++;
		for(x=0; x < 15000; x++);	
	} // end of while
} //end of main


void c51_int0 (void) interrupt 0 {
	state=state^0x01;
} //end of c51_int0

