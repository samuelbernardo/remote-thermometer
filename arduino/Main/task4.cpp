/*
 * task4.cpp
 *
 * Created: 11-12-2013 20:56:36
 *  Author: hp
 */ 
#include <pins_arduino.h>
#include <Global.h>





static int valor;
static int changeMode;
// the setup routine runs once when you press reset:
void task4_setup() {
	// initialize the digital pin as an output.
	DDRD= DDRD & 0xFD;
	valor=0;
	changeMode=0;

}
// the loop routine runs over and over again forever:
void task4_loop() {
	valor = dgtRd(3); 

	

}