#include <DS3231.h>

#include <SPI.h>
#include <SD.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <DHT.h>


#define DEBUG 1

void setup(){

#ifdef DEBUG  
  Serial.begin(115200);
#endif

  rtc_module_setup();
  sd_module_setup();
  water_tta_modules_setup();
  flow_modules_setup();
  room_tta_modules_setup();
  //pyra_module_setup();
}

unsigned long oldTime;
int frequency = 1000;

void loop(){

  if((millis() - oldTime) > frequency){
    String dataString = "";
    
    //poll rtc
    dataString = rtc_get_time();
    dataString += ",";
    //poll tta
    dataString += water_tta_get_temperatures();
    dataString += ",";
    
    //poll flow
    dataString += flow_modules_get();
    dataString += ",";
    
    //poll room_tta
    dataString += room_tta_modules_get_temperatures();
    dataString += ",";
    
    //poll pyra
      
#ifdef DEBUG
    Serial.println(dataString);
#endif
    
    //write to sd
    writeToSd(dataString);

  }
  //delay(1000); //change to something like if((millis() - oldTime) > 1000) 
}



