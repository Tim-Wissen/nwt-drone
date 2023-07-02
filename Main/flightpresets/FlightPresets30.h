#ifndef flightpresets_h
#define flightpresets_h

#include <Arduino.h>

class FlightPresets {
public:
    FlightPresets();

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

private:
    unsigned int speed;
    double fl;
    double fr;
    double bl;
    double br;
    bool clockwise;
};

// FlightPresets::FlightPresets() {
//     speed = 0;
//     fl = 0.0;
//     fr = 0.0;
//     bl = 0.0;
//     br = 0.0;
//     clockwise = false;
// }

void FlightPresets::ff() {
    bl = br = speed;
    fl = fr = speed * 3/4;
}

void FlightPresets::bb() {
    fl = fr = speed;
    bl = br = speed * 3/4;
}

void FlightPresets::ll() {
    fr = br = speed;
    bl = br = speed * 3/4;
}

void FlightPresets::rr() {
    fl = bl = speed;
    fr = br = speed * 3/4;
}

void FlightPresets::fl() {
    br = speed;
    fr = bl = speed * 3/4;
    fl = speed * 2/4;
}

void FlightPresets::fr() {
    bl = speed;
    fl = br = speed * 3/4;
    fr = speed * 2/4;
}

void FlightPresets::bl() {
    fr = speed;
    fl = br = speed * 3/4;
    bl = speed * 2/4;
}

void FlightPresets::br() {
    fl = speed;
    fr = bl = speed * 3/4;
    br = speed * 2/4;
}

void FlightPresets::uu() {
    fl = fr = bl = br = speed;
}

void FlightPresets::dd() {
    fl = fr = bl = br = speed;
}

void FlightPresets::uff() {
    bl = br = speed;
    fl = fr = speed * 3/4;
}

void FlightPresets::ubb() {
    fl = fr = speed;
    bl = br = speed * 3/4;
}

void FlightPresets::ull() {
    fr = br = speed;
    fl = bl = speed * 3/4;
}

void FlightPresets::urr() {
    fl = bl = speed;
    fr = br = speed * 3/4;
}

void FlightPresets::dff() {
    bl = br = speed * 2/4;
    fl = fr = speed * 1/4;
}

void FlightPresets::dbb() {
    fl = fr = speed * 2/4;
    bl = br = speed * 1/4;
}

void FlightPresets::dll() {
    fr = br = speed * 2/4;
    fl = bl = speed * 1/4;
}

void FlightPresets::drr() {
    fl = bl = speed * 2/4;
    fr = br = speed * 1/4;
}

void FlightPresets::ufl() {
    fr = bl = br = speed;
    fl = speed * 3/4;
}

void FlightPresets::ufr() {
    fl = bl = br = speed;
    fr = speed * 3/4;
}

void FlightPresets::ubl() {
    fl = fr = br = speed;
    bl = speed * 3/4;
}

void FlightPresets::ubr() {
    fl = fr = bl = speed;
    br = speed * 3/4;
}

void FlightPresets::dfl() {
    fr = bl = br = speed * 2/4;
    fl = speed * 1/4;
}

void FlightPresets::dfr() {
    fl = bl = br = speed * 2/4;
    fr = speed * 1/4;
}

void FlightPresets::dbl() {
    fl = fr = br = speed * 2/4;
    bl = speed * 1/4;
}

void FlightPresets::dbr() {
    fl = fr = bl = speed * 2/4;
    br = speed * 1/4;
}

#endif
