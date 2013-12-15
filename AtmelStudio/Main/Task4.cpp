/*
 * task4.cpp
 *
 * Created: 11-12-2013 20:56:36
 *  Author: hp
 */ 
#include <pins_arduino.h>
#include <Global.h>
#include <WString.h>






static int valor;
static int changeMode;
static String st = "MODEOFF";
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
	if(valor ==1 && changeMode==0 && Mode==2)
	{
		changeMode=1;
	}
	
	if(changeMode==1 && count<1000 && Mode == 2){
		Mode=1;
		changeMode=0;
		EndProcess=1;
		lockTransmitSave=0;
		EndReceive=0;
		lockReceive=1;
		lockTransmit=0;
		//receivedbuffersize=st.length();
		//st.toCharArray(transmitBuffer,buffersize);
		String("").toCharArray(recievedBuffer, buffersize);	
		String("").toCharArray(transmitBuffer, buffersize);		
		/**/
		receivedbuffersize=0;
	
		transmitbuffersize=0;
		
	}

}