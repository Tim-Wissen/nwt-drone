#include <Wire.h>
#include <Arduino.h>
#include <FlightPresets.h>
#include <MPU6050.h>

MPU6050 gyro;                 //Objektinstanz der Klasse 'MPU6050' mit dem Name 'gyro' wird erstellt
FlightPresets drone;          // Obje#include <Wire.h>
#include <Arduino.h>
#include <FlightPresets.h>

FlightPresets drone;          // Objektinstanz der Klasse 'FlightPresets' mit dem Namen 'drone' wird erstellt

const int adrMPU = 0x68;      //Adresse des MPU

const int adrPWR = 0x6B;      //Adresse des Power-Management
const int adrGXOutH = 0x43;   //Adresse GYRO_XOUT[15:8] (folgende 5 Register bis GYRO_ZOUT[7:0])

long GXOut;                //Wert GYRO_X_OUT
long GYOut;                //Wert GYRO_Y_OUT
long GZOut;                //Wert GYRO_Z_OUT

long GXPos;          //Wert GYRO_X_POSITION
long GYPos;          //Wert GYRO_Y_POSITION
long GZPos;          //Wert GYRO_Z_POSITION

long minGX;            //Minimum-Wert von GYRO_X
long minGY;            //Minimum-Wert von GYRO_Y
long minGZ;            //Minimum-Wert von GYRO_Z

long maxGX;            //Maximum-Wert von GYRO_X
long maxGY;            //Maximum-Wert von GYRO_Y
long maxGZ;            //Maximum-Wert von GYRO_Z

long cGX;          //Kalibrierter Wert von GYRO_X
long cGY;          //Kalibrierter Wert von GYRO_Y
long cGZ;          //Kalibrierter Wert von GYRO_Z

long GXF;          //Finaler Wert GYRO_X
long GYF;          //Finaler Wert GYRO_Y
long GZF;          //Finaler Wert GYRO_Z

int t01 = 1000;               //Zeit-Variable 1
int t02 = 0;                  //Zeit-Variable 2

int mEt01 = 0;          //Zeit-Variable 1 [millis();] -> \sub.ino\calculatePosition(E)

int Ex01_X = 0;         //temp. Variable == GXOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex02_X = 0;         //temp. Variable == GXOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex03_X = 0;         //temp. Variable == GXOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex04_X = 0;         //temp. Variable == GXOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex05_X = 0;         //temp. Variable == GXOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)

int Ex01_Y = 0;         //temp. Variable == GYOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex02_Y = 0;         //temp. Variable == GYOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex03_Y = 0;         //temp. Variable == GYOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex04_Y = 0;         //temp. Variable == GYOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex05_Y = 0;         //temp. Variable == GYOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)

int Ex01_Z = 0;         //temp. Variable == GZOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex02_Z = 0;         //temp. Variable == GZOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex03_Z = 0;         //temp. Variable == GZOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex04_Z = 0;         //temp. Variable == GZOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)
int Ex05_Z = 0;         //temp. Variable == GZOut für 1. Integrationlong -> \sub.ino\calculatePosition(E)

int Ex01_XGes = 0;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex02_XGes = 0;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex03_XGes = 0;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex04_XGes = 0;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex05_XGes = 0;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)

int Ex01_YGes = 0;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex02_YGes = 0;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex03_YGes = 0;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex04_YGes = 0;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex05_YGes = 0;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)

int Ex01_ZGes = 0;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex02_ZGes = 0;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex03_ZGes = 0;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex04_ZGes = 0;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)
int Ex05_ZGes = 0;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration -> \sub.ino\calculatePosition(E)

int Ex11_X = 0;         //temp. Gesamtwert GXOut für 2. Integration -> \sub-sub.ino\Position_Integration_2(E_A)
int Ex11_Y = 0;         //temp. Gesamtwert GYOut für 2. Integration
int Ex11_Z = 0;         //temp. Gesamtwert GZOut für 2. Integration

bool E01_Rotation;          //Anzeige, ob Gyroskop sich bewegt \sub.ino\calculatePosition(E)

int Dt01 = 0;                 //Zeit Variable 1 -> \sub.ino\calibrateGyro(D)
int Dt02 = 100;               //Zeit Variable 2 -> \sub.ino\calibrateGyro(D)
int Dt03 = 2000;              //Zeit Variable 3 -> \sub.ino\calibrateGyro(D)

int E_At01 = 10;          //Zeit-Variable 1 -> \sub-sub.ino\Position_Integration(E_A)

bool Dx1 = 0;                 //allg. Variable 1 -> \sub.ino\calibrateGyro(D)
bool Dx2 = 0;                 //allg. Variable 2 -> \sub.ino\calibrateGyro(D)

