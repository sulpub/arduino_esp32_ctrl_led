#include <Adafruit_NeoPixel.h>

// Paramètres de la bande LED
#define LED_PIN_HR 26  // 26:con proche USB 19:norm Pin de données pour les LEDs  BAND 0
#define LED_PIN_LL 22  // Pin de données pour les LEDs BAND 1
#define LED_PIN_LR 23  // Pin de données pour les LEDs BAND 2
#define LED_PIN_UV 21  // Pin de données pour les LEDs BAND 3

#define MAX_LEDS 30  // Nombre maximum de LEDs prises en charge
#define NB_BAND 4    // Nombre de bande de led

Adafruit_NeoPixel strip1(MAX_LEDS, LED_PIN_HR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(MAX_LEDS, LED_PIN_LL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(MAX_LEDS, LED_PIN_LR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(MAX_LEDS, LED_PIN_UV, NEO_GRB + NEO_KHZ800);

int i = 0;

void all_black(void);

void setup() {
  Serial.begin(115200);  // Initialiser la communication série
  strip1.begin();        // Initialiser la bande LED
  strip1.show();         // Éteindre toutes les LEDs au démarrage
  strip2.begin();        // Initialiser la bande LED
  strip2.show();         // Éteindre toutes les LEDs au démarrage
  strip3.begin();        // Initialiser la bande LED
  strip3.show();         // Éteindre toutes les LEDs au démarrage
  strip4.begin();        // Initialiser la bande LED
  strip4.show();         // Éteindre toutes les LEDs au démarrage

  //eteindre toutes les leds
  all_black();
}


void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // Lire jusqu'à la fin de ligne
    processInput(input);
  }
}

void processInput(String input) {
  input.trim();  // Supprimer les espaces inutiles

  // Découper la chaîne d'entrée par les virgules
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  int thirdComma = input.indexOf(',', secondComma + 1);
  int fourthComma = input.indexOf(',', thirdComma + 1);
  int fiveComma = input.indexOf(',', fourthComma + 1);

  if (firstComma < 0 || secondComma < 0 || thirdComma < 0 || fourthComma < 0 || fiveComma < 0) {
    Serial.println("Erreur: format incorrect");
    return;
  }

  // Extraire les valeurs des paramètres
  int numLEDs = input.substring(0, firstComma).toInt();
  int nbBands = input.substring(firstComma + 1, secondComma).toInt();
  int ledIndex = input.substring(secondComma + 1, thirdComma).toInt();
  int red = input.substring(thirdComma + 1, fourthComma).toInt();
  int green = input.substring(fourthComma + 1, fiveComma).toInt();
  int blue = input.substring(fiveComma + 1).toInt();

  // Vérifications de validité
  if (numLEDs > MAX_LEDS || numLEDs <= 0) {
    Serial.println("Erreur: nombre de LEDs invalide");
    return;
  }

  if (ledIndex < 0 || ledIndex >= numLEDs) {
    Serial.println("Erreur: index LED invalide");
    return;
  }

  if (nbBands == 2025) {
    //eteindre toutes les leds
    all_black();
    Serial.println("Efface toute les leds");
    return;
  }

  if (nbBands < 0 || nbBands >= NB_BAND) {
    Serial.println("Erreur: index nb BAND invalide");
    return;
  }

  if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) {
    Serial.println("Erreur: valeur de couleur invalide");
    return;
  }

  if (nbBands == 0) {
    // Configurer la couleur de la LED spécifiée
    strip1.setPixelColor(ledIndex, strip1.Color(red, green, blue));
    strip1.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 1");
  }
  if (nbBands == 1) {
    // Configurer la couleur de la LED spécifiée
    strip2.setPixelColor(ledIndex, strip2.Color(red, green, blue));
    strip2.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 1");
  }
  if (nbBands == 2) {
    // Configurer la couleur de la LED spécifiée
    strip3.setPixelColor(ledIndex, strip3.Color(red, green, blue));
    strip3.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 1");
  }
  if (nbBands == 3) {
    // Configurer la couleur de la LED spécifiée
    strip4.setPixelColor(ledIndex, strip4.Color(red, green, blue));
    strip4.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 1");
  }
  delay(10);
}



void all_black(void) {

  //effacer les bands
  for (i = 0; i < MAX_LEDS; i++) {
    strip1.setPixelColor(i, strip1.Color(0, 0, 0));
  }
  strip1.show();
  delay(10);

  for (i = 0; i < MAX_LEDS; i++) {
    strip2.setPixelColor(i, strip1.Color(0, 0, 0));
  }
  strip2.show();
  delay(10);

  for (i = 0; i < MAX_LEDS; i++) {
    strip3.setPixelColor(i, strip1.Color(0, 0, 0));
  }
  strip3.show();
  delay(10);

  for (i = 0; i < MAX_LEDS; i++) {
    strip4.setPixelColor(i, strip1.Color(0, 0, 0));
  }
  strip4.show();
  delay(10);
}
