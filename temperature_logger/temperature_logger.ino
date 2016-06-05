#include <DS3231.h>

#include <SPI.h>
#include <SD.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define DEBUG 1

void setup(){

#ifdef DEBUG  
  Serial.begin(115200);
#endif

  rtc_module_setup();
  sd_module_setup();
  water_tta_modules_setup();
  //flow_module_setup();
  //room_tta_modules_setup();
  //pyra_module_setup();
}

void loop(){
  String dataString = "";
  
  //poll rtc
  dataString = rtc_get_time();
  dataString += ",";
  //poll tta
  dataString += water_tta_get_temperatures();
  dataString += ",";
  
#ifdef DEBUG
  Serial.println(dataString);
#endif
  
  
  //poll flow
  
  //poll room_tta
  
  //poll pyra
  
  //write to sd
  writeToSd(dataString);

  delay(1000);
}



