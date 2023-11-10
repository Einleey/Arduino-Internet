#include "SPI.h"
#include "Ethernet.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 143); //mettez sur google : http://192.168.1.143/
EthernetServer local_server(80);

int capteur_temp = A0;

void setup() {
  // Configuration Ethernet
  Ethernet.begin(mac, ip);
  local_server.begin();
  Serial.begin(9600); // Démarrage de la communication série pour le débogage
}

void loop() {
  // Attendre et accepter les connexions entrantes sur le serveur local
  EthernetClient local_client = local_server.available();
  if (local_client) {
    boolean currentLineIsBlank = true;
    while (local_client.connected()) {
      if (local_client.available()) {
        char c = local_client.read();
        // Vérifie si la ligne actuelle est vide
        if (c == '\n' && currentLineIsBlank) {
          // Répondre à la requête HTTP
          local_client.println("HTTP/1.1 200 OK");
          local_client.println("Access-Control-Allow-Origin: *");
          local_client.println("Content-Type: application/json");
          local_client.println("Connection: close");
          local_client.println();

          // Mesurer la température à partir du capteur analogique
          float temperatureAnalog = getTemperatureFromAnalog();
          char sPostData[150] = "";
          // Générer une réponse JSON
          getJSON_DataFromSensors(sPostData, temperatureAnalog);
          local_client.println(sPostData);

          break;
        }

        // Vérifier si la ligne actuelle est vide
        if (c == '\n')
          currentLineIsBlank = true;
        else if (c != '\r')
          currentLineIsBlank = false;
      }
    }
    // Attendre un moment pour laisser le client récupérer les données
    delay(1000);
    // Fermer la connexion client
    local_client.stop();
  }
}

// Fonction pour mesurer la température à partir du capteur analogique
float getTemperatureFromAnalog() {
  int reading = analogRead(capteur_temp);
  float volt = reading * 5.0 / 1024.0;
  return (volt - 0.5) * 100;
}

// Fonction pour générer une réponse JSON
void getJSON_DataFromSensors(char *sDataFromSensors, float temperature) {
  // Commence la structure JSON
  strcpy(sDataFromSensors, "{");
  char tempext[30] = "";
  // Convertit la température en chaîne de caractères
  dtostrf(temperature, 0, 1, tempext);
  // Ajoute la température au JSON
  strcat(sDataFromSensors, "\"Température de l'air\":\" ");
  strcat(sDataFromSensors, tempext);
  strcat(sDataFromSensors, "°C \"");
  // Termine la structure JSON
  strcat(sDataFromSensors, "}");
}
