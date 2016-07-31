// PINS 6,7,8

DHT dhts[] = {
  DHT (6, DHT11),
  DHT (7, DHT11),
  DHT (8, DHT11)
};



void room_tta_modules_setup(){
#ifdef DEBUG  
  Serial.print(F("Initializing Room Temperature MODULES: "));
#endif
  dhts[0].begin();
  dhts[1].begin();
  dhts[2].begin();
}



float room_tta(int i){
  return dhts[i].readTemperature();
}

float room_hum(int i){
  return dhts[i].readHumidity();
}

/*
String room_tta_modules_get_temperatures(){

  String tta_string = "";
  for(int i = 0 ; i<(sizeof(dhts)); i++){
       tta_string += dhts[i].readTemperature();
       tta_string += F(",");
       tta_string += dhts[i].readHumidity();
       if(i<sizeof(dhts)-1){
          tta_string += F(",");
       }
  }
#ifdef DEBUG
  //Serial.println(tta_string);
#endif
  return tta_string;
}
*/
