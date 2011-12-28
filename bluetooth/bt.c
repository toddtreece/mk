#define F_CPU 16000000UL
#define RX_STARVE 20
#define KEY_REFRESH_RATE 15

#include <inttypes.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile uint8_t scan_keypads;

ISR(TIMER0_COMPA_vect) {
  scan_keypads = 1;
  TCNT0 = 0;
}

void USARTInit(uint16_t ubrr_value) {

  //Set Baud rate
  UBRRL = ubrr_value;
  UBRRH = (ubrr_value>>8);

  UCSRC=(1<<USBS)|(3<<UCSZ0);
  UCSRB=(1<<RXEN)|(1<<TXEN);

}

void main() {

  // 115200 baud
  USARTInit(8);

  uint8_t starve;

  DDRB = 0;
  PORTB = 0;

  // keypad timer init
  TCCR0B |= (1<<CS02) | (1<<CS00);
  TIMSK |= (1 << OCIE0A);
  OCR0A = KEY_REFRESH_RATE;

  sei();

  while(1) {

    starve = 0;

    //output
    PORTB = 0;
    DDRB = 0xFF;

    while((UCSRA & (1<<RXC)) && starve < RX_STARVE) {
      starve++;

      PORTB = UDR;
    }

    if(scan_keypads) {

      scan_keypads = 0;

      //input
      PORTB = 0;
      DDRB = 0;

      _delay_us(1);

      //wait until ready to send
      while(!(UCSRA & (1<<UDRE))) {}

      UDR = PORTB;
    }

  }

  return;

}



