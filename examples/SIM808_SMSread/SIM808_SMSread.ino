/*!
 * @file  SIM808_SMSread.ino
 * @brief  Read SMS messages
 * @details  1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's reading SMS
 * @n        2. Open the SIM808_SMSread example or copy these code to your project
 * @n        3. Download and dial the function switch to Arduino
 * @n        4. it will receive SMS Messages and send it to serial
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

#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;

char phone[16];
char datetime[24];

void setup() {
  #if CONNECT_BY_JUMPER
    mySerial.begin(9600);
  #elif defined(ARDUINO_AVR_LEONARDO)
    Serial1.begin(9600);
  #endif
  Serial.begin(9600);

  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      Serial.print("Sim808 init error\r\n");
      delay(1000);
  }
  delay(3000);  
  Serial.println("Init Success, please send SMS message to me!");
}

void loop() {
  //*********** Detecting unread SMS ************************
   messageIndex = sim808.isSMSunread();
    Serial.print("messageIndex: ");
    Serial.println(messageIndex);

   //*********** At least, there is one UNREAD SMS ***********
   if (messageIndex > 0) { 
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);
                 
      //***********In order not to full SIM Memory, is better to delete it**********
      sim808.deleteSMS(messageIndex);
      Serial.print("From number: ");
      Serial.println(phone);  
      Serial.print("Datetime: ");
      Serial.println(datetime);        
      Serial.print("Recieved Message: ");
      Serial.println(message);    
   }
}
