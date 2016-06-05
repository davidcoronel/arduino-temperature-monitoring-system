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
#include <OneWire.h>

//Get DallasTemperature Library here:  http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library
#include <DallasTemperature.h>

/*-----( Declare Constants and Pin Numbers )-----*/
#define ONE_WIRE_BUS_PIN 2

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

DeviceAddress Probe00 = { 0x28, 0xFF, 0x2D, 0xF5, 0x64, 0x15, 0x02, 0x38 }; 
DeviceAddress Probe01 = { 0x28, 0xFF, 0xE6, 0xD6, 0x64, 0x15, 0x01, 0x70 }; 
DeviceAddress Probe02 = { 0x28, 0xFF, 0xCA, 0xB6, 0x64, 0x15, 0x02, 0xDB };
DeviceAddress Probe03 = { 0x28, 0xFF, 0xDB, 0xE9, 0x64, 0x15, 0x01, 0xCA }; 
DeviceAddress Probe04 = { 0x28, 0xFF, 0xC4, 0xB0, 0x64, 0x15, 0x03, 0x2E }; 
DeviceAddress Probe05 = { 0x28, 0xFF, 0x87, 0xDE, 0x64, 0x15, 0x01, 0xB0 };
DeviceAddress Probe06 = { 0x28, 0xFF, 0xE7, 0xB7, 0x64, 0x15, 0x01, 0xA2 }; 
DeviceAddress Probe07 = { 0x28, 0xFF, 0x1E, 0xDD, 0x64, 0x15, 0x01, 0x7C }; 

void setup()   /****** SETUP: RUNS ONCE ******/
{
  // start serial port to show results
  Serial.begin(9600);
  Serial.print("Initializing Temperature Control Library Version ");
  Serial.println(DALLASTEMPLIBVERSION);
  
  // Initialize the Temperature measurement library
  sensors.begin();
  
  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(Probe00, 10);
  sensors.setResolution(Probe01, 10);
  sensors.setResolution(Probe02, 10);
  sensors.setResolution(Probe03, 10);
  sensors.setResolution(Probe04, 10);
  sensors.setResolution(Probe05, 10);
  sensors.setResolution(Probe06, 10);
  sensors.setResolution(Probe07, 10);

}//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  delay(1000);
  Serial.println();
  Serial.print("Number of Devices found on bus = ");  
  Serial.println(sensors.getDeviceCount());   
  Serial.print("Getting temperatures... ");  
  Serial.println();   
  
  // Command all devices on bus to read temperature  
  sensors.requestTemperatures();  
  
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

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
void printTemperature(DeviceAddress deviceAddress)
{

float tempC = sensors.getTempC(deviceAddress);

   if (tempC == -127.00) 
   {
   Serial.print("Error getting temperature  ");
   } 
   else
   {
   Serial.print("C: ");
   Serial.print(tempC);
   Serial.print(" F: ");
   Serial.print(DallasTemperature::toFahrenheit(tempC));
   }
}// End printTemperature
//*********( THE END )***********

