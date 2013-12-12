/*
 * Task1.cpp		Tarefa da temperatura do sensor TMP36
 *
 * Created: 10-12-2013 02:48:32
 *  Author: hp
 */ 
#include <pins_arduino.h>
#include <Global.h>
   /*default*/







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
// the loop routine runs over and over again forever:
void task1_loop() {
	LIGHTValue= anlRd(0);
	if(LIGHTValue>LIGHTValueT2){
		 PORTE=0x40;
		 PORTD=PORTD & 0x7F;
		 PORTC=0x00;
	}else
	if(LIGHTValue>LIGHTValueT1 && LIGHTValue<LIGHTValueT2){
		 PORTE=0x00;
		 PORTD=PORTD | 0x80;
		 PORTC=0x00;
	}else
	if(LIGHTValue<LIGHTValueT1){
		 PORTE=0x00;
		 PORTD=PORTD & 0x7F;
		 PORTC=0x40;
	
	}
		
		
		

}