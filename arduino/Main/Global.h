/*
 * Global.h
 *
 * Created: 10-12-2013 19:15:20
 *  Author: hp
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_



/*Variáveis Globais*/
#define buffersize 16
static char recievedBuffer[buffersize];
static char transmitBuffer[buffersize];
static  int receivedbuffersize;
static  int transmitbuffersize;
static  int LIGHTValue;
static  int LIGHTValueT1;
static  int LIGHTValueT2;
static  float TMP36Value;
static  float TMP36ValueT1;
static  int Mode;
static  int EndProcess;
static  int lockTransmitSave;
static int lockTransmit;
static int lockReceive;
static int EndReceive;

static int anlRd(uint8_t pin);
static int dgtRd(uint8_t pin);





#endif /* GLOBAL_H_ */