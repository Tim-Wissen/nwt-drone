#include <Wire.h>
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
}