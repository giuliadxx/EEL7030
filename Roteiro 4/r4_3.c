#include <reg51.h>

void c51_int0 (void);
void c51_int1 (void);
void delay(void);

unsigned char state0 = 0;
unsigned char state1 = 0;
unsigned char xdata dados[8];

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador"; // 0x4D 0x69 0x63 ...
	unsigned char code *ponteiro;
	unsigned char i = 0;
	unsigned char j = 0;
	
	EX0 = 1;
	IT0 = 1; // interrupção por borda de descida
	EX1 = 1;
	IT1 = 1;
	EA = 1; // interrupção habilitada
	ponteiro = mensagem;
	
	while (1) {
		if (state0 == 1){
			state0 = 0;
			P1 = *(ponteiro+i++);
			if (i == 16) i = 0;
		}
		if (state1 == 1){
			state1 = 0;
			dados[j++] = P1;
			if (j == 8) j = 0;
		}
		} // end of while
	} //end of main

void c51_int0 (void) interrupt 0 {
	state0++;
} //end of c51_int0

void c51_int1 (void) interrupt 2 {
	state1++;
} //end of c51_int1

void delay(void) {
   int i, j;
   
   for (i = 0; i < 15000; i++) { // Loop externo para gerar o atraso
      for (j = 0; j < 10; j++) { // Loop interno para ajustar o tempo
         // Não faz nada
      }
   }
}