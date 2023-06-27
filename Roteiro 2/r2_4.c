// diretiva de compilação
#include <reg51.h> // inclusão de arquivo com endereços de registradores do 8051

// declaração de constantes
#define CS 0x00;

void delay(int value)
{
	int i,j;
	for(i=0; i<=value; i++)
	for(j=0; j<=5; j++);
}

// função main
void main (void)
{
	P0 = CS;
	
	while(1){	
			P1=0x80;delay(2500);P1=0x40;delay(2500);P1=0x20;delay(2500);
			P1=0x10;delay(2500);P1=0x08;delay(2500);P1=0x04;delay(2500);
			P1=0x02;delay(2500);P1=0x01;delay(2500);P1=0x01;delay(2500);
			P1=0x02;delay(2500);P1=0x04;delay(2500);P1=0x08;delay(2500);
			P1=0x10;delay(2500);P1=0x20;delay(2500);P1=0x40;delay(2500);
			P1=0x80;delay(1000);
		}
}
