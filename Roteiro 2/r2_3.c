// diretiva de compilação
#include <reg51.h> // inclusão de arquivo com endereços de registradores do 8051

// declaração dos protótipos de funções
unsigned char converte_7seg (unsigned char);

// declaração de constantes
#define CS 0x80;

// declaração de variáveis globais
unsigned char dsp_0 = 0xE7; // 11100111b
unsigned char dsp_1 = 0xEF; // 11101111b

// função main
void main (void)
{
	short delay;
	unsigned char numero;
	unsigned char contador;
	unsigned char switchs;
	P0 = CS;
	P3 = dsp_1;
	
	while(1){
		switchs = ~P2;
		while (switchs != 0)
    {
        if ((switchs & 1) == 1) contador++;
        switchs = switchs >> 1;
    }
		P1 = converte_7seg(contador);
		contador = 0;
		for (delay = 0; delay < 255; delay++);
	}
}

// função converte_7seg
// retorna valor a ser enviado aos displays para formar o caractere
unsigned char converte_7seg (unsigned char dado)
{
switch (dado) // GFEDCBA
{ case 0: dado = 0x40; break; // "1000000";
	case 1: dado = 0x79; break; // "1111001";
	case 2: dado = 0x24; break; // "0100100";
	case 3: dado = 0x30; break; // "0110000";
	case 4: dado = 0x19; break; // "0011001";
	case 5: dado = 0x12; break; // "0010010";
	case 6: dado = 0x02; break; // "0000010";
	case 7: dado = 0x78; break; // "1111000";
	case 8: dado = 0x00; break; // "0000000";
	case 9: dado = 0x10; break; // "0010000";
	case 10: dado = 0x08; break; // "0001000";
	case 11: dado = 0x03; break; // "0000011";
	case 12: dado = 0x46; break; // "1000110";
	case 13: dado = 0x21; break; // "0100001";
	case 14: dado = 0x06; break; // "0000110";
	case 15: dado = 0x0E; break; // "0001110";
	default: dado = 0x80; // "0000000";
}
return dado;
} // end converte_7seg
