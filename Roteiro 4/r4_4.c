#include <reg51.h>

void c51_int0 (void);
void c51_int1 (void);

unsigned char state0 = 0;
unsigned char state1 = 0;

void main (void) {

	unsigned char aux = 0xFE;
	
	EX0 = 1;
	IT0 = 1; // interrupção por borda de descida
	EX1 = 1;
	IT1 = 1;
	EA = 1; // interrupção habilitada
															
	while (1) {
		if (state0) {
			state0 = 0;																																																										
			if (state1 == 0) {
				aux <<=1;
				aux |= 0x01;
				if (aux == 0xFF) aux = 0xFE;
			}
			else {
				aux >>=1;
				aux |= 0x80;
				if (aux == 0xFF) aux = 0x7F;
			}
			P1 = aux;																																				
		} // end of if state 0
	} // end of while
} //end of main

void c51_int0 (void) interrupt 0 {
	state0++;
} //end of c51_int0

void c51_int1 (void) interrupt 2 {
	state1^=0x01;
} //end of c51_int1