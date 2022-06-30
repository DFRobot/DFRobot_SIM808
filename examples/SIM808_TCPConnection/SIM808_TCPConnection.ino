/*!
 * @file  SIM808_TCPConnection.ino
 * @brief  Connect TCP and send GET request.
 * @details  1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's connect TCP and send GET request.
 * @n        2. Open the SIM808_TCPConnection example or copy these code to your project
 * @n        3. Download and dial the function switch to Arduino
 * @n        4. Open serial helper
 * @n        5. Waiting for a few minutes, until serial has sent "Connect mbed.org success"
 * @n        6. Serial will send "Hello world!"
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

char http_cmd[] = "GET /media/uploads/mbed_official/hello.txt HTTP/1.0\r\n\r\n";
char buffer[512];

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
  delay(3000);  
    
  //*********** Attempt DHCP *******************
  while(!sim808.join(F("cmnet"))) {
      Serial.println("Sim808 join network error");
      delay(2000);
  }

  //************ Successful DHCP ****************
  Serial.print("IP Address is ");
  Serial.println(sim808.getIPAddress());

  //*********** Establish a TCP connection ************
  if(!sim808.connect(TCP,"mbed.org", 80)) {
      Serial.println("Connect error");
  }else{
      Serial.println("Connect mbed.org success");
  }

  //*********** Send a GET request *****************
  Serial.println("waiting to fetch...");
  sim808.send(http_cmd, sizeof(http_cmd)-1);
  while (true) {
      int ret = sim808.recv(buffer, sizeof(buffer)-1);
      if (ret <= 0){
          Serial.println("fetch over...");
          break; 
      }
      buffer[ret] = '\0';
      Serial.print("Recv: ");
      Serial.print(ret);
      Serial.print(" bytes: ");
      Serial.println(buffer);
      break;
  }

  //************* Close TCP or UDP connections **********
  sim808.close();

  //*** Disconnect wireless connection, Close Moving Scene *******
  sim808.disconnect();
}

void loop(){

}
