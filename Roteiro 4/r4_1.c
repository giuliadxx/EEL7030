#include <reg51.h>

void c51_int0 (void);
void delay(void);
unsigned char state = 0;

void main (void) {
	unsigned char aux = 0;
	
	EX0 = 1;
	EA = 1; // interrupção habilitada
	IT0 = 1; // interrupção por borda de descida

	while (1) {
		while(state);
		P1 = aux++;
		if (aux == 16) aux = 0;
		delay();
		} 
	}

void c51_int0 (void) interrupt 0 {
	state = state^0x01;
} //end of c51_int0

void delay(void) {
   int i, j;
   
   for (i = 0; i < 15000; i++) { // Loop externo para gerar o atraso
      for (j = 0; j < 10; j++) { // Loop interno para ajustar o tempo
         // Não faz nada
      }
   }
}