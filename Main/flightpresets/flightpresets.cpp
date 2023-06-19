#include "FlightPresets.h"

void FlightPresets::setSpeed(unsigned int speed) {
  this->speed = speed;
}

void FlightPresets::ff() {
  vbl = vbr = speed;
  vfl = vfr = speed * 3/4;
}

void FlightPresets::bb() {
  vfl = vfr = speed;
  vbl = vbr = speed * 3/4;
}

void FlightPresets::ll() {
  vfr = vbr = speed;
  vbl = vbr = speed * 3/4;
}

void FlightPresets::rr() {
  vfl = vbl = speed;
  vfr = vbr = speed * 3/4;
}

void FlightPresets::fl() {
  vbr = speed;
  vfr = vbl = speed * 3/4;
  vfl = speed * 2/4;
}

void FlightPresets::fr() {
  vbl = speed;
  vfl = vbr = speed * 3/4;
  vfr = speed * 2/4;
}

void FlightPresets::bl() {
  vfr = speed;
  vfl = vbr = speed * 3/4;
  vbl = speed * 2/4;
}

void FlightPresets::br() {
  vfl = speed;
  vfr = vbl = speed * 3/4;
  vbr = speed * 2/4;
}

void FlightPresets::uu() {
  vfl = vfr = vbl = vbr = speed;
}

void FlightPresets::dd() {
  vfl = vfr = vbl = vbr = speed;
}

void FlightPresets::uff() {
  vbl = vbr = speed;
  vfl = vfr = speed * 3/4;
}

void FlightPresets::ubb() {
  vfl = vfr = speed;
  vbl = vbr = speed * 3/4;
}

void FlightPresets::ull() {
  vfr = vbr = speed;
  vfl = vbl = speed * 3/4;
}

void FlightPresets::urr() {
  vfl = vbl = speed;
  vfr = vbr = speed * 3/4;
}

void FlightPresets::dff() {
  vbl = vbr = speed * 2/4;
  vfl = vfr = speed * 1/4;
}

void FlightPresets::dbb() {
  vfl = vfr = speed * 2/4;
  vbl = vbr = speed * 1/4;
}

void FlightPresets::dll() {
  vfr = vbr = speed * 2/4;
  vfl = vbl = speed * 1/4;
}

void FlightPresets::drr() {
  vfl = vbl = speed * 2/4;
  vfr = vbr = speed * 1/4;
}

void FlightPresets::ufl() {
  vfr = vbl = vbr = speed;
  vfl = speed * 3/4;
}

void FlightPresets::ufr() {
  vfl = vbl = vbr = speed;
  vfr = speed * 3/4;
}

void FlightPresets::ubl() {
  vfl = vfr = vbr = speed;
  vbl = speed * 3/4;
}

void FlightPresets::ubr() {
  vfl = vfr = vbl = speed;
  vbr = speed * 3/4;
}

void FlightPresets::dfl() {
  vfr = vbl = vbr = speed * 2/4;
  vfl = speed * 1/4;
}

void FlightPresets::dfr() {
  vfl = vbl = vbr = speed * 2/4;
  vfr = speed * 1/4;
}

void FlightPresets::dbl() {
  vfl = vfr = vbr = speed * 2/4;
  vbl = speed * 1/4;
}

void FlightPresets::dbr() {
  vfl = vfr = vbl = speed * 2/4;
  vbr = speed * 1/4;
}
