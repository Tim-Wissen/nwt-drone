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