/*!
 * @file  sim808.h
 * @brief  A library for DFRobot's SIM808 GPS/GPRS/GSM Shield
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [Jason](jason.ling@dfrobot.com)
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-02-08
 * @url  https://github.com/DFRobot/DFRobot_SIM808
 */
#include "sim808.h"

//SoftwareSerial *serialSIM808 = NULL;

Stream *serialSIM808 = NULL;

/*
void  sim808_init(void * uart_device, uint32_t baud)
{
    serialSIM808 = (SoftwareSerial*)uart_device;
	  serialSIM808->begin(baud);
}

*/

void  sim808_init(void * uart_device, char num)
{
    if(num)
	    serialSIM808 = (HardwareSerial*)uart_device;
	else{
        #if !defined(ESP32)
		serialSIM808 = (SoftwareSerial*)uart_device;
        #endif
    }
}


int sim808_check_readable()
{
    return serialSIM808->available();
}

int sim808_wait_readable (int wait_time)
{
    unsigned long timerStart;
    int dataLen = 0;
    timerStart = millis();
    while((unsigned long) (millis() - timerStart) > wait_time * 1000UL) {
        delay(500);
        dataLen = sim808_check_readable();
        if(dataLen > 0){
            break;
        }
    }
    return dataLen;
}

void sim808_flush_serial()
{
    while(sim808_check_readable()){
        serialSIM808->read();
    }
}

void sim808_read_buffer(char *buffer, int count, unsigned int timeout, unsigned int chartimeout)
{
    int i = 0;
    unsigned long timerStart, prevChar;
    timerStart = millis();
    prevChar = 0;
    while(1) {
        while (sim808_check_readable()) {
            char c = serialSIM808->read();
            prevChar = millis();
            buffer[i++] = c;
            if(i >= count)break;
        }
        if(i >= count)break;
        if ((unsigned long) (millis() - timerStart) > timeout * 1000UL) {
            break;
        }
        //If interchar Timeout => return FALSE. So we can return sooner from this function. Not DO it if we dont recieve at least one char (prevChar <> 0)
        if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)) {
            break;
        }
    }
}

void sim808_clean_buffer(char *buffer, int count)
{
    for(int i=0; i < count; i++) {
        buffer[i] = '\0';
    }
}

//HACERR quitar esta funcion ?
void sim808_send_byte(uint8_t data)
{
	serialSIM808->write(data);
}

void sim808_send_char(const char c)
{
	serialSIM808->write(c);
}

void sim808_send_cmd(const char* cmd)
{
  for(uint16_t i=0; i<strlen(cmd); i++)
    {
        sim808_send_byte(cmd[i]);
    }
}

void sim808_send_cmd(const __FlashStringHelper* cmd)
{
  int i = 0;
  const char *ptr = (const char *) cmd;
  while (pgm_read_byte(ptr + i) != 0x00) {
    sim808_send_byte(pgm_read_byte(ptr + i++));
  }
}

void sim808_send_cmd_P(const char* cmd)
{
  while (pgm_read_byte(cmd) != 0x00)
    sim808_send_byte(pgm_read_byte(cmd++));
}

boolean sim808_send_AT(void)
{
    return sim808_check_with_cmd(F("AT\r\n"),"OK",CMD);
}

void sim808_send_End_Mark(void)
{
    sim808_send_byte((char)26);
}

boolean sim808_wait_for_resp(const char* resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
    int len = strlen(resp);
    int sum = 0;
    unsigned long timerStart, prevChar;    //prevChar is the time when the previous Char has been read.
    timerStart = millis();
    prevChar = 0;
    while(1) {
        if(sim808_check_readable()) {
            char c = serialSIM808->read();
            prevChar = millis();
            sum = (c==resp[sum]) ? sum+1 : 0;
            if(sum == len)break;
        }
        if ((unsigned long) (millis() - timerStart) > timeout * 1000UL) {
            return false;
        }
        //If interchar Timeout => return FALSE. So we can return sooner from this function.
        if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)) {
            return false;
        }

    }
    //If is a CMD, we will finish to read buffer.
    if(type == CMD) sim808_flush_serial();
    return true;
}


boolean sim808_check_with_cmd(const char* cmd, const char *resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
    sim808_send_cmd(cmd);
    return sim808_wait_for_resp(resp,type,timeout,chartimeout);
}

//HACERR que tambien la respuesta pueda ser FLASH STRING
boolean sim808_check_with_cmd(const __FlashStringHelper* cmd, const char *resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
    sim808_send_cmd(cmd);
    return sim808_wait_for_resp(resp,type,timeout,chartimeout);
}
