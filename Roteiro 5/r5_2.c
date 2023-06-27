#include <reg51.h>
void c51_tmr1 (void);
unsigned char state = 0;

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador";
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	ponteiro = mensagem;
	
	TMOD = 0x00;
	TH1 = 236; // 256 - 20 (640/32)
	TL1 = 0;
	ET1 = 1;
	EA = 1; // interrupção habilitada
	TR1 = 1 ; // dispara timer
	
	while (1) {
		while (state != 1);
			state = 0;
			P1 = *(ponteiro+aux++);
			if (aux == 16) aux = 0;
	} // end of while
} //end of main

void c51_tmr1 (void) interrupt 3 {
	TH1 = 236;
	TL1 = 0;
	state++;
} //end of c51_tmr0