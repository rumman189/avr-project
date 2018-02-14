#define F_CPU 16000000UL
#define BUAD 19200
#define BUAD_RATE_CALC ((F_CPU/16/BUAD) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

char buffer[3];



void init_adc(){
	DDRB  |= 0xff;
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRA |= (1<<ADEN);
}

void init_usart(){
	//High and low bits
	UBRR0H = (BUAD_RATE_CALC >> 8);
	UBRR0L = BUAD_RATE_CALC;
	////////////////
	//transimit and recieve enable
	UCSR0B = (1 << TXEN0)|  (1 << RXEN0) ;
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
}

int read_adc(int channel){
	ADMUX &= 0xF0;                 
	ADMUX |= channel;                
	ADCSRA |= (1<<ADSC);                
	while ( (ADCSRA &  (1<<ADSC)));
	return ADC;
}

void run_usart(int val){
	itoa(val, buffer, 10);
	for(int i =0; i< 3; i++){
		while(!(UCSR0A&(1<<UDRE0))){};
		UDR0 = buffer[i];
		
	}
	while(!(UCSR0A&(1<<UDRE0))){};
	UDR0 = 13;
	_delay_ms(200);
}

int main(void) {
	init_usart();
	init_adc();
	
	while(1) {
		int adc = read_adc(0);
		
		if (adc > 512){
			PORTB = (1<<PORTB0);
		}
		else{
			PORTB &= ~(1<<PORTB0);
		}
		
		run_usart(adc);
	}
}