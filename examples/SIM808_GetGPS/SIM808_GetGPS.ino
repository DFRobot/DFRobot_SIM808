/*
### Get GPS data
1. This example is used to test SIM808 GPS/GPRS/GSM Shield's reading GPS data.
2. Open the SIM808_GetGPS example or copy these code to your project
3. Download and dial the function switch to Arduino
4. open serial helper
4. Place it outside, waiting for a few minutes and then it will send GPS data to serial

create on 2016/09/23, version: 1.0
by jason

*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

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

  //************* Turn on the GPS power************
  if( sim808.attachGPS())
      Serial.println("Open the GPS power success");
  else 
      Serial.println("Open the GPS power failure");
  
}

void loop() {
   //************** Get GPS data *******************
   if (sim808.getGPS()) {
    Serial.print(sim808.GPSdata.year);
    Serial.print("/");
    Serial.print(sim808.GPSdata.month);
    Serial.print("/");
    Serial.print(sim808.GPSdata.day);
    Serial.print(" ");
    Serial.print(sim808.GPSdata.hour);
    Serial.print(":");
    Serial.print(sim808.GPSdata.minute);
    Serial.print(":");
    Serial.print(sim808.GPSdata.second);
    Serial.print(":");
    Serial.println(sim808.GPSdata.centisecond);
    Serial.print("latitude :");
    Serial.println(sim808.GPSdata.lat);
    Serial.print("longitude :");
    Serial.println(sim808.GPSdata.lon);
    Serial.print("speed_kph :");
    Serial.println(sim808.GPSdata.speed_kph);
    Serial.print("heading :");
    Serial.println(sim808.GPSdata.heading);
    Serial.println();

    //************* Turn off the GPS power ************
    sim808.detachGPS();
  }

}
