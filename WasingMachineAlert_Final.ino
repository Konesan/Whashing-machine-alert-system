//Washing Machine Alert  System
//EE322 Project
//Group 14

#include <SoftwareSerial.h>

SoftwareSerial sim800l(2, 3); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

void setup()
{
  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);
  //delay(1000);

  pinMode(A0, INPUT);   //declaring inputs
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
  pinMode(7, OUTPUT); //declaring the output
}

void loop()
{
//reading analog inputs
  if (digitalRead(A0) && digitalRead(A1)){
    if (digitalRead(A2) || digitalRead(A3)){
      digitalWrite(7, LOW);             //turning off the LED if the a and b bits are on
      }else{
        digitalWrite(7, HIGH);
        SendSMS();                          //And this function is called
      }
  }
  if (sim800l.available())             //Displays on the serial monitor if there's a communication from the module
  {
    Serial.write(sim800l.read());
  }
}

void SendSMS()
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+94767749492\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(100);
  sim800l.print("Washing Process is over. Take your clothes out");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(100);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(100);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(100);
}
