/*
GPRS Call Up 

This sketch is used to test seeeduino GPRS_Shield's callUp function.
to make it work, you should insert SIM card to Seeeduino GPRS 
and replace the phoneNumber,enjoy it!
create on 2016/09/23, version: 1.0
by jason
*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define PHONE_NUMBER  "18750762139"

GPRS gprsTest(&Serial);

void setup() {
  Serial.begin(9600);
  while(!gprsTest.init()) { //gprs init
      delay(1000);
      Serial.print("init error\r\n");
  }
  Serial.println("gprs init success");
  Serial.println("start to call ...");
  gprsTest.callUp(PHONE_NUMBER);
}
void loop() {
  //nothing to do
}
