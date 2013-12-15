/*
 * Comm.cpp		Tarefa que trata da comunicação
 *
 * Created: 10-12-2013 17:41:09
 *  Author: hp
 */ 

#include <pins_arduino.h>
#include "HardwareSerial.h"
#include <Global.h>




static int lockTransmit;
static int lockReceive;
static int transmit_Flag;
static int EndReceive;

/* estado MODE: 1=query, 2=save   */
static int MODE;
static String str;


// the setup routine runs once when you press reset:
void task3_setup() {                
  // initialize the digital pin as an output.

  MODE = 1; /*Modo query*/
  receivedbuffersize=0;
  transmitbuffersize=0;
  lockReceive=1;
  lockTransmit=0;
  transmit_Flag=0;
  EndReceive=0;

}
void commandProcess(){
	
	switch (recievedBuffer[0])
	{
	case '1' : 
	//do something
		switch (recievedBuffer[1])
		{
		case '0':
			break;
		case '1':
			break;
		default : 
			/*Leitura do sensor de em A0*/
			str = String(LIGHTValue);
			str.toCharArray(transmitBuffer,buffersize);
			receivedbuffersize=str.length();
			//Serial.println(receivedbuffersize);
			EndReceive=0;
			lockTransmit=1;
			break;
		}
		break;
	case '2': 
	//do something
		recievedBuffer[0]='0';
		transmitbuffersize=0;
		receivedbuffersize=0;
		EndReceive=0;
		lockReceive=1;/*para nao bloquear, apagar esta lnha quando definir o comando 2*/
		break;
	}
}
void receivedData(){
int i;
	if(Serial.available() && receivedbuffersize < buffersize && EndReceive==0){
		i=Serial.read();
		recievedBuffer[receivedbuffersize]=i;
		receivedbuffersize++;
	
	}else{
		if(!Serial.available() && receivedbuffersize!=0){
			EndReceive=1;
			lockReceive=0;
		}
	}	
}
void transmitData(){
	if( transmitbuffersize < receivedbuffersize){
		Serial.println(transmitBuffer[transmitbuffersize]);
		transmitbuffersize++;
	}else{
		transmitbuffersize=0;
		receivedbuffersize=0;
		lockTransmit=0;
		lockReceive=1;
	}
}
// the loop routine runs over and over again forever:
void task3_loop() {
	switch (MODE)
	{
	case 1:
		if(lockReceive)	receivedData();
		if(lockTransmit) transmitData();
		if(EndReceive) commandProcess();	
		break;
	case 2:
	break;
	}
}





