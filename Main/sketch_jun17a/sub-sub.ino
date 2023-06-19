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