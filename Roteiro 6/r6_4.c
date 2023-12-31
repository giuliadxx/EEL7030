#include <reg51.h>

void serial(void); // protótipo de função

unsigned char state = 0;
unsigned char statedata = 0;


void main (void) {

	unsigned char aux = 0x43; // 0100 0011B
	unsigned char auxdata = 0;
	unsigned char data mensagem[5];
	unsigned char data *ponteiro;
	ponteiro = mensagem;

	SCON = 0xD0; // 1101 0000B -- SCON: modo 3, 9-bits
	PCON = 0x80; // 1000 0000B => SMOD = 1
	TMOD = 0x20; // 0010 0000B => TMOD: timer 1, modo 2
	TH1 = 0xFF; // TH1: valor de recarga para 62500 baud; clk = 12 MHz
	TR1 = 1; // TR1: dispara timer
	ES = 1;
	EA = 1; // habilita interrupcao serial
	ACC = aux++; 
	TB8 = P;
	SBUF = ACC;

	while (1) {
		if (state == 1){ // aguarda interrupção serial
			state = 0; // indica atendimento interrupcao serial
			ACC = aux++; 
			TB8 = P;
			SBUF = ACC;
			if (aux == 0x62) aux = 0x43; 
		}
		if (statedata == 1){
			statedata = 0;
			SBUF = P3^0;
			*(ponteiro+auxdata++)= SBUF; 
			if (auxdata == 5) aux = 0;
		}
	} // end of while
} // end of main
						
void serial(void) interrupt 4 { // especifica tratador de interrupção serial (4)
	if (TI) { // testa se buffer de transmissão vazio
		TI=0; // limpa flag
		state = 1;
	} // end of if
				
	if (RI) { 
		RI=0; // limpa flag
		statedata = 1;
	} // end of if
} // end of serial