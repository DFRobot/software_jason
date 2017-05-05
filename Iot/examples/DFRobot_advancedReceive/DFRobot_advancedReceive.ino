/*********************************************************************
* DFRobot_advancedReceive.
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:
* The IOT device receives the number 1, turns on the LED, otherwise turns off the LED
* 
* author  :  Jason
* version :  V1.0
* date    :  2017-03-06
**********************************************************************/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Iot.h"

Iot iot;                 

int ledPin = 2;                            //led小灯引脚

SoftwareSerial mySerial(10, 11);         // RX, TX

#define WIFI_SSID       "DFSoftware"       //wifi名称
#define WIFI_PASSWD     "dfrobotsoftware"  //wifi密码
#define IOT_USERNAME    "test"             //物联网账号
#define IOT_PASSWD      "test"             //物联网账号密码

void * eventHandle(const char *data, uint16_t len)
{
  
   switch(atoi(data))                      //将物联网发送字符串转换成数字
    {
      case 0:
        digitalWrite(ledPin,LOW);           //关闭小灯
        break;
      case 1:
        digitalWrite(ledPin,HIGH);          //打开小灯
        break;
      default:break;
    }
  
}

void setup(void)
{ 
  mySerial.begin(38400);
  pinMode(ledPin,OUTPUT);
  iot.setup(mySerial, WIFI_SSID, WIFI_PASSWD, IOT_USERNAME, IOT_PASSWD);
  iot.subscribe("Button", eventHandle);
  iot.start();
}

void loop(void)
{
	iot.loop();
}
