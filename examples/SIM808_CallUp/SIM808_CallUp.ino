/*
SIM808 Call Up 

This sketch is used to test  SIM808 GPS/GPRS/GSM Shield's callUp function.
to make it work, you should insert SIM card to SIM808 GPS/GPRS/GSM Shield 
and replace the phoneNumber,enjoy it!
create on 2016/09/23, version: 1.0
by jason
*/

#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

//#define PIN_TX    10
//#define PIN_RX    11
//SoftwareSerial mySerial(PIN_TX,PIN_RX);
//DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

//Mobile phone number,need to change
#define PHONE_NUMBER  "187******39"   

DFRobot_SIM808 sim808(&Serial);

void setup() {
  //mySerial.begin(9600);
  Serial.begin(9600);
  //********Initialize sim808 module*************
  while(!sim808.init()) { 
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }
  Serial.println("Sim808 init success");
  Serial.println("Start to call ...");

  //*********Call specified number***************
  sim808.callUp(PHONE_NUMBER);
}
void loop() {
  //nothing to do
}
