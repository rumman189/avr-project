#include <avr/io.h>

#define F_CPU 16000000
#define BUAD 19200
#define BUAD_RATE_CALC ((F_CPU/(16 *BUAD)) - 1)

int main(void){

	char ar[]= "hello";

	//High and low bits
	UBRR0H = (BUAD_RATE_CALC >> 8);
	UBRR0L = BUAD_RATE_CALC;
	////////////////
	//transimit and recieve enable
	UCSR0B = (1 << TXEN0)| (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	////////////////////////////////////////////////////////////////
	int i = 0;

	while (1){

		while (( UCSR0A & (1<<UDRE0))  == 0){};
		for (i = 0; i < strlen(ar); i++){
			UDRE0 = ar[i];
		}
	}
}