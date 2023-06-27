#include <reg51.h>
void c51_tmr0 (void);
void c51_int1 (void);
unsigned char state0 = 0;
unsigned char state1 = 0;
unsigned char dado;

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador";
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	ponteiro = mensagem;
	
	TMOD = 0x02;
	TH0 = 0x60;
	TL0 = 0x60;
	EX1 = 1;
	IT1 = 1;
	ET0 = 1;
	EA = 1; // interrupção habilitada
	TR0 = 1 ; // dispara timer
	
	while (1) {
		while (state0 == 1){
			state0 = 0;
			dado = P2;
		}
		while(state1 == 1){
			state1 = 0;
			P1 = *(ponteiro+aux++);
			if (aux == 16) aux = 0;
		}
	} // end of while
} //end of main

void c51_tmr0 (void) interrupt 1 {
	state1++;
	TH0 = dado;
} //end of c51_tmr0

void c51_int1 (void) interrupt 2 {
	state0++;
}