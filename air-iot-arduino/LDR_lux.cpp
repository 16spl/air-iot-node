#include "LDR_lux.h"
#include "Arduino.h"

LDR::LDR(uint8_t pin){
  _pin = pin;
}

float LDR::LDRResVoltage(){
  int val = analogRead(_pin);
  return (float)val / 1024. * 5;
}

float LDR::LDRResistance(){
  float resVolt = LDRResVoltage();
  return (5-resVolt) / resVolt * RESISTANCE;
}

int LDR::getLux(){
  return (int)((1.25*pow(10, LUX_INTERSECT)) * pow(LDRResistance(), LUX_SLOPE));
}

