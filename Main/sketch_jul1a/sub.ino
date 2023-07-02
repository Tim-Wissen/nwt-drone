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


//Unterprogramm E zum Umrechnen der 3 Achsenwerte in 4 Propellerwerte
void calculateGyro(){
  x = map(GXOut, -32000, 32000, -100, 100);
  y = map(GYOut, -32000, 32000, -100, 100);
  z = map(GZOut, -32000, 32000, -100, 100);

  fl = y + x - z;
  fr = y - x + z;
  bl = - y + x + z;
  br = - y - x - z;

  flp = speed + fl * 1/1000;
  frp = speed + fr * 1/1000;
  blp = speed + bl * 1/1000;
  brp = speed + br * 1/1000;
}


//Unterprogramm F zur endgültigen Ausgabe der Flugdaten an die Motoren
void flydrone(){
  for(F_01, F_01 < 1000, F_01++){
  analogWrite(P_fl, flp);
  analogWrite(P_fr, frp);
  analogWrite(P_bl, blp);
  analogWrite(P_br, brp);
  }
}