// diretiva de compila��o
#include <reg51.h> // inclus�o de arquivo com endere�os de registradores do 8051

// declara��o de constantes
#define CS 0x00;

void delay(int value)
{
	int i,j;
	for(i=0; i<=value; i++)
	for(j=0; j<=5; j++);
}

// fun��o main
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
