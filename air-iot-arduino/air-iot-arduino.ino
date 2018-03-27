/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMEP280 Breakout 
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required 
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <dht.h>
#include <OneWire.h>
#include <EEPROM.h>


dht DHT;

#define DHT11_PIN 7
#define DEVICE_ID "air-3" //TODO Generate automatically or load from EEPROM

//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
OneWire ds(4);
byte addr[8];
char sID[9];

void tempSearch(){
  byte i;
  bool done = false;
  while(!done){
    if ( !ds.search(addr)) {
      Serial.println("No more addresses.");
      Serial.println();
      ds.reset_search();
      delay(250);
      return;
    }
    
    Serial.print("Unique ID = ");
    for( i = 0; i < 8; i++) {
      Serial.write(' ');
      Serial.print(addr[i], HEX);
    }
    Serial.println();
    if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
    }else{
      done = !done;
    }
  }
}

float readTemp() { //TODO: tämä syö addressin ja hakee sen perusteella lämpötilan
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  return (float)raw / 16.0;
}

void setup() {
  Serial.begin(9600);
  while(!Serial){;}
  for(int i = 0; i<8; i++){
    sID[i] = EEPROM.read(i);
  }
  Serial.print("Arduino ID:");
  Serial.println(sID);
  Serial.println("Sensors Initializing");
  delay(20);
  tempSearch();
  delay(20);
  Serial.println("Done"); //!IMPORTANT! Python script detects this and starts to send data

}
void loop() {
  int comd = 0;
  while(Serial.available() > 0){
    comd = Serial.read();
    Serial.write(comd);
  }
  switch (comd){
    case 10:
    int chk = DHT.read11(DHT11_PIN);
    Serial.print("Device_ID ");
    Serial.print(DEVICE_ID);
    Serial.print(" Temperature ");
    Serial.print(readTemp()); //readTemp lukee lämmön, tais palauttaa floatin
    Serial.print(" Humidity ");
    Serial.println(DHT.humidity);
    
      break;
  }
  delay(200);
}