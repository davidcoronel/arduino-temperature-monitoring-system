// PINS 4 & 5

// DS3231_Serial_Easy
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my DS3231-library to 
// quickly send time and date information over a serial link
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// DS3231:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//          SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the DS3231 to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

//#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

void rtc_module_setup(){
  // Setup Serial connection
  //Serial.begin(115200);
  
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(22, 9, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(30, 7, 2016);   // Set the date to January 1st, 2014
}

String rtc_get_time(){
  // Send Day-of-Week
  //String currentDayTime = rtc.getDateStr();
  //int currentDateTime = rtc.getUnixTime(rtc.getTime());
  
#ifdef DEBUG  
  //Serial.print("RTC: ");
  // Send date
  //Serial.print(rtc.getDateStr());
  //Serial.print(" -- ");
  // Send time
  //Serial.println(rtc.getTimeStr());
#endif
  String res = rtc.getDateStr() + String(" ") + rtc.getTimeStr();
  return res;
}
