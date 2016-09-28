/*
### Connect TCP and send GET request.
1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's connect TCP and send GET request.
2. Open the SIM808_TCPConnection example or copy these code to your project
3. Download and dial the function switch to Arduino
4. Open serial helper
5. Waiting for a few minutes, until serial has sent "Connect mbed.org success"
6. Serial will send "Hello world!"

create on 2016/09/23, version: 1.0
by jason
*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

//#define PIN_TX    10
//#define PIN_RX    11
//SoftwareSerial mySerial(PIN_TX,PIN_RX);
//DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

//make sure that the baud rate of SIM900 is 9600!
//you can use the AT Command(AT+IPR=9600) to set it through SerialDebug

DFRobot_SIM808 sim808(&Serial);

char http_cmd[] = "GET /media/uploads/mbed_official/hello.txt HTTP/1.0\r\n\r\n";
char buffer[512];

void setup(){
  //mySerial.begin(9600);
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
