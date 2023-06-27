// Rotinas para a escrita de mensagem no display do Edsim51 em C
// Para gerar arquivo com a extensão HEX ir em OPTIONS FOR TARGET1/OUTPUT
// modelo de memória no KEIL: SMALL !!!!!! (OPTIONS FOR TARGET1/TARGET)

#pragma SMALL
#include <reg51.h>

#define CMD 0 // 0000 0000 B -- objetiva fazer RS (P1.3) = 0
#define DADO 8 // 0000 1000 B -- objetiva fazer RS (P1.3) = 1

void write2nibbles(unsigned char *, unsigned char); // função p/envio dados/cmds p/display

void initdsp (void); // função que inicializa o display

sbit CS = P0^7; // variável global
sbit EN = P1^2; // variável global

unsigned char code cadeia[]="teste$"; // array contendo mensagem
unsigned char code init[]={0x28,0x0f,0x06,'$'}; // vetor de inicializacao do display

// -- function set - display on/off - entry mode
void main (void)
{
CS=0; // inibe displays de 7 segmentos
initdsp(); // chama rotina de inicializacao dos display
write2nibbles (cadeia,DADO); // envia caracteres a serem mostrados no display
while(1); // necessario para congelar o 8051
}

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
} // end of write2nibbles