// diretiva de compila��o
#include <reg51.h> // inclus�o de arquivo com endere�os de registradores do 8051

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
						
	if (led != 0x01) led = led >> 1;
	else led = 0x80;

	P1 = ~led;
	
	for(i=0;i<275;i++);
	
	}
}