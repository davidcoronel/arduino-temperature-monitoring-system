// PIN 2

/* YourDuino Multiple DS18B20 Temperature Sensors on 1 wire
  Connections:
  DS18B20 Pinout (Left to Right, pins down, flat side toward you)
  - Left   = Ground
  - Center = Signal (Pin 2):  (with 3.3K to 4.7K resistor to +5 or 3.3 )
  - Right  = +5 or +3.3 V

   Questions: terry@yourduino.com 
   V1.01  01/17/2013 ...based on examples from Rik Kretzinger
   
/*-----( Import needed libraries )-----*/
// Get 1-wire Library here: http://www.pjrc.com/teensy/td_libs_OneWire.html
//#include <OneWire.h>

//Get DallasTemperature Library here:  http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library
//#include <DallasTemperature.h>

/*-----( Declare Constants and Pin Numbers )-----*/
#define ONE_WIRE_BUS_PIN 5

/*-----( Declare objects )-----*/
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS_PIN);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*-----( Declare Variables )-----*/
// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

// Color
/* 
DeviceAddress Probe00 = { 0x28, 0xFF, 0x17, 0xBE, 0x64, 0x15, 0x03, 0x2B }; 
DeviceAddress Probe01 = { 0x28, 0xFF, 0x4E, 0xA5, 0x64, 0x15, 0x02, 0xBF }; 
DeviceAddress Probe02 = { 0x28, 0xFF, 0xD8, 0xC2, 0x72, 0x15, 0x01, 0xFB };
*/

DeviceAddress addresses[] = {
  { 0x28, 0xFF, 0x2D, 0xF5, 0x64, 0x15, 0x02, 0x38 },
  { 0x28, 0xFF, 0xE6, 0xD6, 0x64, 0x15, 0x01, 0x70 }, 
  { 0x28, 0xFF, 0xCA, 0xB6, 0x64, 0x15, 0x02, 0xDB },
  { 0x28, 0xFF, 0xDB, 0xE9, 0x64, 0x15, 0x01, 0xCA },
  { 0x28, 0xFF, 0xC4, 0xB0, 0x64, 0x15, 0x03, 0x2E },
  { 0x28, 0xFF, 0x87, 0xDE, 0x64, 0x15, 0x01, 0xB0 },
  { 0x28, 0xFF, 0xE7, 0xB7, 0x64, 0x15, 0x01, 0xA2 },
  { 0x28, 0xFF, 0x1E, 0xDD, 0x64, 0x15, 0x01, 0x7C },
  { 0x28, 0xFF, 0x09, 0x5D, 0xA8, 0x15, 0x01, 0x60 },
  { 0x28, 0xFF, 0x52, 0x81, 0xA8, 0x15, 0x03, 0x2A },
  { 0x28, 0xFF, 0xCD, 0x7B, 0xA8, 0x15, 0x03, 0x98 },
  { 0x28, 0xFF, 0xCA, 0xB6, 0x64, 0x15, 0x02, 0xDB },
  { 0x28, 0xFF, 0xFF, 0x8E, 0x72, 0x15, 0x02, 0x42 }
}; 


void water_tta_modules_setup()   /****** SETUP: RUNS ONCE ******/
{
  // start serial port to show results
  //Serial.begin(9600);
#ifdef DEBUG  
  Serial.print("Initializing Water Temperature MODULES: ");
  Serial.println(DALLASTEMPLIBVERSION);
#endif
  
  // Initialize the Temperature measurement library
  sensors.begin();
  
  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  for(int i = 0 ; i<sizeof(addresses)-1; i++){
    sensors.setResolution(addresses[i], 10);
  }

}//--(end setup )---

void water_tta_modules_loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  delay(1000);
  Serial.println();
  Serial.print("Number of Devices found on bus = ");  
  Serial.println(sensors.getDeviceCount());   
  Serial.print("Getting temperatures... ");  
  Serial.println();   
  
  // Command all devices on bus to read temperature  
  sensors.requestTemperatures();  

  /*
  Serial.print("Probe 00 temperature is:   ");
  printTemperature(Probe00);
  Serial.println();

  Serial.print("Probe 01 temperature is:   ");
  printTemperature(Probe01);
  Serial.println();

  Serial.print("Probe 02 temperature is:   ");
  printTemperature(Probe02);
  Serial.println();
 
  Serial.print("Probe 03 temperature is:   ");
  printTemperature(Probe03);
  Serial.println();

  Serial.print("Probe 04 temperature is:   ");
  printTemperature(Probe04);
  Serial.println();

  Serial.print("Probe 05 temperature is:   ");
  printTemperature(Probe05);
  Serial.println();
 
  Serial.print("Probe 06 temperature is:   ");
  printTemperature(Probe06);
  Serial.println();

  Serial.print("Probe 07 temperature is:   ");
  printTemperature(Probe07);
  Serial.println();
  */
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
void printTemperature(DeviceAddress deviceAddress)
{

float tempC = sensors.getTempC(deviceAddress);

   if (tempC == -127.00){
#ifdef DEBUG
    Serial.print("Error getting temperature  ");
#endif
   }else{
#ifdef DEBUG
     Serial.print("C: ");
     Serial.print(tempC);
     Serial.print(" F: ");
     Serial.print(DallasTemperature::toFahrenheit(tempC));
#endif
  }
}// End printTemperature
//*********( THE END )***********


String water_tta_get_temperatures(){
  String tta_string = "";
  sensors.requestTemperatures();  
  for(int i = 0 ; i<(sizeof(addresses)/8); i++){
       tta_string += sensors.getTempC(addresses[i]);
       if(i<sizeof(addresses)-1){
          tta_string += ",";
       }
  }
  return tta_string;
}

