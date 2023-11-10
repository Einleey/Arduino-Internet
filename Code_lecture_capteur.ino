int brocheCapteur = 0; //Correspond à la broche A0 de la carte Arduino

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("Pret");
}

void loop() {
  float valeur = analogRead(brocheCapteur); // Lecture de la valeur transmise par le capteur
  valeur = valeur*5.0/1024; // Conversion de la valeur en une tension utilisable
  valeur = (valeur - 0.5)/0.01; // ou *100 
  Serial.print(valeur); Serial.println(" °C"); //Conversion de la tension en une température. D'après la datasheet, la courbe de la tension en fonction de la température possède un coefficient directeur de 10 mV/°C et un offset de 0.5 V
  
  delay(1000);
}
