/*
GPRS Call Up 

This sketch is used to test seeeduino GPRS_Shield's callUp function.
to make it work, you should insert SIM card to Seeeduino GPRS 
and replace the phoneNumber,enjoy it!

create on 2015/05/14, version: 1.0
by lawliet.zou(lawliet.zou@gmail.com)
*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

//#define PIN_TX    10
//#define PIN_RX    11
//SoftwareSerial mySerial(PIN_TX,PIN_RX);
//GPRS gprsTest(&mySerial);//RX,TX,PWR,

GPRS gprsTest(&Serial);

void setup() {
  Serial.begin(9600);
  while(!gprsTest.init()) { //gprs init
      delay(1000);
      Serial.print("init error\r\n");
  }

if( gprsTest.attachGPS())
    Serial.println("gprs init success");
else 
    Serial.println("status=ERROR");
  
}

void loop() {
   bool gps_success = gprsTest.getGPS();
   if (gps_success) {
    Serial.print(gprsTest.GPSdata.year);
    Serial.print("/");
    Serial.print(gprsTest.GPSdata.month);
    Serial.print("/");
    Serial.print(gprsTest.GPSdata.day);
    Serial.print(" ");
    Serial.print(gprsTest.GPSdata.hour);
    Serial.print(":");
    Serial.print(gprsTest.GPSdata.minute);
    Serial.print(":");
    Serial.print(gprsTest.GPSdata.second);
    Serial.print(":");
    Serial.println(gprsTest.GPSdata.centisecond);
    Serial.print("latitude :");
    Serial.println(gprsTest.GPSdata.lat);
    Serial.print("longitude :");
    Serial.println(gprsTest.GPSdata.lon);
    Serial.print("speed_kph :");
    Serial.println(gprsTest.GPSdata.speed_kph);
    Serial.print("heading :");
    Serial.println(gprsTest.GPSdata.heading);
    Serial.println();
    gprsTest.detachGPS();
  }

}