int speed;          //Geschwindigkeitsvariable





void setup() {
  Serial.begin(9600);
  Wire.begin();
}


void loop() {
  startGyro();                // => \sub.ino\startGyro(A)
  calibrateGyro();            // => \sub.ino\calibrateGyro(D)
  readGyro();                 // => \sub.ino\readGyro(B)
  Position_Integration();   // => \sub.ino\Position_Integration_1(E)
  writeGyro();                // => \sub.ino\writeGyro(C)
  drone.setSpeed(speed);      // sendet Geschwindigkeit [input] über Objektinstanz 'drone' an Klasse 'FlightPresets' der Library 'FlightPresets.h'
  drone.printSpeed();         // liest Geschwindigkeit der Klasse 'FlightPresets' der Library 'FlightPresets.h' aus und gibt sie in seriellem Monitor aus

  delay(1000);
}ktinstanz der Klasse 'FlightPresets' mit dem Namen 'drone' wird erstellt

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

  readGyro_checkX();  // => \sub-sub.ino\readyGyro_checkX(B_A)
  readGyro_checkY();  // => \sub-sub.ino\readyGyro_checkY(B_B)
  readGyro_checkZ();  // => \sub-sub.ino\readyGyro_checkZ(B_C)

  if (GXOut < maxGX && GXOut > minGX){
    GXOut = 0;
    E01_Rotation = 0;
  }
  else E01_Rotation = 1;

  if (GYOut < maxGY && GYOut > minGY){
    GYOut = 0;
    E01_Rotation = 0;
  }
  else E01_Rotation = 1;

  if (GZOut < maxGZ && GZOut > minGZ){
    GZOut = 0;
    E01_Rotation = 0;
  }
  else E01_Rotation = 1;
}


