#ifndef MQ135_h
#define MQ135_h
#include "Arduino.h"


// MQ135 sensorin vastus, ohmeina
//#define RLOAD 9600
// Kalibrointiin käytettävä arvo
#define RZERO 64000
// CO2 konsentraatiokäyrän arvot
#define PARA 116.6020682
#define PARB 2.769034857

// Lämpökorjausparametrit, otettu MQ135 datasheetistä
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

// Ulkoilman nominaali PPM
#define ATMOCO2 397.13


class MQ135 {
  private:
    uint8_t _pin;
    uint16_t _RLOAD;
  public:
    MQ135(uint8_t pin, uint16_t RLOAD);
    float getResistance();
    float getRZero();
    float getPPM();
};
#endif
