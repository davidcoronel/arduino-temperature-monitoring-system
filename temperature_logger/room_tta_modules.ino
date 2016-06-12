// PINS 6,7,8

DHT dhts[] = {
  DHT (6, DHT11),
  DHT (7, DHT11),
  DHT (8, DHT11)
};



void room_tta_modules_setup(){
  dhts[0].begin();
  dhts[1].begin();
  dhts[2].begin();
}


String room_tta_modules_get_temperatures(){
  
  String tta_string = "";
  for(int i = 0 ; i<(sizeof(dhts)); i++){
       tta_string += dhts[i].readTemperature();
       tta_string += ",";
       tta_string += dhts[i].readHumidity();
       if(i<sizeof(dhts)-1){
          tta_string += ",";
       }
  }
#ifdef DEBUG
  Serial.println(tta_string);
#endif
  return tta_string;
}
