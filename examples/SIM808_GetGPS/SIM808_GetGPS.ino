/*!
 * @file  SIM808_GetGPS.ino
 * @brief  Get GPS data
 * @details  1. This example is used to test SIM808 GPS/GPRS/GSM Shield's reading GPS data.
 * @n        2. Open the SIM808_GetGPS example or copy these code to your project
 * @n        3. Download and dial the function switch to Arduino
 * @n        4. open serial helper
 * @n        4. Place it outside, waiting for a few minutes and then it will send GPS data to serial
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [Jason](jason.ling@dfrobot.com)
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-02-08
 * @url  https://github.com/DFRobot/DFRobot_SIM808
 */
#include <DFRobot_SIM808.h>

/**
 * Besides push-in connection with expansion board, it can also be connected by jump wires
 * Set DIP switch to 3-Arduino, open the following macro
 * Connect the main controller to the module with Dupont wires:
 *  Arduino | module
 *   PIN_TX |  TX1
 *   PIN_RX |  RX1
 * Power the module, which is successful when the power indicator on the module is ON
 */
// #define CONNECT_BY_JUMPER   1
#if CONNECT_BY_JUMPER
  #define PIN_TX    10
  #define PIN_RX    11
  SoftwareSerial mySerial(PIN_TX, PIN_RX);
  DFRobot_SIM808 sim808(&mySerial);
/**
 * Use Leonardo for push-in connection
 * Set DIP switch to 3-Arduino, and use the Serial1 of Leonardo for communication
 */
#elif defined(ARDUINO_AVR_LEONARDO)
  DFRobot_SIM808 sim808(&Serial1);
/**
 * Use UNO & MEGA2560 for push-in connection
 * Set DIP switch to 3-Arduino, and use the Serial of UNO and MEGA2560 for communication
 */
#else
  DFRobot_SIM808 sim808(&Serial);
#endif

void setup() {
  #if CONNECT_BY_JUMPER
    mySerial.begin(9600);
  #elif defined(ARDUINO_AVR_LEONARDO)
    Serial1.begin(9600);
  #endif
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
    Serial.println(sim808.GPSdata.lat,6);
    
    sim808.latitudeConverToDMS();
    Serial.print("latitude :");
    Serial.print(sim808.latDMS.degrees);
    Serial.print("\^");
    Serial.print(sim808.latDMS.minutes);
    Serial.print("\'");
    Serial.print(sim808.latDMS.seconeds,6);
    Serial.println("\"");
    Serial.print("longitude :");
    Serial.println(sim808.GPSdata.lon,6);
    sim808.LongitudeConverToDMS();
    Serial.print("longitude :");
    Serial.print(sim808.longDMS.degrees);
    Serial.print("\^");
    Serial.print(sim808.longDMS.minutes);
    Serial.print("\'");
    Serial.print(sim808.longDMS.seconeds,6);
    Serial.println("\"");
    
    Serial.print("speed_kph :");
    Serial.println(sim808.GPSdata.speed_kph);
    Serial.print("heading :");
    Serial.println(sim808.GPSdata.heading);

    //************* Turn off the GPS power ************
    sim808.detachGPS();
  }

}
