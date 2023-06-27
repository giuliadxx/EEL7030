#include <reg51.h>

void c51_int0 (void);
unsigned char state = 0;

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador"; // 0x4D 0x69 0x63 ...
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	EX0 = 1;
	EA = 1; // interrupção habilitada
	IT0 = 1; // interrupção por borda de descida
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