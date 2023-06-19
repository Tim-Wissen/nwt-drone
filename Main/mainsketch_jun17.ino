#include <Wire.h>
#include <Arduino.h>
#include <FlightPresets.h>
#include <MPU6050.h>

MPU6050 gyro;                 //Objektinstanz der Klasse 'MPU6050' mit dem Name 'gyro' wird erstellt
FlightPresets drone;          // Objektinstanz der Klasse 'FlightPresets' mit dem Namen 'drone' wird erstellt

const int adrMPU = 0x68;      //Adresse des MPU

const int adrPWR = 0x6B;      //Adresse des Power-Management
const int adrGXOutH = 0x43;   //Adresse GYRO_X_OUT_HIGH (folgende 5 Register bis GYRO_Z_OUT_LOW)

int16_t GXOut;                //Wert GYRO_X_OUT
int16_t GYOut;                //Wert GYRO_Y_OUT
int16_t GZOut;                //Wert GYRO_Z_OUT

int16_t minGX;            //Minimum-Wert von GYRO_X
int16_t maxGX;            //Maximum-Wert von GYRO_X
int16_t minGY;            //Minimum-Wert von GYRO_Y
int16_t maxGY;            //Maximum-Wert von GYRO_Y
int16_t minGZ;            //Minimum-Wert von GYRO_Z
int16_t maxGZ;            //Maximum-Wert von GYRO_Z

int16_t cGX;          //Kalibrierter Wert von GYRO_X
int16_t cGY;          //Kalibrierter Wert von GYRO_Y
int16_t cGZ;          //Kalibrierter Wert von GYRO_Z

int16_t GXF;          //Finaler Wert GYRO_X
int16_t GYF;          //Finaler Wert GYRO_Y
int16_t GZF;          //Finaler Wert GYRO_Z

int t01 = 1000;               //Zeit-Variable 1
int t02 = 0;                  //Zeit-Variable 2

int Bt01 = 100;               //Zeit-Variable 1 -> \Unterprogramme.ino\readGyro(B)

int Dt01 = 0;                 //Zeit Variable 1 -> \Unterprogramme.ino\calibrateGyro(D)
int Dt02 = 100;               //Zeit Variable 2 -> \Unterprogramme.ino\calibrateGyro(D)
int Dt03 = 2000;              //Zeit Variable 3 -> \Unterprogramme.ino\calibrateGyro(D)

bool Dx1 = 0;                 //allg. Variable 1 -> \Unterprogramme.ino\calibrateGyro(D)
bool Dx2 = 0;                 //allg. Variable 2 -> \Unterprogramme.ino\calibrateGyro(D)





void setup() {
  Serial.begin(9600);
  Wire.begin();
}


void loop() {
  startGyro();                // => \Unterprogramme.ino\startGyro(A)
  calibrateGyro();            // => \Unterprogramme.ino\calibrateGyro(D)
  readGyro();                 // => \Unterprogramme.ino\readGyro(B)
  writeGyro();                // => \Unterprogramme.ino\writeGyro(C)
  calculateSpeed();           // => \Unterprogramme.ino\calculateSpeed(E)
  drone.setSpeed(87);         // sendet Geschwindigkeit [input] über Objektinstanz 'drone' an Klasse 'FlightPresets' der Library 'FlightPresets.h'
  drone.printSpeed();         // liest Geschwindigkeit der Klasse 'FlightPresets' der Library 'FlightPresets.h' aus und gibt sie in seriellem Monitor aus

  delay(500);
}
//Unterprogramm A zum Starten des Slaves
void startGyro() {
  Wire.beginTransmission(adrMPU);
  Wire.write(adrPWR);
  Wire.write(0);
  Wire.endTransmission();
}


//Unterprogramm B zum Auslesen der Gyroskop-Werte
void readGyro() {
  Wire.beginTransmission(adrMPU);
  Wire.write(adrGXOutH);
  Wire.endTransmission(false);
  Wire.requestFrom(adrMPU, 6, false);

  GXOut = Wire.read() << 8 | Wire.read();
  GYOut = Wire.read() << 8 | Wire.read();
  GZOut = Wire.read() << 8 | Wire.read();

  readGyro_checkX();      // => \Unter-Unterprogramme.ino\readyGyro_checkX(B_A)
  readGyro_checkY();      // => \Unter-Unterprogramme.ino\readyGyro_checkY(B_B)
  readGyro_checkZ();      // => \Unter-Unterprogramme.ino\readyGyro_checkZ(B_C)
}


