/*
SD card datalogger, SPI communication 

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4


RTC(Real time clock),I2C communication 
SCL - A5
SDL - A4

*/



#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

const int chipSelect = 4;

String data;

void setup () {
    Serial.begin(9600);
    
    //RTC Initializing
    Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

//SD card Initializing
   Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
}
void loop () {
    DateTime now = RTC.now();
    data="Date:";
    data+= String(now.year(), DEC);
    data+="/";
    data+=String(now.month(), DEC);
    data+="/";
    data+=String(now.day(), DEC);
    

    data+=", Time:";
    
    data+=String(now.hour(), DEC);
    data+="-";
    data+=String(now.minute(), DEC);
    data+="-";
    data+=String(now.second(), DEC);

    data+=", Current:";
    int w=20;
    data+=String(w);
    data+=",";
    
    Serial.print(data);
    Serial.println(); 
    delay(1000);




    File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
    Serial.println(data);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
