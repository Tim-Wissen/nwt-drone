#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;         //Erstellt Objektinstanz 'mpu' der Library 'Adafruit_MPU6050.h'
sensors_event_t event;          //Erstellt Ojektinstanz 'event' der Library 'Adafruit_Sensor.h'

const int adrMPU = 0x68;      //Adresse des MPU

const int adrPWR = 0x6B;      //Adresse des Power-Management
const int adrGXOutH = 0x43;   //Adresse GYRO_XOUT[15:8] (folgende 5 Register bis GYRO_ZOUT[7:0])

const byte P_fl = 3;         //Festlegung des Propellers fl als PIN-OUTPUT 3
const byte P_fr = 5;         //Festlegung des Propellers fr als PIN-OUTPUT 5
const byte P_bl = 6;         //Festlegung des Propellers bl als PIN-OUTPUT 6
const byte P_br = 9;         //Festlegung des Propellers br als PIN-OUTPUT 9

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

int x = 0;
int y = 0;
int z = 0;

int t01 = 1000;               //Zeit-Variable 1
int t02 = 0;                  //Zeit-Variable 2

int Dt01 = 0;                 //Zeit Variable 1 -> \sub.ino\calibrateGyro(D)
int Dt02 = 100;               //Zeit Variable 2 -> \sub.ino\calibrateGyro(D)
int Dt03 = 2000;              //Zeit Variable 3 -> \sub.ino\calibrateGyro(D)

bool Dx1 = 0;                 //allg. Variable 1 -> \sub.ino\calibrateGyro(D)
bool Dx2 = 0;                 //allg. Variable 2 -> \sub.ino\calibrateGyro(D)

byte E_scale = 50;          //Skalierungs-Variable -> \sub.ino\calculateGyro(E)

unsigned int F_01;

const int speed = 50;          //Geschwindigkeitsvariable

int fl, fr, bl, br;             //Variable, in der drei Achsenwerte zu 4 Propellerwerte zugerechnet werden
int flp, frp, blp, brp;         //Variable, die die endgültigen Propellerwerte angeben (einschl. Grundgeschw.)





void setup() {
  Serial.begin(9600);
  Wire.begin();
}


void loop() {
  startGyro();                // => \sub.ino\startGyro(A)
  calibrateGyro();            // => \sub.ino\calibrateGyro(D)
  readGyro();                 // => \sub.ino\readGyro(B)
  calculateGyro();            // => \sub.ino\calculateGyro(E)
  writeGyro();                // => \sub.ino\writeGyro(C)
  flydrone();                 // => \sub.ino\flydrone(F)

  delay(1000);
}