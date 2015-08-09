/*
  ds1307 - Date and time functions using a DS1307 RTC connected
  via I2C and Wire lib using Adafruit DS1307 RTC Breakout and
  Energia.  Requires RTClib.cpp and RTClib.h from Adafruit.

  NOTE: This is a 5V module.  Requires logic level conversion
  to work with LaunchPads.

  Hardware used
  MSP-EXP430F5529
  Addicore Bi-directional Logic Level Converter (4 Channel)
  https://www.addicore.com/Logic-Level-Converter-Bi-Directional-5V-to-3-3V-p/227.htm
  Adafruit DS130 RTC Breakout
  http://www.adafruit.com/product/264

  Tested on the following pins
             
  RTC Pin     Logic Conv   430F5529    
  -------     ----------   --------    
  GND         GND          GND         
  5V          HV           5V         
  SDA         HV1                    
  SCL         HV2  
              LV1          15 (SDA) 
              LV2          14 (SCL)
              LV           3V3
              GND          GND
  
  Frank Milburn
  June 14, 2015
*/
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
  Serial.begin(57600);
  Wire.begin();
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now.unixtime() + 7 * 86400L + 30);
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(3000);
}
