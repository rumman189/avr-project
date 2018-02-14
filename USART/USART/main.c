 #include <avr/io.h>
 #define F_CPU 16000000
 #define BUAD 19200
 #define BUAD_RATE_CALC ((F_CPU/16/BUAD) - 1)

 int main(void){
	 
	 char buffer [3];
	 //High and low bits
	 UBRR0H = (BUAD_RATE_CALC >> 8);
	 UBRR0L = BUAD_RATE_CALC;
	 ////////////////
	 //transimit and recieve enable
	 UCSR0B = (1 << TXEN0)| (1 << RXEN0);
	 UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	 ////////////////////////////////////////////////////////////////
	 int i = 0;
	 int counter = 0;
	 DDRB =0xff;
	 while (1){
		 send_usart( counter);
		 rcv_usart();
		 counter++;
		 if(counter == 100){
			return 0;
		 } 
		 
	 }
 }
 
 void send_usart( unsigned char data )
 {
	 while (( UCSR0A & (1<<UDRE0))  == 0){};
	 UDR0 = data;
 }
 
 void rcv_usart()
 {
	 while (!(UCSR0A & (1<<RXC0)) ){};
	 PORTB = UDR0;
 }