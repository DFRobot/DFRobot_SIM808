/*!
 * @file DFRobot_sim808.h
 * @n Header file for DFRobot's SIM808 GPS/DFRobot_SIM808/GSM Shield
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 *
 * @author [Jason](jason.ling@dfrobot.com)
 * @version  V1.0
 * @date  2016-09-23
 
  * The MIT License (MIT)
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#ifndef __DFROBOT_SIM808_H__
#define __DFROBOT_SIM808_H__

#include "sim808.h"

/** DFRobot_SIM808 class.
 *  used to realize DFRobot_SIM808 communication
 */ 
 
enum Protocol {
    CLOSED = 0,
    TCP    = 1,
    UDP    = 2,
};

class DFRobot_SIM808
{
public:
    /** Create DFRobot_SIM808 instance
     *  @param number default phone number during mobile communication
     */
	 
    DFRobot_SIM808(uint8_t tx, uint8_t rx, uint32_t baudRate = 9600 ); 
	DFRobot_SIM808(HardwareSerial *mySerial);
	DFRobot_SIM808(SoftwareSerial *mySerial);
    
    /** get instance of DFRobot_SIM808 class
     */
    static DFRobot_SIM808* getInstance() {
        return inst;
    };
    
    /** initialize DFRobot_SIM808 module including SIM card check & signal strength
     *  @return true if connected, false otherwise
     */

    bool init(void);

   
    /** check if DFRobot_SIM808 module is powered on or not
     *  @returns
     *      true on success
     *      false on error
     */
    bool checkPowerUp(void);

    
    /** power Up DFRobot_SIM808 module (JP has to be soldered)
     *  @param  pin pin 9 connected to JP jumper so we can power up and down through software
     *  @returns
     *      
     */
    void powerUpDown(uint8_t pin);  
    
    /** power reset for SIM800 board 
     *  @param  pin (preconfigurated as OUTPUT)
     *  @returns
     *      
     */	
    void powerReset(uint8_t pin);
     
     
    /** send text SMS
     *  @param  *number phone number which SMS will be send to
     *  @param  *data   message that will be send to
     *  @returns
     *      false on success
     *      true on error
     */
    bool sendSMS(char* number, char* data);

    /** Check if there is any UNREAD SMS: this function DOESN'T change the UNREAD status of the SMS
     *  @returns
     *      1..20 on success, position/index where SMS is stored, suitable for the function ReadSMS
     *      -1 on error
     *       0 - there is no SMS with specified status (UNREAD)
     */

	char isSMSunread();
    
    /** read SMS, phone and date if getting a SMS message. It changes SMS status to READ 
     *  @param  messageIndex  SIM position to read
     *  @param  message  buffer used to get SMS message
     *  @param  length  length of message buffer
     *  @param  phone  buffer used to get SMS's sender phone number
     *  @param  datetime  buffer used to get SMS's send datetime
     *  @returns
     *      true on success
     *      false on error
     */
    bool readSMS(int messageIndex, char *message, int length, char *phone, char *datetime); 

    /** read SMS if getting a SMS message
     *  @param  buffer  buffer that get from DFRobot_SIM808 module(when getting a SMS, DFRobot_SIM808 module will return a buffer array)
     *  @param  message buffer used to get SMS message
     *  @param  check   whether to check phone number(we may only want to read SMS from specified phone number)
     *  @returns
     *      true on success
     *      false on error
     */
    bool readSMS(int messageIndex, char *message, int length);

    /** delete SMS message on SIM card
     *  @param  index   the index number which SMS message will be delete
     *  @returns
     *      true on success
     *      false on error
     */
    bool deleteSMS(int index);

    /** call someone
     *  @param  number  the phone number which you want to call
     *  @returns
     *      true on success
     *      false on error
     */
    bool callUp(char* number);

    /** auto answer if coming a call
     *  @returns
     */    
    void answer(void);
    
    /** hang up if coming a call
     *  @returns
     *      true on success
     *      false on error
     */    
    bool hangup(void);  

    /** Disable +CLIP notification when an incoming call is active, RING text is always shown. See isCallActive function
     *  This is done in order no to overload serial outputCheck if there is a call active and get the phone number in that case
     *  @returns
     *      true on success
     *      false on error
     */
    bool disableCLIPring(void);
	
	/** Get Subscriber Number (your number) using AT+CNUM command, but if nothing returns, then
	 *  you need to command this to your SIM900. (See AT+CPBS, AT+CPBW)
	 *	AT+CPBS="ON"
	 *	AT+CPBW=1,"+{Your Number}",145
	 *	AT+CPBS="SM"
	 *  @param
	 *	@return
	 *		true on success
	 *		false on error
	 */
	bool getSubscriberNumber(char *number);
    
	/** Check if there is a call active and get the phone number in that case
     *  @returns
     *      true on success
     *      false on error
     */
    bool isCallActive(char *number);  

    /** get DateTime from SIM900 (see AT command: AT+CLTS=1) as string
     *  @param
     *  @returns
     *      true on success
     *      false on error
     * 
     * 	   If it doesn't work may be for two reasons:
     *	 	1. Your carrier doesn't give that information
     *		2. You have to configurate the SIM900 IC.
         *			- First with SIM900_Serial_Debug example try this AT command: AT+CLTS?
	 *			- If response is 0, then it is disabled.
	 *			- Enable it by: AT+CLTS=1
	 *			- Now you have to save this config to EEPROM memory of SIM900 IC by: AT&W
	 *			- Now, you have to power down and power up again the SIM900 
	 *			- Try now again: AT+CCLK?
	 *			- It should work now
	 *
     */
       
