// diretiva de compila��o
#include <reg51.h>

// declara��o de constantes
#define CS 0x00;

// declara��o de vari�veis globais
unsigned char led = 0x80; // 1000 0000 B
unsigned char i;

// fun��o main
void main (void)
{
	
	P0 = CS;
	
	while(1) {
						
		while (led != 0xFF){ 
			led >>= 1;
			led |= 0x80;
			P1 = ~led;
		}
		
		while (led != 0x00){
			led <<= 1;
			P1 = ~led;
		}
		
		}
}