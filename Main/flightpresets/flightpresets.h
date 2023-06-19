#ifndef FlightPresets_h
#define FlightPresets_h

#include <Arduino.h>

class FlightPresets {
public:
  int vfl, vfr, vbl, vbr;  // Member-Variablen für die Motorgeschwindigkeiten

  FlightPresets() {
    vfl = vfr = vbl = vbr = 0;  // Initialisierung der Motorgeschwindigkeiten
  }

  void ff();
  void bb();
  void ll();
  void rr();
  void fl();
  void fr();
  void bl();
  void br();
  void uu();
  void dd();
  void uff();
  void ubb();
  void ull();
  void urr();
  void dff();
  void dbb();
  void dll();
  void drr();
  void ufl();
  void ufr();
  void ubl();
  void ubr();
  void dfl();
  void dfr();
  void dbl();
  void dbr();

  void setSpeed(unsigned int speed);
  
  void printSpeed(){
    Serial.println(speed);
  }

private:
  unsigned int speed;
};

#endif
