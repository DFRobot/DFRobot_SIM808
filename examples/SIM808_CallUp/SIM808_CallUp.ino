/*!
 * @file  SIM808_CallUp.ino
 * @brief  Make phone calls
 * @details  1. This example is used to test DFRobot_SIM808 SIM808 GPS/GPRS/GSM Shield's callUp function.
 * @n        2. Open the SIM808_CallUp example or copy these code to your project
 * @n        3. Replace the phoneNumber：#define PHONE_NUMBER  "187******39"
 * @n        4. Download and dial the function switch to Arduino, and enjoy it
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
 * Try using ESP32
 */
#elif defined(ESP32)
  DFRobot_SIM808 sim808(&Serial1);
/**
 * Use UNO & MEGA2560 for push-in connection
 * Set DIP switch to 3-Arduino, and use the Serial of UNO and MEGA2560 for communication
 */
#else
  DFRobot_SIM808 sim808(&Serial);
#endif

//Mobile phone number,need to change
#define PHONE_NUMBER  "187******39"

void setup() {
  #if CONNECT_BY_JUMPER
    mySerial.begin(9600);
  #elif defined(ARDUINO_AVR_LEONARDO)
    Serial1.begin(9600);
  #elif defined(ESP32)
    Serial1.begin(9600, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
  #endif
  Serial.begin(9600);
  //********Initialize sim808 module*************
  while(!sim808.init()) { 
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }
  Serial.println("Sim808 init success");
  Serial.println("Start to call ...");

  //*********Call specified number***************
  sim808.callUp((char *)PHONE_NUMBER);
}
void loop() {
  //nothing to do
}
