//Unterprogramm A zum Starten des Slaves
void startGyro() {
  Wire.beginTransmission(adrMPU);
  Wire.write(adrPWR);
  Wire.write(0);
  Wire.endTransmission(false);
}


//Unterprogramm B zum Auslesen der Gyroskop-Werte
void readGyro() {
  Wire.beginTransmission(adrMPU);
  Wire.write(adrGXOutH);
  Wire.endTransmission(false);
  Wire.requestFrom(adrMPU, 6, true);

  GXOut = Wire.read() << 8 | Wire.read();
  GYOut = Wire.read() << 8 | Wire.read();
  GZOut = Wire.read() << 8 | Wire.read();

  GyX = GXOut;
  GyY = GYOut;
  GyZ = GZOut;

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