//Unterprogramm C zum Schreiben der Werte des Gyroskops
void writeGyro() {
  Serial.print("Gyro X:   ");
  Serial.print(GXOut);
  Serial.print("   Gyro Y:   ");
  Serial.print(GYOut);
  Serial.print("   Gyro Z:   ");
  Serial.println(GZOut);

  Serial.print("POS X:   ");
  Serial.print(GXPos);
  Serial.print("   POS Y:   ");
  Serial.print(GYPos);
  Serial.print("   POS Z:   ");
  Serial.println(GZPos);
  Serial.println("");
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

    GXPos = 0;
    GYPos = 0;
    GZPos = 0;

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


//Unterprogramm E für Integration von Acceleration zu Position
void Position_Integration() {
  mEt01 = 0;

  for (mEt01 = 0; mEt01 < 11; mEt01 +=2) {
    

    if (mEt01 == 2 && E01_Rotation == 1) {
      Ex01_XGes = Ex01_XGes - Ex01_X;
      Ex01_YGes = Ex01_YGes - Ex01_Y;
      Ex01_ZGes = Ex01_ZGes - Ex01_Z;

      Ex02_XGes = Ex02_XGes - Ex01_X;
      Ex02_YGes = Ex02_YGes - Ex01_Y;
      Ex02_ZGes = Ex02_ZGes - Ex01_Z;

      readGyro();
      Ex01_X = GXOut;
      Ex01_Y = GYOut;
      Ex01_Z = GZOut;

      Ex01_XGes = Ex01_X + Ex01_X;
      Ex01_YGes = Ex01_Y + Ex01_Y;
      Ex01_ZGes = Ex01_Z + Ex01_Z;
      
      Ex02_XGes = Ex02_X + Ex01_X;
      Ex02_YGes = Ex02_Y + Ex01_Y;
      Ex02_ZGes = Ex02_Z + Ex01_Z;

      Position_Integration_2();         // => \sub-sub.ino\Position_Integration_2
    }

    else if (mEt01 == 4 && E01_Rotation == 1) {
      Ex02_XGes = Ex02_XGes - Ex02_X;
      Ex02_YGes = Ex02_YGes - Ex02_Y;
      Ex02_ZGes = Ex02_ZGes - Ex02_Z;

      Ex03_XGes = Ex03_XGes - Ex02_X;
      Ex03_YGes = Ex03_YGes - Ex02_Y;
      Ex03_ZGes = Ex03_ZGes - Ex02_Z;

      readGyro();
      Ex02_X = GXOut;
      Ex02_Y = GYOut;
      Ex02_Z = GZOut;

      Ex02_XGes = Ex02_X + Ex02_X;
      Ex02_YGes = Ex02_Y + Ex02_Y;
      Ex02_ZGes = Ex02_Z + Ex02_Z;
      
      Ex03_XGes = Ex03_X + Ex02_X;
      Ex03_YGes = Ex03_Y + Ex02_Y;
      Ex03_ZGes = Ex03_Z + Ex02_Z;

      Position_Integration_2();         // => \sub-sub.ino\Position_Integration_2
    }

    else if (mEt01 == 6 && E01_Rotation == 1) {
      Ex03_XGes = Ex03_XGes - Ex03_X;
      Ex03_YGes = Ex03_YGes - Ex03_Y;
      Ex03_ZGes = Ex03_ZGes - Ex03_Z;
      
      Ex04_XGes = Ex04_XGes - Ex03_X;
      Ex04_YGes = Ex04_YGes - Ex03_Y;
      Ex04_ZGes = Ex04_ZGes - Ex03_Z;

      readGyro();
      Ex03_X = GXOut;
      Ex03_Y = GYOut;
      Ex03_Z = GZOut;

      Ex03_XGes = Ex03_X + Ex03_X;
      Ex03_YGes = Ex03_Y + Ex03_Y;
      Ex03_ZGes = Ex03_Z + Ex03_Z;
      
      Ex04_XGes = Ex04_X + Ex03_X;
      Ex04_YGes = Ex04_Y + Ex03_Y;
      Ex04_ZGes = Ex04_Z + Ex03_Z;

      Position_Integration_2();         // => \sub-sub.ino\Position_Integration_2
    }

    else if (mEt01 == 8 && E01_Rotation == 1) {
      Ex04_XGes = Ex04_XGes - Ex03_X;
      Ex04_YGes = Ex04_YGes - Ex03_Y;
      Ex04_ZGes = Ex04_ZGes - Ex03_Z;
      
      Ex05_XGes = Ex05_XGes - Ex03_X;
      Ex05_YGes = Ex05_YGes - Ex03_Y;
      Ex05_ZGes = Ex05_ZGes - Ex03_Z;
      
      readGyro();
      Ex04_X = GXOut;
      Ex04_Y = GYOut;
      Ex04_Z = GZOut;

      Ex04_XGes = Ex04_X + Ex04_X;
      Ex04_YGes = Ex04_Y + Ex04_Y;
      Ex04_ZGes = Ex04_Z + Ex04_Z;
      
      Ex05_XGes = Ex05_X + Ex04_X;
      Ex05_YGes = Ex05_Y + Ex04_Y;
      Ex05_ZGes = Ex05_Z + Ex04_Z;

      Position_Integration_2();         // => \sub-sub.ino\Position_Integration_2
    }

    else if (mEt01 == 10 && E01_Rotation == 1) {
      Ex05_XGes = Ex05_XGes - Ex05_X;
      Ex05_YGes = Ex05_YGes - Ex05_Y;
      Ex05_ZGes = Ex05_ZGes - Ex05_Z;
      
      Ex01_XGes = Ex01_XGes - Ex05_X;
      Ex01_YGes = Ex01_YGes - Ex05_Y;
      Ex01_ZGes = Ex01_ZGes - Ex05_Z;

      readGyro();
      Ex05_X = GXOut;
      Ex05_Y = GYOut;
      Ex05_Z = GZOut;

      Ex05_XGes = Ex05_X + Ex05_X;
      Ex05_YGes = Ex05_Y + Ex05_Y;
      Ex05_ZGes = Ex05_Z + Ex05_Z;
      
      Ex01_XGes = Ex01_X + Ex05_X;
      Ex01_YGes = Ex01_Y + Ex05_Y;
      Ex01_ZGes = Ex01_Z + Ex05_Z;

      Position_Integration_2();         // => \sub-sub.ino\Position_Integration_2
    }
  }
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


//Unterprogramm E_A -> berechnet 2.Integration der X-, Y-, und Z-Werte
void Position_Integration_2(){
  GXPos = GXPos - Ex11_X;    // Aktualisierung der Position der X-Achse
  GYPos = GYPos - Ex11_Y;    // Aktualisierung der Position der Y-Achse
  GZPos = GZPos - Ex11_Z;    // Aktualisierung der Position der Z-Achse
  
  delay(E_At01);

  Ex11_X = Ex01_XGes + Ex02_XGes + Ex03_XGes + Ex04_XGes + Ex05_XGes;
  Ex11_Y = Ex01_YGes + Ex02_YGes + Ex03_YGes + Ex04_YGes + Ex05_YGes;
  Ex11_Y = Ex01_YGes + Ex02_YGes + Ex03_YGes + Ex04_YGes + Ex05_YGes;

  delay(E_At01);

  GXPos = GXPos + Ex11_X;    // Aktualisierung der Position der X-Achse
  GYPos = GYPos + Ex11_Y;    // Aktualisierung der Position der Y-Achse
  GZPos = GZPos + Ex11_Z;    // Aktualisierung der Position der Z-Achse

  Serial.println("\n ---- == ----\n");
}