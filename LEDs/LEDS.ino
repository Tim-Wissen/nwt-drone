// Pin-Definitionen für die LEDs
const int fl_LED = 3;  // Pin für vorne links
const int fr_LED = 5;  // Pin für vorne rechts
const int bl_LED = 6;  // Pin für hinten links
const int br_LED = 9;  // Pin für hinten rechts

void setup() {
  pinMode(fl_LED, OUTPUT);  // Pin für vorne links als Ausgang festlegen
  pinMode(fr_LED, OUTPUT);  // Pin für vorne rechts als Ausgang festlegen
  pinMode(bl_LED, OUTPUT);  // Pin für hinten links als Ausgang festlegen
  pinMode(br_LED, OUTPUT);  // Pin für hinten rechts als Ausgang festlegen
}

void loop() {
  // Beispielhafte Werte für die Helligkeit der LEDs
  int fl = 120;  // Helligkeit von vorne links
  int fr = 200;  // Helligkeit von vorne rechts
  int bl = 50;   // Helligkeit von hinten links
  int br = 255;  // Helligkeit von hinten rechts

  leuchten_steuerung(fl, fr, bl, br);

  delay(1000);  // Eine Sekunde warten, bevor die LEDs aktualisiert werden
}


void steerLED(){
    analogWrite(fl_LED, fl);
    analogWrite(fr_LED, fr);
    analogWrite(bl_LED, bl);
    analogWrite(br_LED, br);
}