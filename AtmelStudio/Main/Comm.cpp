/*
 * Comm.cpp		Tarefa que trata da comunicação
 *
 * Created: 10-12-2013 17:41:09
 *  Author: hp
 */ 

#include <pins_arduino.h>
#include "HardwareSerial.h"
#include <Global.h>
#include <string.h>






static int novoThres;

/* estado MODE: 1=query, 2=save   */

static String str;


// the setup routine runs once when you press reset:
void task3_setup() {                
  // initialize the digital pin as an output.

  Mode = 1; /*Modo query*/ /*Modo Save = 2*/
  receivedbuffersize=0;
  transmitbuffersize=0;
  lockReceive=1;
  lockTransmit=0;
  lockTransmitSave=0;
count=0;
  EndReceive=0;
  EndProcess=1;
  novoThres=0;

}
void commandProcess(){
	
	switch (recievedBuffer[0])
	{
	case '1' : 
	//do something
		switch (recievedBuffer[1])
		{
		case '0':
			str = String(TMP36ValueT1);
			receivedbuffersize=str.length()+1;
			str.toCharArray(transmitBuffer,buffersize);
			
			//Serial.println(receivedbuffersize);
			EndReceive=0;
			lockTransmit=1;
			break;
			
		case '1':
			/*Devolve valor do threshold do terceiro sensor
			* Sensor nao implementado
			*/
			EndReceive=0;
			lockReceive=1;
			transmitbuffersize=0;
			receivedbuffersize=0;
			break;
					
		case '2':
		/**/	Mode=2;
			EndReceive=0;/*Var de modo query*/
			lockReceive=1;/*Var de modo query*/
			lockTransmit=0;/*Var de modo query*/
			EndProcess=1;/*Var de modo save*/
			lockTransmitSave=0;/*Var de modo save*/
			transmitbuffersize=0;
			receivedbuffersize=0;
			break;
		case '3':
			/*Leitura do sensor de em A0*/
			str = String(LIGHTValue);
			receivedbuffersize=str.length();
			str.toCharArray(transmitBuffer,buffersize);
		
			//Serial.println(receivedbuffersize);
			EndReceive=0;
			lockTransmit=1;
			break;
		}
		break;
	case '2': 
	//do something
					/*Leitura do sensor de em A0*/
					str = String(TMP36Value);
					receivedbuffersize=5;
					str.toCharArray(transmitBuffer,receivedbuffersize);
					
					//Serial.println(receivedbuffersize);
					EndReceive=0;
					lockTransmit=1;
					
		break;
		
		case '3':
		/*Terceiro sensor, não implementado*/
					EndReceive=0;
					lockReceive=1;
					transmitbuffersize=0;
					receivedbuffersize=0;
			break;
		
		case '4':
		
			str="";
			str.concat(recievedBuffer[1]);str.concat(recievedBuffer[2]);str.concat(recievedBuffer[3]);str.concat(recievedBuffer[4]);
			novoThres = str.toInt();
			LIGHTValueT1=novoThres;
			EndReceive=0;
			transmitbuffersize=0;
			receivedbuffersize=0;
			lockTransmit=0;
			lockReceive=1;
		
			break;
		
		case '5':
				
				str="";
				str.concat(recievedBuffer[1]);str.concat(recievedBuffer[2]);str.concat(recievedBuffer[3]);str.concat(recievedBuffer[4]);
				novoThres = str.toInt();
				LIGHTValueT2=novoThres;
				EndReceive=0;
				transmitbuffersize=0;
				receivedbuffersize=0;
				lockTransmit=0;
				lockReceive=1;
			break;
		
		case '6':
				str="";
				str.concat(recievedBuffer[1]);str.concat(recievedBuffer[2]);str.concat(recievedBuffer[3]);str.concat(recievedBuffer[4]);
				novoThres = str.toInt();
				TMP36ValueT1=novoThres;
				EndReceive=0;
				transmitbuffersize=0;
				receivedbuffersize=0;
				lockTransmit=0;
				lockReceive=1;
			break;
		
		case '7':
				/*Configurar threshold para terceiro sensor
				* Sensor nao implementado
				*/
				EndReceive=0;
				lockReceive=1;
				transmitbuffersize=0;
				receivedbuffersize=0;
			break;
		
		case '8':
				str = String(LIGHTValueT1);
				receivedbuffersize=str.length();
				str.toCharArray(transmitBuffer,buffersize);
				
				//Serial.println(receivedbuffersize);
				EndReceive=0;
				lockTransmit=1;
			break;
		
		case '9':
				str = String(LIGHTValueT2);
				receivedbuffersize=str.length();
				str.toCharArray(transmitBuffer,buffersize);
				
				//Serial.println(receivedbuffersize);
				EndReceive=0;
				lockTransmit=1;
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
void transmitDataSave(){
		if( transmitbuffersize < receivedbuffersize){
			Serial.println(transmitBuffer[transmitbuffersize]);
			transmitbuffersize++;
			}else{
			transmitbuffersize=0;
			receivedbuffersize=0;
			lockTransmitSave=0;
			count = 0;
			EndProcess=1;
		}
}
void commandProcessSave(){
	String s1,s2;
	
	str="1";
	s1 = String(LIGHTValue);
	str.concat(s1);
	s2 = String(TMP36Value);
	s2.toCharArray(transmitBuffer,6);
	s2=String(transmitBuffer);
	str.concat("_2");
	str.concat(s2);
	

	receivedbuffersize=str.length();
	str.toCharArray(transmitBuffer,receivedbuffersize);
	transmitbuffersize=0;
	EndProcess=0;
	lockTransmitSave=1;
	
}
void task3_loop() {
	switch (Mode)
	{
	case 1:
	/*QUERY MODE*/

		if(lockReceive)	receivedData();
		if(lockTransmit) transmitData();
		if(EndReceive) commandProcess();
	
		
		break;
	case 2:
	/*SAVE MODE*/
	if(count>2000 ){
			
			if(EndProcess) commandProcessSave();
			if(lockTransmitSave) transmitDataSave();

	}
	count++;
	
	
	
	break;
	}
}





