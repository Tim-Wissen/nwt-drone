#include <Arduino.h>
#include <Wire.h>
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

int mEt01;          //Zeit-Variable 1 [millis();] -> \Unterprogramme.ino\calculatePosition(E)
int mEt02;          //Zeit-Variable 2 [millis();] -> \Unterprogramme.ino\calculatePosition(E)

int Ex01_X;         //temp. Variable == GXOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex02_X;         //temp. Variable == GXOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex03_X;         //temp. Variable == GXOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex04_X;         //temp. Variable == GXOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex05_X;         //temp. Variable == GXOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)

int Ex01_Y;         //temp. Variable == GYOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex02_Y;         //temp. Variable == GYOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex03_Y;         //temp. Variable == GYOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex04_Y;         //temp. Variable == GYOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex05_Y;         //temp. Variable == GYOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)

int Ex01_Z;         //temp. Variable == GZOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex02_Z;         //temp. Variable == GZOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex03_Z;         //temp. Variable == GZOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex04_Z;         //temp. Variable == GZOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex05_Z;         //temp. Variable == GZOut für 1. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)

int Ex01_XGes;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex02_XGes;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex03_XGes;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex04_XGes;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex05_XGes;          //temp. Gesamtwert GXOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)

int Ex01_YGes;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex02_YGes;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex03_YGes;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex04_YGes;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex05_YGes;          //temp. Gesamtwert GYOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)

int Ex01_ZGes;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex02_ZGes;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex03_ZGes;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex04_ZGes;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)
int Ex05_ZGes;          //temp. Gesamtwert GZOut (5 Schritte) für 1. & 2. Integration(Acceleration -> Speed) -> \Unterprogramme.ino\calculatePosition(E)

int Dt01 = 0;                 //Zeit Variable 1 -> \Unterprogramme.ino\calibrateGyro(D)
int Dt02 = 100;               //Zeit Variable 2 -> \Unterprogramme.ino\calibrateGyro(D)
int Dt03 = 2000;              //Zeit Variable 3 -> \Unterprogramme.ino\calibrateGyro(D)

bool Dx1 = 0;                 //allg. Variable 1 -> \Unterprogramme.ino\calibrateGyro(D)
bool Dx2 = 0;                 //allg. Variable 2 -> \Unterprogramme.ino\calibrateGyro(D)

int speed;          //Geschwindigkeitsvariable





void setup() {
  Serial.begin(9600);
  Wire.begin();
}


void loop() {
  startGyro();                // => \Unterprogramme.ino\startGyro(A)
  calibrateGyro();            // => \Unterprogramme.ino\calibrateGyro(D)
  readGyro();                 // => \Unterprogramme.ino\readGyro(B)
  Position_Integration_1();   // => \Unterprogramme.ino\Position_Integration_1(E)
  writeGyro();                // => \Unterprogramme.ino\writeGyro(C)
  drone.setSpeed(speed);      // sendet Geschwindigkeit [input] über Objektinstanz 'drone' an Klasse 'FlightPresets' der Library 'FlightPresets.h'
  drone.printSpeed();         // liest Geschwindigkeit der Klasse 'FlightPresets' der Library 'FlightPresets.h' aus und gibt sie in seriellem Monitor aus

  delay(500);
}