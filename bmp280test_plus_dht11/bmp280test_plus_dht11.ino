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

dht DHT;

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10
#define DHT11_PIN 7
#define DEVICE_ID "air-2"

//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);


void setup() {
  Serial.begin(9600);
  while(!Serial){;}
  
  Serial.println(F("Sensors Initializing"));
  

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
    //Serial.print(bme.readTemperature()-1.2);    

    Serial.print(" Humidity ");
    Serial.println(DHT.humidity);
    
      break;
  }
  delay(200);
}
