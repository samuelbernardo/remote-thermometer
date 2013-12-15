#define ARDUINO_MAIN

// Disable some warnings for the Arduino files
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wuninitialized"

#include <Arduino.h>

extern "C"{
	#include <pins_arduino.h>
}

/*
* Libraries
*/
// Arduino Leonardo source files for serial:
#define USB_VID 0x2341
#define USB_PID 0x8036
#include <CDC.cpp>
#include <USBCore.cpp>
#include <HID.cpp>

// Other source files, depends on your program which you need
#include <Print.cpp>
#include <New.cpp>
#include <wiring.c>
#include <wiring_digital.c>
#include <wiring_analog.c> //analog read/write functions
#include <WString.cpp>
#include <WMath.cpp>
#include "Task1.cpp"
#include "Task2.cpp"
#include "Task4.cpp"
#include "Comm.cpp"
#include <Global.h>
// Unused source files:
//#include <WInterrupts.c>
//#include <wiring_pulse.c>
//#include <wiring_shift.c>
//#include <IPAddress.cpp>
//#include <Tone.cpp>

// Restore original warnings configuration
#pragma GCC diagnostic pop

/*
int LIGHTValue;
int LIGHTValueT1;
int LIGHTValueT2;
float TMP36Value;
float TMP36ValueT1;
int Mode;
int EndProcess;
//int lockTransmitSave;


char recievedBuffer[buffersize];
char transmitBuffer[buffersize];
int receivedbuffersize;
int transmitbuffersize;
*/
static int anarf = 1;
/*
* Main harness for sketch.
*/
int dgtRd(uint8_t pin){
		uint8_t timer = digitalPinToTimer(pin);
		uint8_t bit = digitalPinToBitMask(pin);
		uint8_t port = digitalPinToPort(pin);

		if (port == NOT_A_PIN) return LOW;

		// If the pin that support PWM output, we need to turn it off
		// before getting a digital reading.
		if (timer != NOT_ON_TIMER) turnOffPWM(timer);

		if (*portInputRegister(port) & bit) return HIGH;
		return LOW;
	
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
int main(void)
{
	init();
	
	#if defined(USBCON)
	USBDevice.attach();
	#endif
	
	task1_setup();
	task2_setup();
	task3_setup();
	task4_setup();
	delay(5000);
	
	while(1) {
		
		task1_loop();
		task2_loop();
		task3_loop();
		task4_loop();
		//if (serialEventRun) serialEventRun();
		
		
	}
	return 0;
}