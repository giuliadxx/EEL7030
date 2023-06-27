// diretiva de compila��o
#include <reg51.h> // inclus�o de arquivo com endere�os de registradores do 8051

// declara��o dos prot�tipos de fun��es
unsigned char converte_7seg (unsigned char);
unsigned char converte_chave (unsigned char);

// declara��o de constantes
#define CS 0x80;

// declara��o de vari�veis globais
unsigned char dsp_0 = 0xE7; // 11100111 B

// fun��o main
void main (void)
{
	short delay;
	unsigned char switchs;
	P0 = CS;
	P3 = dsp_0;
	
	while(1){
		switchs = ~P2; 																	// switchs armazena P2 (porta q le o valor das chaves). ex: se todas est�o fechadas
																										// seria lido 0b00000000 e se apenas a menos sign. fechada seria ob11111110
																										// entao esses valores do exemplo seriam agora o valor que temos na variavel switchs
																										// porem, estou negando a variavel para que, se fosse o segundo exemplo, tenhamos 0b00000001
		switchs = switchs & 0x0F;												// estou pegando os digitos mais significativos da leitura de P2 e mascarando
																										// se temos x x x x x x x x em P2
																										// com &    0 0 0 0 1 1 1 1
																										// ficamos  0 0 0 0 x x x x porque tanto faz E 0 d� zero, enquanto tanto faz E 1 d� tanto faz
		P1 = converte_7seg(switchs);  									// aqui, pegamos o valor agora modificado de switchs e colocamos na porta p1, que diz QUAIS CARACTERES mostrar
		for (delay = 0; delay < 15000; delay++);
	}
}

// fun��o converte_7seg
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
