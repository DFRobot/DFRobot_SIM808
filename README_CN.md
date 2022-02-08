# DFRobot_ENS160
* [English Version](./README.md)

ENS160是一款数字多气体传感器解决方案, 基于金属氧化物(MOX)技术, 带有四个MOX传感器元件。
每个传感器元件都有独立的热板控制, 以检测各种气体, 如挥发性有机化合物(VOCs), 包括乙醇, 甲苯, 以及氢和二氧化氮, 具有优越的选择性和准确性。
对于室内空气质量应用, ENS160支持智能算法, 数字化处理芯片上的原始传感器测量。
这些算法计算二氧化碳当量, TVOC, 空气质量指数(AQIs), 湿度和温度补偿, 以及基线管理-全部在芯片上!
此外, 一个开发选项可用于从每个传感器元件数字输出原始传感器测量值, 以进行定制。
LGA封装设备包括一个SPI或I²C从接口与单独的VDDIO与主主机处理器通信。
ENS160是一种经过验证和免维护的技术, 专为高容量和可靠性而设计。

![产品实物图](./resources/images/ENS160.png)


## 产品链接 (https://www.dfrobot.com.cn/)
    SKU：SEN0514/SEN0515

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)


## 概述

* TrueVOC™空气质量检测, 具有行业领先的纯度和稳定性, 提供多种输出, 如eCO21, TVOC和aqis2, 符合全球iaq3信号标准
* 独立传感器加热器控制最高选择性(如乙醇, 甲苯, 丙酮, NO2)和突出的背景辨别能力
* 对硅氧烷和湿度的免疫力
* 无麻烦的片上加热器驱动器控制和数据处理-不需要外部库-没有主板cpu性能影响
* 低功耗应用程序中断阈值
* 工作范围广:温度:-40至+85°C;湿度:5 ~ 95%5;VDD: 1.71 to 1.98V;VDDIO 1.71至3.6V
* 该库支持SPI/I2C通信。


## 库安装

要使用这个库, 首先下载库文件, 将其粘贴到\Arduino\libraries目录中, 然后打开示例文件夹并在文件夹中运行演示。


## 方法

```C++

  /**
   * @fn begin
   * @brief 初始化函数
   * @return int类型, 表示返回初始化的状态
   * @retval 0 NO_ERROR
   * @retval -1 ERR_DATA_BUS
   * @retval -2 ERR_IC_VERSION
   */
  virtual int begin(void);

  /**
   * @fn setPWRMode
   * @brief 设置电源模式
   * @param mode 可配置的电源模式:
   * @n       ENS160_SLEEP_MODE: 深度睡眠模式(低功耗待机)
   * @n       ENS160_IDLE_MODE: 空闲模式(低功耗)
   * @n       ENS160_STANDARD_MODE: 标准气体传感模式
   * @return None
   */
  void setPWRMode(uint8_t mode);

  /**
   * @fn setINTMode
   * @brief 中断配置(INT)
   * @param mode 需要设置的中断模式,下列模式经过或运算后得到mode:
   * @n       中断设置(有新数据时产生中断): eINTModeDIS-禁用中断, eINTModeEN-启用中断
   * @n       中断引脚输出驱动模式: eINTPinOD-开漏输出, eINTPinPP-推挽输出
   * @n       中断引脚有效电平: eINTPinActiveLow-低电平有效, eINTPinActiveHigh-高电平有效
   * @return None
   */
  void setINTMode(uint8_t mode);

  /**
   * @fn setTempAndHum
   * @brief 用户将环境温度和相对湿度写入ENS160, 用于气体测量数据的校准补偿。
   * @param ambientTemp 用于补偿的当前环境温度, float类型, 单位: C
   * @param relativeHumidity 用于补偿的当前环境温度, float类型, 单位: %rH
   * @return None
   */
  void setTempAndHum(float ambientTemp, float relativeHumidity);

  /**
   * @fn getENS160Status
   * @brief 这个API获取传感器的运行状态信息
   * @return 运行状态:
   * @n        eNormalOperation: Normal operation; 
   * @n        eWarmUpPhase: Warm-Up phase; 
   * @n        eInitialStartUpPhase: Initial Start-Up phase; 
   * @n        eInvalidOutput: Invalid output
   */
  uint8_t getENS160Status(void);

  /**
   * @fn getAQI
   * @brief 获取根据UBA计算出的空气质量指数
   * @return 返回值范围为: 1-5(对应优秀, 良好, 中等, 贫困, 不健康这五个等级)
   */
  uint8_t getAQI(void);

  /**
   * @fn getTVOC
   * @brief 获取总挥发性有机化合物(TVOC)的浓度
   * @return 返回值范围为: 0–65000, 单位: ppb
   */
  uint16_t getTVOC(void);

  /**
   * @fn getECO2
   * @brief 获取根据检测到的VOCs和氢报告计算出的二氧化碳当量浓度(eCO2 – Equivalent CO2)
   * @return 返回值范围为: 400–65000, 单位: ppm
   * @note 分为五个等级: Excellent(400 - 600), Good(600 - 800), Moderate(800 - 1000), 
   * @n                  Poor(1000 - 1500), Unhealthy(> 1500)
   */
  uint16_t getECO2(void);

```


## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP8266 |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
FireBeetle-M0      |      √       |              |             |
Micro:bit          |      √       |              |             |


## 历史

- 2021/10/27 - 1.0.0 版本


## 创作者

Written by qsjhyy(yihuan.huang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

