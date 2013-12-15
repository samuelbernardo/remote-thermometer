/*
 * Task1.cpp		Tarefa da temperatura do sensor TMP36
 *
 * Created: 10-12-2013 02:48:32
 *  Author: hp
 */ 
#include <pins_arduino.h>
#include <Global.h>
   /*default*/




static int anarf = 1;


// the setup routine runs once when you press reset:
void task1_setup() {                
  // initialize the digital pin as an output.
  LIGHTValueT1=350;
  LIGHTValueT2=700;
 DDRE=0x40;
 DDRD=0x80;
 DDRC=0x40;
 PORTE=0x00;
 PORTD=0x00;
 PORTC=0x00;
 

}
int anlRd(uint8_t pin){
	uint8_t low, high;
	if (pin >= 18) pin -= 18;
	pin = analogPinToChannel(pin);
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
		// set the analog reference (high two bits of ADMUX) and select the
		// channel (low 4 bits).  this also sets ADLAR (left-adjust result)
		// to 0 (the default).
		#if defined(ADMUX)
		ADMUX = ( anarf << 6) | (pin & 0x07);
		#endif
		#if defined(ADCSRA) && defined(ADCL)
		// start the conversion
		(_SFR_BYTE(ADCSRA) |= _BV(ADSC));

		// ADSC is cleared when the conversion finishes
		while (bit_is_set(ADCSRA, ADSC));

		// we have to read ADCL first; doing so locks both ADCL
		// and ADCH until ADCH is read.  reading ADCL second would
		// cause the results of each conversion to be discarded,
		// as ADCL and ADCH would be locked when it completed.
		low  = ADCL;
		high = ADCH;
		#else
		// we dont have an ADC, return 0
		low  = 0;
		high = 0;
		#endif
		return (high << 8)|low;
	
}
// the loop routine runs over and over again forever:
void task1_loop() {
	LIGHTValue= anlRd(0);
	if(LIGHTValue>LIGHTValueT2){
		 PORTE=0x40;
		 PORTD=0x00;
		 PORTC=0x00;
	}else
	if(LIGHTValue>LIGHTValueT1 && LIGHTValue<LIGHTValueT2){
		 PORTE=0x00;
		 PORTD=0x80;
		 PORTC=0x00;
	}else{
		 PORTE=0x00;
		 PORTD=0x00;
		 PORTC=0x40;
	
	}

}
