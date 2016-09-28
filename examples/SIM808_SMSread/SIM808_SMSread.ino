/*
SIM808 SMS Read

This sketch is used to test SIM808 GPS/GPRS/GSM Shield's reading SMS 
function.To make it work, you should insert SIM card to SIM808 
GPS/GPRS/GSM Shield,enjoy it!

There are two methods to read SMS:
  1. SIM808_LoopHandle.ino  -> in order to recieve "+CMTI: "SM"" 
      may be you need to send this command to your shield: "AT+CNMI=2,2,0,0,0"
  2. SIM808_SMSread.ino -> you have to check if there are any 
      UNREAD sms, and you don't need to check serial data continuosly

create on 2016/09/23, version: 1.0
by jason
*/

#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;

char phone[16];
char datetime[24];

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
