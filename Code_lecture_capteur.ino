/* Programme Capteur de Temperature, led Rouge (chauffage allumee), Led Vert (chauffage etient),
**
**------TMP36----------------------------------------------
**      _________
**      |       |
**      | TMP36 |
**      ---------
**        | | |
**      GND,A0,+5v
** 
**    A0 = Pin Analog de Arduino
**
**---------LED VERT----------------------------------------
**   
**     ledG = led Vert 
**
**                R
**         |---\/\/\/---|    |\  |
**   D1 ---|            |----|  >|----------GND
**         |---\/\/\/---|    |/  |
**                R
**
**            R = 51 ohm      R//R = Req ~= 25ohm
**
**           D1 = Pin D1 arduino
**
**
**---------LED ROUGE-----------------------------------------
**   
**     ledR = led Rouge 
**
**                R
**         |---\/\/\/---|    |\  |
**   D0 ---|            |----|  >|----------GND
**         |---\/\/\/---|    |/  |
**                R
**
**            R = 100 ohm      R//R = Req ~= 50ohm
**
**           D0 = Pin D0 arduino
**
*/

#define brocheCapteur A0
#define ledR 0
#define ledG 1


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);         // pin A0 Analog pour capteur de temperature
  pinMode(ledR, OUTPUT);      // pin digital sortie
  pinMode(ledG, OUTPUT);      // pin digital sortie
  Serial.println("Pret");
}

float lire_temp()
{
  float valeur = analogRead(brocheCapteur);
  Serial.println(valeur, 2);

  float voltage = valeur * 5 / 1023.0; // Cconvertir en tension
  Serial.println(voltage, 2);
  //Conversion de la tension en une température. D'après la datasheet, la courbe de la tension en fonction de la température possède un coefficient directeur de 10 mV/°C et un offset de 0.5 V
  float temperature = (voltage - 0.5) * 100.0; // convertir en celcius
  return temperature;
}


void aff_temp_ecran(float temp)
{
  Serial.print(temp, 2); Serial.println(" °C"); 
  Serial.println();
  delay(1000);
}

void chauffage(float temp)
{
  if(temp <= 25)
  {
    digitalWrite(ledR,HIGH);
    digitalWrite(ledG,LOW);
  }
  if(temp >= 25)
  {
    digitalWrite(ledR,LOW);
    digitalWrite(ledG,HIGH);
  }

} 
void loop() 
{
  aff_temp_ecran(lire_temp());
  chauffage(lire_temp());
}
