/*
### Auto answer phone calls and read SMS Messages
1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's call answering and
   reading SMS function.
2. Open the SIM808_LoopHandle example or copy these code to your project
3. Download and dial the function switch to Arduino
4. it will Auto-Answer phone calls or send SMS Messages to serial

create on 2016/09/23, version: 1.0
by jason
*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>


//#define PIN_TX    10
//#define PIN_RX    11
//SoftwareSerial mySerial(PIN_TX,PIN_RX);
//DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

#define MESSAGE_LENGTH 20
char gprsBuffer[64];
char *s = NULL;

DFRobot_SIM808 sim808(&Serial);

void setup() {
  //mySerial.begin(9600);
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
