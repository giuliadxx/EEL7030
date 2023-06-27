#include <reg51.h>
void serial(void); // protótipo de função
unsigned char state = 0;

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador";
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	ponteiro=mensagem;
	
	SCON = 0xC0; // SCON: modo 3, 9-bits
	TMOD = 0x20; // TMOD: timer 1, modo 2
	TH1 = 0xFD; // TH1: valor de recarga para 9600 baud; clk = 11,059 MHz
	TR1 = 1; // TR1: dispara timer
	ES = 1; 
	EA = 1; // habilita interrupcao serial
	
	SBUF = *ponteiro; // envia M
	TB8 = P;
	aux++;
	while (1) {
		while (state != 1); // aguarda interrupção serial
		state = 0; // indica atendimento interrupcao serial
		SBUF = *(ponteiro+aux++);
		TB8 = P;
		if (aux == 16) aux = 0;
	}
}

void serial(void) interrupt 4 { // especifica tratador de interrupção serial (4)
	if (TI) { // testa se buffer de transmissão vazio
		TI=0; // limpa flag
		state = 1;
	} 
} 