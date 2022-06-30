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
#ifndef __SIM808_H__
#define __SIM808_H__

#include <Arduino.h>
#if !defined(ESP32)
    #include <SoftwareSerial.h>
#endif

#define DEFAULT_TIMEOUT      5   //seconds
#define DEFAULT_INTERCHAR_TIMEOUT   1500   //miliseconds

/**
 * @enum  enum DataType
 * @brief  Data Type, command or data
 */
enum DataType {
    CMD     = 0,
    DATA    = 1,
};

/**
 * @fn sim808_init
 * @brief sim808 initialization
 * @param uart_device  serial ports for communication, supporting hard and soft serial ports
 * @param num  It is used to determine whether the serial port is hard or soft
 * @return None
 */
void sim808_init(void * uart_device, char num );
//void  sim808_init(void * uart_device, uint32_t baud);

/**
 * @fn sim808_check_readable
 * @brief Check whether Sim808 is readable
 * @return Returns the number of bytes currently readable by the SERIAL port of SIM808
 */
int sim808_check_readable(void);

/**
 * @fn sim808_wait_readable
 * @brief Wait until SIM808 becomes readable
 * @param wait_time  Wait time, in seconds
 * @return Returns the number of bytes that SIM808 can read during the wait time, or 0 until the wait time is over
 */
int sim808_wait_readable(int wait_time);

/**
 * @fn sim808_flush_serial
 * @brief sim808 flush serial
 * @return None
 */
void sim808_flush_serial(void);

/**
 * @fn sim808_read_buffer
 * @brief sim808 read buffer
 * @param buffer  The space in which read data is stored
 * @param count  The length of data to read
 * @param timeout  seconds
 * @param chartimeout  miliseconds
 * @return None
 */
void sim808_read_buffer(char* buffer, int count, unsigned int timeout=DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);

/**
 * @fn sim808_clean_buffer
 * @brief clear buffer
 * @param buffer  data buffer
 * @param count  Length of data to clear
 * @return None
 */
void sim808_clean_buffer(char* buffer, int count);

/**
 * @fn sim808_send_byte
 * @brief sim808 send one byte of data
 * @param data  Data to be sent
 * @return None
 */
void sim808_send_byte(uint8_t data);

/**
 * @fn sim808_send_char
 * @brief sim808 send a char data
 * @param c  char data to be sent
 * @return None
 */
void sim808_send_char(const char c);

/**
 * @fn sim808_send_cmd
 * @brief sim808 send a command
 * @param cmd  command data to be sent
 * @return None
 */
void sim808_send_cmd(const char* cmd);
void sim808_send_cmd(const __FlashStringHelper* cmd);

/**
 * @fn sim808_send_cmd_P
 * @brief sim808 send the flash command
 * @param cmd  flash command data to be sent
 * @return None
 */
void sim808_send_cmd_P(const char* cmd);

/**
 * @fn sim808_send_AT
 * @brief sim808 send AT
 * @return true on success, false on error
 */
boolean sim808_send_AT(void);

/**
 * @fn sim808_send_End_Mark
 * @brief sim808 send end mark
 * @return None
 */
void sim808_send_End_Mark(void);

/**
 * @fn sim808_wait_for_resp
 * @brief sim808 wait for response
 * @param resp  Required response, typically "OK"
 * @param type  If is a CMD, we will finish to read buffer.
 * @param timeout  seconds
 * @param chartimeout  miliseconds
 * @return true on success, false on error
 */
boolean sim808_wait_for_resp(const char* resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);

/**
 * @fn sim808_check_with_cmd
 * @brief sim808 send data and wait for a response
 * @param cmd  command data to be sent
 * @param resp  Required response, typically "OK"
 * @param type  If is a CMD, we will finish to read buffer.
 * @param timeout  seconds
 * @param chartimeout  miliseconds
 * @return true on success, false on error
 */
boolean sim808_check_with_cmd(const char* cmd, const char *resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT*5);
boolean sim808_check_with_cmd(const __FlashStringHelper* cmd, const char *resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);

#endif
