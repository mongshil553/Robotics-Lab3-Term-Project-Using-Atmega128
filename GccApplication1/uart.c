﻿#include <avr/io.h>
#include "uart.h"

#define UBRR 103

void UART_init(){
	UBRR0L = (unsigned char)UBRR;
	UBRR0H = (unsigned char)(UBRR >> 8);

	
	UCSR0A = 0x00; //비동기 1배속
	UCSR0B = 0x18; //송수신 허가
	//UCSR0B = (1<<RXCIE0)|(1<<TXCIE0)|(1<<RXEN0)|(1<<TXEN0); //recv complete interrupt enable
	UCSR0C = 0x87; //비동기, non-parity mode, stop bit:1 bit, data: 8bit
}

void USART0_TX_vect(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char USART0_RX(void){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void USART0_sNUM(long nNum){
	USART0_TX_vect((nNum%10000) / 1000 + 48);
	USART0_TX_vect((nNum%1000) / 100 + 48);
	USART0_TX_vect((nNum%100) / 10 + 48);
	USART0_TX_vect((nNum%10) + 48);
}

void USART0_NUM(long nNum){
	if(nNum >= 0){
		USART0_TX_vect(' ');
		USART0_sNUM(nNum/10000);
		USART0_sNUM(nNum%10000);
	}
	else{
		USART0_TX_vect('-');
		USART0_sNUM((-1)*nNum/10000);
		USART0_sNUM((-1)*nNum%10000);
	}
	USART0_ln();
}
inline void USART0_ln(){
	USART0_TX_vect('\n');
	USART0_TX_vect('\r');
}

