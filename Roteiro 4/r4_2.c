#include <reg51.h>

void c51_int0 (void);
void c51_int1 (void);

unsigned char state = 0;

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador"; // 0x4D 0x69 0x63 ...
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	
	EX0 = 1;
	IT0 = 1; // interrupção por borda de descida

	EX1 = 1;
	IT1 = 1; // interrupção por borda de descida

	EA = 1; // interrupção habilitada

	ponteiro = mensagem;
	
	while (1) {
		while (state != 1);
		state = 0;
		P1 = *(ponteiro+aux++);
		if (aux == 16) aux = 0;
	} // end of while
} //end of main

void c51_int0 (void) interrupt 0 {
	state++;
} //end of c51_int0

void c51_int1 (void) interrupt 2 {
	EX0 = ~EX0;
	IE0 = 0;
} //end of c51_int1