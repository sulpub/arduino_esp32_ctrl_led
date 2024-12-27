#include <Adafruit_NeoPixel.h>

// Paramètres de la bande LED
#define LED_PIN 26       // Pin de données pour les LEDs
#define MAX_LEDS 21    // Nombre maximum de LEDs prises en charge

Adafruit_NeoPixel strip(MAX_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200); // Initialiser la communication série
  strip.begin();        // Initialiser la bande LED
  strip.show();         // Éteindre toutes les LEDs au démarrage
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Lire jusqu'à la fin de ligne
    processInput(input);
  }
}

void processInput(String input) {
  input.trim(); // Supprimer les espaces inutiles

  // Découper la chaîne d'entrée par les virgules
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  int thirdComma = input.indexOf(',', secondComma + 1);
  int fourthComma = input.indexOf(',', thirdComma + 1);

  if (firstComma < 0 || secondComma < 0 || thirdComma < 0 || fourthComma < 0) {
    Serial.println("Erreur: format incorrect");
    return;
  }

  // Extraire les valeurs des paramètres
  int numLEDs = input.substring(0, firstComma).toInt();
  int ledIndex = input.substring(firstComma + 1, secondComma).toInt();
  int red = input.substring(secondComma + 1, thirdComma).toInt();
  int green = input.substring(thirdComma + 1, fourthComma).toInt();
  int blue = input.substring(fourthComma + 1).toInt();

  // Vérifications de validité
  if (numLEDs > MAX_LEDS || numLEDs <= 0) {
    Serial.println("Erreur: nombre de LEDs invalide");
    return;
  }

  if (ledIndex < 0 || ledIndex >= numLEDs) {
    Serial.println("Erreur: index LED invalide");
    return;
  }

  if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) {
    Serial.println("Erreur: valeur de couleur invalide");
    return;
  }

  // Configurer la couleur de la LED spécifiée
  strip.setPixelColor(ledIndex, strip.Color(red, green, blue));
  strip.show();

  // Retourner un accusé de réception
  Serial.println("OK: LED mise à jour");
}
