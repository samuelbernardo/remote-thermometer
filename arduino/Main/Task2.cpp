/*
 * Task2.cpp	Tarefa de sensor de luminosidade
 *
 * Created: 10-12-2013 02:48:32
 *  Author: hp
 */ 
#include <pins_arduino.h>
#include <Global.h>
#include "HardwareSerial.h"




static float auxiliarVoltage;

// the setup routine runs once when you press reset:
void task2_setup() {                
  // initialize the digital pin as an output.
  
  TMP36ValueT1=16.0;
  

  DDRD= DDRD | 0x10;
  
  PORTD= PORTD | 0x10;


}

// the loop routine runs over and over again forever:
void task2_loop() {

	auxiliarVoltage=anlRd(1);

	//auxiliarVoltage/=1024.0;
	TMP36Value = auxiliarVoltage/10;//  * 1000/10000;


	if (TMP36Value>= TMP36ValueT1){
		PORTD= PORTD|0x10;
		
	}else{
		PORTD=PORTD & 0xEF;
		
	}
	
	

}
