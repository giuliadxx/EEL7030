#pragma SMALL
#include <reg51.h>

#define CMD 0 // 0000 0000 B -- objetiva fazer RS (P1.3) = 0
#define DADO 8 // 0000 1000 B -- objetiva fazer RS (P1.3) = 1

void write2nibbles(unsigned char, unsigned char); // função p/envio dados/cmds p/display
void writeinit(unsigned char *, unsigned char);
void initdsp (void); // função que inicializa o display

sbit CS = P0^7; // variável global
sbit EN = P1^2; // variável global

unsigned char chaves;
unsigned char i;
unsigned char code cadeia[]={"Valor: $"};
unsigned char code init[]={0x28,0x0f,0x06	,'$'}; // vetor de inicializacao do display
unsigned char code cursor[]={0x87}; // 1000 0111 b

// -- function set - display on/off - entry mode
void main (void)
{
	CS=0; // inibe displays de 7 segmentos
	initdsp(); // chama rotina de inicializacao dos display
	
	while (1){
		writeinit (cadeia,DADO);
		chaves = ~P2;
		chaves = chaves & 0x0F;	
		chaves = chaves + 0x30;
		writeinit(cursor, CMD);
		write2nibbles (chaves,DADO); // envia caracteres a serem mostrados no display
		for (i=0;i<255;i++);
	}
}

// Funcao para inicializar o display
void initdsp(void)
{
unsigned char x;
	P1=0x20; // informa ao HD44780 sobre barramento de 4 trilhas
	EN=1;
	EN=0;
	for (x=0; x<50; x++); // introduz atraso -- melhor usar timer
	//writeinit(init,CMD); // envia demais bytes de inicializacao
}


void write2nibbles(unsigned char dados, unsigned char RS)
{
unsigned char x, temp1;
		P1 = (dados & 0xf0)|RS; // AND 1111 0000 OR 0000 X000
		EN=1;
		EN=0;
		P1 = (dados << 4)|RS; // XXXX 0000 OR 0000 X000
		EN=1;
		EN=0;
		for (x=0; x<50; x++); // introduz atraso -- melhor usar timer
} // end of write2nibbles

void writeinit(unsigned char *dados, unsigned char RS)
{
unsigned char x, temp1;
	while (*dados!= '$') {
		temp1 = *dados++; // desloca byte apontado pelo ponteiro
		P1 = (temp1 & 0xf0)|RS; // AND 1111 0000 OR 0000 X000
		EN=1;
		EN=0;
		P1 = (temp1 << 4)|RS; // XXXX 0000 OR 0000 X000
		EN=1;
		EN=0;
		for (x=0; x<50; x++); // introduz atraso -- melhor usar timer
		} // end of while
}