#include <reg51.h>
void serial(void); // protótipo de função
unsigned char state = 0;

void main (void) {
	unsigned char data mensagem[5];
	unsigned char data *ponteiro;
	unsigned char aux = 0;
	ponteiro = mensagem;
	
	SCON = 0x50; // SCON: modo 1, 8-bits, REN = 1 (receber dados)
	TMOD |= 0x20; // TMOD: timer 1, modo 2
	TH1 = 0xFD; // TH1: valor de recarga para 9600 baud; clk = 11,059 MHz
	TR1 = 1; // TR1: dispara timer
	ES = 1; 
	EA = 1; // habilita interrupcao serial
	
	SBUF = P3^0;
	
	while (1) {
		while (state != 1); // aguarda interrupção serial
		state = 0; // indica atendimento interrupcao serial
	     *(ponteiro+aux++)= SBUF; 
		if (aux == 5) aux = 0;
	}
}

void serial(void) interrupt 4 { // especifica tratador de interrupção serial (4)
	if (RI) { // 
		RI=0; // limpa flag
		state = 1;
	} 
} 