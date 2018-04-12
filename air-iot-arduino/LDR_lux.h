#ifndef LDR_h
#define LDR_h
#include "Arduino.h"

#define LUX_INTERSECT 7.32
#define LUX_SLOPE -1.31
#define RESISTANCE 4700

class LDR {
  private:
    uint8_t _pin;
  public:
    LDR(uint8_t pin);
    float LDRResistance();
    int getLux();
    float LDRResVoltage();
   
};

#endif
