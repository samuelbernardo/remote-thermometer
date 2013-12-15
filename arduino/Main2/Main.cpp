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
#include <new.cpp>
#include <wiring.c>
#include <wiring_digital.c>
#include <wiring_analog.c> //analog read/write functions
#include <WString.cpp>
#include <WMath.cpp>
#include "Task1.cpp"
#include "Task2.cpp"
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


int LIGHTValue;
int LIGHTValueT1;
int LIGHTValueT2;
char recievedBuffer[buffersize];
char transmitBuffer[buffersize];
int receivedbuffersize;
int transmitbuffersize;
/*
* Main harness for sketch.
*/
int main(void)
{
	init();
	
	#if defined(USBCON)
	USBDevice.attach();
	#endif
	
	task1_setup();
	task2_setup();
	task3_setup();
	delay(5000);
	
	while(1) {
		
		delay(50);
		task1_loop();
		task2_loop();
		task3_loop();
		//if (serialEventRun) serialEventRun();
		
		
	}
	return 0;
}
