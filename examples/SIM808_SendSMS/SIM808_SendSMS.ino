/*
### Send SMS messages
1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's send SMS func.
2. Open the SIM808_SendSMS example or copy these code to your project
3. Replace the phoneNumber：#define PHONE_NUMBER  "187******39"    
4. Download and dial the function switch to Arduino, and enjoy it

create on 2016/09/23, version: 1.0
by jason
*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

//Mobile phone number,need to change
#define PHONE_NUMBER "187*******39"  
 
//The content of messages sent
#define MESSAGE  "hello,world"

//#define PIN_TX    10
//#define PIN_RX    11
//SoftwareSerial mySerial(PIN_TX,PIN_RX);
//DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

DFRobot_SIM808 sim808(&Serial);

void setup() {
  //mySerial.begin(9600);
  Serial.begin(9600);
 
 //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }  
  Serial.println("Sim808 init success");
  Serial.println("Start to send message ...");

  //******** define phone number and text **********
  sim808.sendSMS(PHONE_NUMBER,MESSAGE); 
}

void loop() {
  //nothing to do
}
