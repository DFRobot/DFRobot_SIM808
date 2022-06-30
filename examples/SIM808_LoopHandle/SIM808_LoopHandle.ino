/*!
 * @file  SIM808_LoopHandle.ino
 * @brief  Auto answer phone calls and read SMS Messages
 * @details  1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's 
 * @n           call answering and reading SMS function.
 * @n        2. Open the SIM808_LoopHandle example or copy these code to your project
 * @n        3. Download and dial the function switch to Arduino
 * @n        4. it will Auto-Answer phone calls or send SMS Messages to serial
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

#define MESSAGE_LENGTH 20
char gprsBuffer[64];
char *s = NULL;

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
  Serial.println("Init Success, please call or send SMS message to me!");
}

void loop() {
   //******** Wait serial data *************
   if(sim808.readable()){
      sim808_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
      //Serial.print(gprsBuffer);

   //************** Detect the current state of the telephone or SMS ************************
      if(NULL != strstr(gprsBuffer,"RING")) {
          sim808.answer();
      }else if(NULL != (s = strstr(gprsBuffer,"+CMTI: \"SM\""))) { //SMS: $$+CMTI: "SM",24$$
          char message[MESSAGE_LENGTH];
          int messageIndex = atoi(s+12);
          sim808.readSMS(messageIndex, message,MESSAGE_LENGTH);
          Serial.print("Recv Message: ");
          Serial.println(message);
     }
     sim808_clean_buffer(gprsBuffer,32);  
   }
}