//Unterprogramm C zum Schreiben der Werte des Gyroskops
void writeGyro() {
  Serial.print("Gyro X:   ");
  Serial.print(GXOut);
  Serial.print("   Gyro Y:   ");
  Serial.print(GYOut);
  Serial.print("   Gyro Z:   ");
  Serial.println(GZOut);
}


//Unterprogramm D zum Kallibrieren des Gyroskops
void calibrateGyro() {
  if (Dx2 == 0) {

    Dx2 = 1;
    Serial.println("Starte Kalibrierung...");
    delay(1000);

    readGyro();
    minGX = GXOut;
    maxGX = GXOut;
    minGY = GYOut;
    maxGY = GYOut;
    minGZ = GZOut;
    maxGZ = GZOut;
  }

  for (Dt01; Dt01 < 5000; Dt01 = millis()) {

    Dx1 = 1;

    startGyro();
    readGyro();
    if (GXOut <= minGX) minGX = GXOut;
    if (GXOut >= maxGX) maxGX = GXOut;

    if (GYOut <= minGY) minGY = GYOut;
    if (GYOut >= maxGY) maxGY = GYOut;

    if (GZOut <= minGZ) minGZ = GZOut;
    if (GZOut >= maxGZ) maxGZ = GZOut;


    Serial.print("X:   ");
    Serial.print(minGX);
    Serial.print("  /  ");
    Serial.println(maxGX);
    Serial.print("Y:   ");
    Serial.print(minGY);
    Serial.print("  /  ");
    Serial.println(maxGY);
    Serial.print("Z:   ");
    Serial.print(minGZ);
    Serial.print("  /  ");
    Serial.println(maxGZ);

    delay(Dt02);
  }
  if (Dx1 == 1) {
    Dx1 = 0;
    Serial.println("Kalibrierung beendet.");
    delay(Dt03);
  }
}


//Unterprogramm E zum Umrechnen der Gyro-Neigungswerte in Geschwindigkeiten für alle 4 Motoren
void calculateSpeed(){
}
//Unterprogramm B_A -> prüft, ob Rotation der X-Achse in Kalibriertem Bereich liegt, und Geschwindigkeit der Drohne dadurch "O" ist.
void readGyro_checkX() {

  GXF = GXOut;
  cGX = map(GXOut, minGX, maxGX, 0, 255);
  
  Serial.print("Bewegung X-Achse:   ");

  if (cGX < 255 && cGX > 0) {
    GXF = 0;
    Serial.print(GXF);
    Serial.print("   /   ");
    Serial.println(cGX);
  } else {
    GXF = cGX;
    Serial.print(GXF);
    Serial.print("   /   ");
    Serial.println(cGX);
  }
}


//Unterprogramm B_B -> prüft, ob Rotation der Y-Achse in Kalibriertem Bereich liegt, und Geschwindigkeit der Drohne dadurch "O" ist.
void readGyro_checkY() {

  GYF = GYOut;
  cGY = map(GYOut, minGY, maxGY, 0, 255);

  Serial.print("Bewegung Y-Achse:   ");


  if (cGY < 255 && cGY > 0) {
    GYF = 0;
    Serial.print(GYF);
    Serial.print("   /   ");
    Serial.println(cGY);
  } else {
    GYF = cGY;
    Serial.print(GYF);
    Serial.print("   /   ");
    Serial.println(cGY);
  }
}


//Unterprogramm B_C -> prüft, ob Rotation der Z-Achse in Kalibriertem Bereich liegt, und Geschwindigkeit der Drohne dadurch "O" ist.
void readGyro_checkZ() {

  GZF = GZOut;
  cGZ = map(GZOut, minGZ, maxGZ, 0, 255);

  Serial.print("Bewegung Z-Achse:   ");


  if (cGZ < 255 && cGZ > 0) {
    GZF = 0;
    Serial.print(GZF);
    Serial.print("   /   ");
    Serial.println(cGZ);
  } else {
    GZF = cGZ;
    Serial.print(GZF);
    Serial.print("   /   ");
    Serial.println(cGZ);
  }
}