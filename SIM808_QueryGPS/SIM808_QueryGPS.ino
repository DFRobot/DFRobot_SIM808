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

// Arduino Uno Wifi Rev2
#define PIN_TX    1
#define PIN_RX    0
SoftwareSerial simSerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&simSerial);//Connect RX,TX,PWR,

//DFRobot_SIM808 sim808(&Serial);

void setup() {
  // Arduino Uno Wifi Rev2 has a hardware Serial
  // and talks to the dfrobot board using digital pins 0,1
  simSerial.begin(9600);
  Serial.begin(9600);

  //******** Initialize sim808 module *************
  while(!sim808.init(false)) { 
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
      Serial.println("\n\n");
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
    Serial.println(sim808.GPSdata.lat,6);
    
    sim808.latitudeConverToDMS();
    Serial.print("latitude :");
    Serial.print(sim808.latDMS.degrees);
    Serial.print(167);
    Serial.print(sim808.latDMS.minutes);
    Serial.print("\'");
    Serial.print(sim808.latDMS.seconds,6);
    Serial.println("\"");
    Serial.print("longitude :");
    Serial.println(sim808.GPSdata.lon,6);
    sim808.LongitudeConverToDMS();
    Serial.print("longitude :");
    Serial.print(sim808.longDMS.degrees);
    Serial.print(167);
    Serial.print(sim808.longDMS.minutes);
    Serial.print("\'");
    Serial.print(sim808.longDMS.seconds,6);
    Serial.println("\"");
    
    Serial.print("speed_kph :");
    Serial.println(sim808.GPSdata.speed_kph);
    Serial.print("heading :");
    Serial.println(sim808.GPSdata.heading);

    Serial.print("pressions (h,v,p):");
    Serial.print(sim808.GPSStatus.horizontal_pres);
    Serial.print(",");
    Serial.print(sim808.GPSStatus.vertical_pres);
    Serial.print(",");
    Serial.println(sim808.GPSStatus.position_pres);

    Serial.print("satellites (inview, used, Glonass):");
    Serial.print(sim808.GPSStatus.sat_in_view);
    Serial.print(",");
    Serial.print(sim808.GPSStatus.sat_used);
    Serial.print(",");
    Serial.println(sim808.GPSStatus.sat_glonass);

    Serial.print("CGNSINF:");
    for (int i=0; i < sizeof(sim808.cgnsinf)-1; i++)  {
        if (sim808.cgnsinf[i]<32) sim808.cgnsinf[i] = ' ';
    }
    Serial.println(sim808.cgnsinf);

  } else {
    Serial.println("getGPS failed");
    delay(1000);
  }

}
