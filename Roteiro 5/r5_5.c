#include <reg51.h>
void c51_tmr0 (void);
void c51_tmr1 (void);

unsigned char state = 0;
sbit pino = P2^3;


void main (void) {
	unsigned char code mensagem[]= "Microcontrolador";
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	ponteiro = mensagem;
	
	TMOD = 0x02;
	TH0 = 0x60;
	TL0 = 0x60;

	TH1 = 226;
	TL1 = 0;

	ET0 = 1;
	ET1 = 1;
	EA = 1; // interrupção habilitada
	TR0 = 1 ; // dispara timer
	TR1 =  1;
	
	while (1) {
		while (state != 4);
			state = 0;
			P1 = *(ponteiro+aux++);
			if (aux == 16) aux = 0;
	} // end of while
} //end of main

void c51_tmr0 (void) interrupt 1 {
	state++;
} //end of c51_tmr0

void c51_tmr1 (void) interrupt 3 {
	TH1 = 225;
	pino = ~pino;
}