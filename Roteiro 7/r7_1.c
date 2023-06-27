#include <reg51.h>

#define TC_MODO_0 0x00
#define TC_MODO_1 0x01
#define TC_MODO_2 0x02
#define TC_MODO_3 0x03
#define TC_TMR 0x00
#define TC_CNT 0x04
#define TC_GATE_LOW 0x00
#define TC_GATE_HIGH 0x08

#define SR_MODO_0 0x00
#define SR_MODO_1 0x04
#define SR_MODO_2 0x08
#define SR_MODO_3 0x0C
#define SR_SM2_LOW 0x00
#define SR_SM2_HIGH 0x02
#define SR_REN_LOW 0x00
#define SR_REN_HIGH 0x01

void serial(void); // protótipo de função
unsigned char state = 0;


struct TmodInitStruct { char mode; char cntr_tmr; char gate; } Timer0, Timer1 ;
struct SconInitStruct { char mode; char sm2; char ren; } Serial1 ;

// função para inicializar Timers 0 (modo 1) e 1 (modo 2) como timers
void InitTimerFunction (void) {
	char temp;
	Timer1.mode = TC_MODO_2;
	Timer1.cntr_tmr = TC_TMR;
	Timer1.gate = TC_GATE_LOW;
	temp = (Timer1.mode | Timer1.cntr_tmr | Timer1.gate) << 4;
	Timer0.mode = TC_MODO_1;
	Timer0.cntr_tmr = TC_CNT;
	Timer0.gate = TC_GATE_HIGH;
	TMOD = temp | (Timer0.mode | Timer0.cntr_tmr | Timer0.gate);
}

// função para inicializar Timers 0 (modo 1) e 1 (modo 2) como timers
void InitSerialFunction (void) {
	char temp;
	Serial1.mode = SR_MODO_1;
	Serial1.sm2 = SR_SM2_LOW;
	Serial1.ren = SR_REN_LOW;
	temp = (Serial1.mode | Serial1.sm2 | Serial1.ren) << 4;
	SCON = temp;
}

// OBS: para rodar o hex gerado no Edsim 2.1.20, fazer update freq = 100
void main (void) {
	unsigned char aux = 0x41; 
	
	// inicialização dos Timers 0 e 1 como timers nos modos 1 e 2, respectivamente
	InitTimerFunction();
	InitSerialFunction();
	// estabelece valor de recarga -- inicia contagem do Timer 1
	PCON = 0x80; // smod = 1
	TH1 = 0xFD;
	TR1 = 1;
	ES = 1;
	EA = 1;
	
	while (1) {
		while (state != 1); // aguarda interrupção serial
		state = 0; // indica atendimento interrupcao serial
		ACC = aux++; 
		SBUF = ACC;
		if (aux == 0x61) aux = 0x41;
	} // end of while
} // end of main

void serial(void) interrupt 4 { // especifica tratador de interrupção serial (4)
	if (TI) { // testa se buffer de transmissão vazio
		TI=0; // limpa flag
		state = 1;
	} // end of if
} // end of serial