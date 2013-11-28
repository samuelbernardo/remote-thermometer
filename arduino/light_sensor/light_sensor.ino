int LDR = 0;                                //analog pin to which LDR is connected, here we set it to 0 so it means A0
int Temp1 = 1;                                //analog pin to which LDR is connected, here we set it to 0 so it means A0
int Temp2 = 2;                                //analog pin to which LDR is connected, here we set it to 0 so it means A0
int LDRValue = 0;                    //that’s a variable to store LDR values
int in = 0;                  //that’s a variable to store LDR values
float voltage=0;

float Temp = 0;                    //that’s a variable to store LDR values
int light_sensitivity = 500;  //This is the approx value of light surrounding your LDR

 
void setup()
  {
    Serial.begin(9600);            //start the serial monitor with 9600 buad
    pinMode(13, OUTPUT);     //we mostly use13 because there is already a built in yellow LED in arduino which shows output when 13 pin is enabled
  }
 
void loop()
  {
  
    LDRValue = analogRead(LDR);          //reads the ldr’s value through LDR which we have set to Analog input 0 “A0″
    Serial.println(LDRValue);                  //prints the LDR values to serial monitor
    delay(50);                                                //This is the speed by which LDR sends value to arduino
 
    if (LDRValue < light_sensitivity) 
      {
        digitalWrite(13, HIGH);
      }
    else
      {
        digitalWrite(13, LOW);
      }
      
      in = analogRead(Temp1);
      voltage = in*5.0;
      voltage/=1024.0;
      Serial.print(voltage,5); Serial.println(" volts");
      Temp = (voltage - 0.5)*100;
      Serial.println(Temp);
      
      
      in = analogRead(Temp2);
      voltage = in*2.5;
      voltage/=1024.0;
      Serial.print(voltage,5); Serial.println(" volts");
      
      Temp = (voltage - 0.5) * 100;
      Serial.println(Temp);
   
  }

