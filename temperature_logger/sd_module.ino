// PINS 4,11,12,13

/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

//#include <SPI.h>
//#include <SD.h>

const int chipSelect = 4;

void sd_module_setup() {
  // Open serial communications and wait for port to open:
  //Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

#ifdef DEBUG
  Serial.print(F("Initializing SD card..."));
#endif

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
#ifdef DEBUG
    Serial.println("Card failed, or not present");
#endif
    // don't do anything more:
    return;
  }
#ifdef DEBUG
  Serial.println(F("card initialized."));
#endif
}

void writeToSd(String dataString){
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
#ifdef DEBUG
    Serial.println(dataString);
#endif
  }
  // if the file isn't open, pop up an error:
  else {
#ifdef DEBUG
    Serial.println(F("error opening datalog.txt"));
#endif
  }
}






