// diretivas de compilação

#pragma SMALL
#include <reg51.h>

// declaração dos protótipos de funções

void write2nibbles(unsigned char *, unsigned char); // função p/envio dados/cmds p/display
void write1byte(unsigned char, unsigned char);
void initdsp (void); // função que inicializa o display

// declaração de constantes

#define CMD 0 // 0000 0000 B -- objetiva fazer RS (P1.3) = 0
#define DADO 8 // 0000 1000 B -- objetiva fazer RS (P1.3) = 1
#define COL_7 0x87 // 1000 0111 B   -- comando para posicionar cursor na coluna 07H


// declaração de variáveis globais

sbit CS = P0^7; // variável global
sbit EN = P1^2; // variável global

unsigned char code cadeia[]="Valor: $"; // array contendo mensagem
unsigned char code init[]={0x28,0x0C,0x06,'$'}; // vetor de inicializacao do display -- function set - display on/off - entry mode
unsigned char lcd_code[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46};

// função main
void main (void)
{
	
	unsigned char dado_lido,temp;
		
	CS=0; // inibe displays de 7 segmentos
	initdsp(); // chama rotina de inicializacao dos display
	write2nibbles (cadeia,DADO); // envia caracteres a serem mostrados no display

	while(1) {
		
		dado_lido = ~P2;

		temp = dado_lido >> 4;
		write1byte(lcd_code[temp],DADO);

		temp = dado_lido & 0x0f;
		write1byte(lcd_code[temp],DADO);

		write1byte(COL_7,CMD);

	 }  // end of while
		
}  // end of main

// Funcao para inicializar o display
void initdsp(void)
{
	unsigned char x;
	P1=0x20; // informa ao HD44780 sobre barramento de 4 trilhas
	EN=1;
	EN=0;
	for (x=0; x<50; x++); // introduz atraso -- melhor usar timer
	write2nibbles(init,CMD); // envia demais bytes de inicializacao
}

// Funcao para escrever conjunto de caracteres ou comandos no display ;
// dado (RS=1); comando (RS=0);
void write2nibbles(unsigned char *dados, unsigned char RS)
{
	unsigned char temp1;
	while (*dados!= '$') {
		temp1 = *dados++; // desloca byte apontado pelo ponteiro

		write1byte(temp1,RS);
	} // end of while
} // end of write2nibbles

// função para escrever 1 byte de comando/dado
void write1byte(unsigned char temp1, unsigned char RS)
{
	unsigned char x;
		
	P1 = (temp1 & 0xf0)|RS; // AND 1111 0000 OR 0000 X000
	EN=1;
	EN=0;
	P1 = (temp1 << 4)|RS; // XXXX 0000 OR 0000 X000
	EN=1;
	EN=0;
	for (x=0; x<50; x++); // introduz atraso -- melhor usar timer

} // end of write1word