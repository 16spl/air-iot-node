#include "MQ135.h"
#include "Arduino.h"

MQ135::MQ135(uint8_t pin, uint16_t RLOAD){
  _pin = pin;
  _RLOAD = RLOAD;
}


float MQ135::getResistance() {
  int val = analogRead(_pin);
  return ((1023./(float)val-1) * _RLOAD);
}

float MQ135::getRZero(){
  return getResistance() * pow((ATMOCO2/PARA), (1/PARB));
}

float MQ135::getPPM(){
  return PARA * pow(getResistance()/RZERO, -PARB);
}