    bool getDateTime(char *buffer);
    
	/** get Signal Strength from SIM900 (see AT command: AT+CSQ) as integer
	*  @param
	*  @returns
	*      true on success
	*      false on error
	*/
	bool getSignalStrength(int *buffer);
    
    /** Send USSD Command Synchronously (Blocking call until unsolicited response is received)
     *  @param
	 *		*ussdCommand string command UUSD, ex: *123#
	 *		*resultCode	char Result Code, see AT+CUSD command
	 *		*response	string response
	 *		*cellBroadcast	int Cell Broadcast Data Coding Scheme
     *  @returns
     *      true on success
     *      false on error
     */  
	bool sendUSSDSynchronous(char *ussdCommand, char *resultcode, char *response);

    /** Cancel USSD Session
     *  @returns
     *      true on success cancel active session
     *      false on error or because no active session
     */
	bool cancelUSSDSession(void);

//////////////////////////////////////////////////////
/// DFRobot_SIM808
//////////////////////////////////////////////////////  
   /**  Connect the DFRobot_SIM808 module to the network.
     *  @return true if connected, false otherwise
     */
	 
    bool join(const __FlashStringHelper *apn = 0, const __FlashStringHelper *userName = 0, const __FlashStringHelper *passWord = 0);

    /** Disconnect the DFRobot_SIM808 module from the network
     *  @returns
     */
    void disconnect(void);
    
    /** Open a tcp/udp connection with the specified host on the specified port
     *  @param socket an endpoint of an inter-process communication flow of DFRobot_SIM808 module,for SIM900 module, it is in [0,6]
     *  @param ptl protocol for socket, TCP/UDP can be choosen
     *  @param host host (can be either an ip address or a name. If a name is provided, a dns request will be established)
     *  @param port port
     *  @param timeout wait seconds till connected
     *  @param chartimeout wait milliseconds between characters from DFRobot_SIM808 module
     *  @returns true if successful
     */
    bool connect(Protocol ptl, const char * host, int port, int timeout = 2 * DEFAULT_TIMEOUT, int chartimeout = 2 * DEFAULT_INTERCHAR_TIMEOUT);
	bool connect(Protocol ptl, const __FlashStringHelper *host, const __FlashStringHelper *port, int timeout = 2 * DEFAULT_TIMEOUT, int chartimeout = 2 * DEFAULT_INTERCHAR_TIMEOUT);

    /** Check if a tcp link is active
     *  @returns true if successful
     */
    bool is_connected(void);
	
	/** Close a tcp connection
     *  @returns true if successful
     */
    bool close(void);
	
    /** check if DFRobot_SIM808 module is readable or not
     *  @returns true if readable
     */
    int readable(void);

    /** wait a few time to check if DFRobot_SIM808 module is readable or not
     *  @param socket socket
     *  @param wait_time time of waiting
     */
    int wait_readable(int wait_time);

    /** wait a few time to check if DFRobot_SIM808 module is writeable or not
     *  @param socket socket
     *  @param wait_time time of waiting
     */
    int wait_writeable(int req_size);

    /** send data to socket
     *  @param socket socket
     *  @param str string to be sent
     *  @param len string length
     *  @returns return bytes that actually been send
     */
    int send(const char * str, int len);

    /** read data from socket
     *  @param socket socket
     *  @param buf buffer that will store the data read from socket
     *  @param len string length need to read from socket
     *  @returns bytes that actually read
     */
    int recv(char* buf, int len);

    /** Enables the selected software serial port to listen
     *  @returns none
     */
    void listen(void);
	
    /** Tests to see if requested software serial port is actively listening.
     *  @returns none
     */
    bool isListening(void);

    /** convert the host to ip
     *  @param host host ip string, ex. 10.11.12.13
     *  @param ip long int ip address, ex. 0x11223344
     *  @returns true if successful
     */
    //NOT USED bool gethostbyname(const char* host, uint32_t* ip); 
    
    char* getIPAddress();
    unsigned long getIPnumber();	
    bool getLocation(const __FlashStringHelper *apn, float *longitude, float *latitude);
	
	//Open or Close GPS
	bool  attachGPS();
	bool  detachGPS();
	
     // Parse a (potentially negative) number with up to 2 decimal digits -xxxx.yy
	 
	void getTime(uint32_t time);
	void getDate(uint32_t data);  
	int32_t parseDecimal(const char *term);   
	
	
	//parser Serial data
	bool  parseGPRMC(char *gpsbuffer);
	bool  getGPRMC();
	
	//get GPS signal
	bool  getGPS(); 
	
	
	 SoftwareSerial *gprsSerial;
	 HardwareSerial *hgprsSerial;
	Stream *sgprsSerial;
	
public:
	struct gspdata{
		uint16_t year;
		uint8_t month;
		uint8_t day;
		uint8_t hour;
		uint8_t minute;
		uint8_t second;
		uint8_t centisecond;
		float lat;
		float lon;
		float speed_kph;
		float heading;
		float altitude;
	}GPSdata;

private:
	byte serialFlag;
    bool checkSIMStatus(void);
    uint32_t str_to_ip(const char* str);
    static DFRobot_SIM808* inst;
    uint32_t _ip;
    char ip_string[16]; //XXX.YYY.ZZZ.WWW + \0
};
#endif
