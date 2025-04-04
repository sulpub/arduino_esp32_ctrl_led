#include <Adafruit_NeoPixel.h>

/*
Liste de librairie : 
  - Adafruit NeoPixel at version 1.11.0 : Adafruit_NeoPixel by Adafruit

PINOUT ATOM M5STACK
                    WIFI
              ________________
         3V3 |                |
  BAND1  G22 |                |G21 BAND3
  BAND0  G19 |    BOTTOM      |G25
  BAND2  G23 |                |5V
         G33 |________________|GND
               GND 5V G26 G32

Configuration UART : 115200 8 N 1
Commande UART 1 : nombre_led,numero_bande,numero_led,niveau_rouge,niveau_vert_niveau_bleu,niveau_blanc
nombre led SK6812 RGBW : 200
niveau led : 0 à 255 (0:led eteinte et 255:led au max)
numéro bande : 0 - led du haut
               1 - led bas droite
               2 - led bas gauche
               3 - led UV

exemple : 
 - 200,0,6,100,0,0,0 -> bande 0 , led 6 avec niveau rouge = 10 
 - 200,0,16,0,0,0,50 -> bande 0 , led 16 avec niveau blanc = 50
 - 200,1,3,0,0,0,50  -> bande 1 , led 3 avec niveau blanc = 50
 - 200,2,3,0,0,0,50  -> bande 2 , led 3 avec niveau blanc = 50
 - 200,3,0,1,1,1,1   -> bande 3 UV ON, bande led on (non selectionnable)
 - 200,3,0,0,0,0,0   -> bande 3 UV OFF, bande led on (non selectionnable)

Commande spécial numéro bande = 2025 -> efface toute les leds
exemple : 200,2025,0,0,0,0,0

Note : la bande 3 est RGB, la valeur blanche n'est pas pris en compte

Commande UART 2 : mode eclairage
2025,mode :
mode de 1 à 10
mode 100 erase all

*/


// Paramètres de la bande LED
#define LED_PIN_HR 19  // 26:con proche USB 19:norm Pin de données pour les LEDs  BAND 0
#define LED_PIN_LL 22  // Pin de données pour les LEDs BAND 1
#define LED_PIN_LR 23  // Pin de données pour les LEDs BAND 2
#define LED_PIN_UV 21  // Pin de données pour les LEDs BAND 3

#define LED_PIN_PWR_UV 33  // Pin de données pour les LEDs BAND 3

#define MAX_LEDS 200  // Nombre maximum de LEDs prises en charge
#define NB_BAND 4     // Nombre de bande de led

#define PERIOD_CHANGE 1000  //ms

Adafruit_NeoPixel strip1(MAX_LEDS, LED_PIN_HR, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip2(MAX_LEDS, LED_PIN_LL, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip3(MAX_LEDS, LED_PIN_LR, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip4(MAX_LEDS, LED_PIN_UV, NEO_RGB + NEO_KHZ800);

int i = 0;
int k = 0;
int typeLed = 0;  //0:RGBW  1:RGB
int mode = 0;     //led mode
int passmode = 2025;
int passaccess = 0;
int update = 0;

//time variables
unsigned long nowTimeMillis = 0;  //PERIOD_CHANGE
unsigned long updateAnim = 0;

void all_black(void);
void all_black_init_led(void);
void changemode(void);
void processInput(String input);

void setup() {
  Serial.begin(115200);  // Initialiser la communication série

  //pin power band UV
  pinMode(LED_PIN_PWR_UV, OUTPUT);
  digitalWrite(LED_PIN_PWR_UV, LOW);  // POWER OFF LED UV

  strip1.begin();  // Initialiser la bande LED
  strip1.show();   // Éteindre toutes les LEDs au démarrage
  strip2.begin();  // Initialiser la bande LED
  strip2.show();   // Éteindre toutes les LEDs au démarrage
  strip3.begin();  // Initialiser la bande LED
  strip3.show();   // Éteindre toutes les LEDs au démarrage
  strip4.begin();  // Initialiser la bande LED
  strip4.show();   // Éteindre toutes les LEDs au démarrage

  //eteindre toutes les leds
  //all_black();
}


void loop() {

  nowTimeMillis = millis();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // Lire jusqu'à la fin de ligne
    processInput(input);
  }

  changemode();

  delay(1);
}

void changemode(void) {

  switch (mode) {
    case 0:
      // mode 1
      if (update == 1) {
        update = 0;
      }
      break;
    case 1:
      // mode 1
      if (update == 1) {
        update = 0;
        all_black_init_led();
        Serial.println("MODE 1");
        strip1.setPixelColor(4, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(5, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(6, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(8, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(15, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(16, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(18, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(21, strip1.Color(0, 0, 50, 0));
        strip1.show();

        strip2.setPixelColor(3, strip1.Color(0, 0, 0, 5));
        strip2.setPixelColor(5, strip1.Color(0, 0, 0, 5));
        strip2.setPixelColor(6, strip1.Color(0, 0, 0, 5));
        strip2.show();

        strip3.setPixelColor(3, strip1.Color(0, 0, 0, 5));
        strip3.setPixelColor(5, strip1.Color(0, 0, 0, 5));
        strip3.setPixelColor(6, strip1.Color(0, 0, 0, 5));
        strip3.show();
      }
      break;
    case 2:
      // mode 1
      if (update == 1) {
        update = 0;
        all_black_init_led();
        Serial.println("MODE 2");
        strip1.setPixelColor(4, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(5, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(6, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(8, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(15, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(16, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(18, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(21, strip1.Color(0, 0, 50, 0));
        strip1.show();

        strip2.show();

        strip3.show();
      }
      break;      
    case 3:
      // mode 2
      if (update == 1) {
        update = 0;
        all_black_init_led();
        Serial.println("MODE 3");
        strip1.setPixelColor(4, strip1.Color(50, 0, 0, 0));
        strip1.setPixelColor(5, strip1.Color(50, 0, 0, 0));
        strip1.setPixelColor(6, strip1.Color(50, 0, 0, 0));
        strip1.setPixelColor(8, strip1.Color(50, 0, 0, 0));
        strip1.setPixelColor(15, strip1.Color(50, 0, 0, 0));
        strip1.setPixelColor(16, strip1.Color(50, 0, 0, 0));
        strip1.setPixelColor(18, strip1.Color(50, 0, 0, 0));
        strip1.setPixelColor(21, strip1.Color(0, 0, 50, 0));
        strip1.show();

        strip2.setPixelColor(3, strip1.Color(1, 0, 0, 0));
        strip2.setPixelColor(5, strip1.Color(1, 0, 0, 0));
        strip2.setPixelColor(6, strip1.Color(1, 0, 0, 0));
        strip2.show();

        strip3.setPixelColor(3, strip1.Color(1, 0, 0, 0));
        strip3.setPixelColor(5, strip1.Color(1, 0, 0, 0));
        strip3.setPixelColor(6, strip1.Color(1, 0, 0, 0));
        strip3.show();
      }
      break;
    case 4:
      // mode 3
      if (update == 1) {
        update = 0;
        all_black_init_led();
        Serial.println("MODE 4");
        strip1.setPixelColor(4, strip1.Color(0, 90, 0, 0));
        strip1.setPixelColor(5, strip1.Color(0, 90, 0, 0));
        strip1.setPixelColor(6, strip1.Color(0, 90, 0, 0));
        strip1.setPixelColor(8, strip1.Color(0, 90, 0, 0));
        strip1.setPixelColor(15, strip1.Color(0, 90, 0, 0));
        strip1.setPixelColor(16, strip1.Color(0, 90, 0, 0));
        strip1.setPixelColor(18, strip1.Color(0, 90, 0, 0));
        strip1.setPixelColor(21, strip1.Color(0, 0, 50, 0));
        strip1.show();

        strip2.setPixelColor(3, strip1.Color(0, 10, 0, 0));
        strip2.setPixelColor(5, strip1.Color(0, 10, 0, 0));
        strip2.setPixelColor(6, strip1.Color(0, 10, 0, 0));
        strip2.show();

        strip3.setPixelColor(3, strip1.Color(0, 10, 0, 0));
        strip3.setPixelColor(5, strip1.Color(0, 10, 0, 0));
        strip3.setPixelColor(6, strip1.Color(0, 10, 0, 0));
        strip3.show();
      }
      break;
    case 5:
      // mode 4 animation
      if (update == 1) {
        update = 0;
        Serial.println("MODE 5");
      }

      if (millis() > updateAnim) {
        updateAnim = millis() + PERIOD_CHANGE;
        k++;
        for (i = 0; i < MAX_LEDS; i++) {
          strip1.setPixelColor(i, strip1.Color(0, 0, 0, 0));
        }
        strip1.setPixelColor((k + 4) % 20, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor((k + 5) % 20, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor((k + 6) % 20, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor((k + 8) % 20, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor((k + 15) % 20, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor((k + 16) % 20, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor((k + 18) % 20, strip1.Color(0, 0, 0, 50));
        strip1.setPixelColor(21, strip1.Color(0, 0, 50, 0));
        strip1.show();

        strip2.setPixelColor(3, strip1.Color(0, 0, 0, 5));
        strip2.setPixelColor(5, strip1.Color(0, 0, 0, 5));
        strip2.setPixelColor(6, strip1.Color(0, 0, 0, 5));
        strip2.show();

        strip3.setPixelColor(3, strip1.Color(0, 0, 0, 5));
        strip3.setPixelColor(5, strip1.Color(0, 0, 0, 5));
        strip3.setPixelColor(6, strip1.Color(0, 0, 0, 5));
        strip3.show();
      }
      break;

    default:
      //eteindre toutes les leds
      if (update == 1) {
        update = 0;
        all_black();
      }
      break;
  }
}


void processInput(String input) {
  input.trim();  // Supprimer les espaces inutiles

  // Découper la chaîne d'entrée par les virgules
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  int thirdComma = input.indexOf(',', secondComma + 1);
  int fourthComma = input.indexOf(',', thirdComma + 1);
  int fifthComma = input.indexOf(',', fourthComma + 1);
  int sixthComma = input.indexOf(',', fifthComma + 1);


  if (firstComma < 0 || secondComma < 0 || thirdComma < 0 || fourthComma < 0 || fifthComma < 0 || sixthComma < 0) {

    passaccess = input.substring(0, firstComma).toInt();
    if (passaccess == passmode) {
      update = 1;
      mode = input.substring(firstComma + 1, secondComma).toInt();
    } else {
      Serial.println("Erreur: format incorrect");
    }

    return;
  }

  // Extraire les valeurs des paramètres
  int numLEDs = input.substring(0, firstComma).toInt();
  int nbBands = input.substring(firstComma + 1, secondComma).toInt();
  int ledIndex = input.substring(secondComma + 1, thirdComma).toInt();
  int red = input.substring(thirdComma + 1, fourthComma).toInt();
  int green = input.substring(fourthComma + 1, fifthComma).toInt();
  int blue = input.substring(fifthComma + 1, sixthComma).toInt();
  int white = input.substring(sixthComma + 1).toInt();

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

  if (white >= 256) {
    typeLed = 1;  //0:RGBW  1:RGB
    white = 255;
  }


  if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255 || white < 0 || white > 255) {
    Serial.println("Erreur: valeur de couleur invalide");
    return;
  }


  if (nbBands == 0) {
    // Configurer la couleur de la LED spécifiée
    strip1.setPixelColor(ledIndex, strip1.Color(green, red, blue, white));
    strip1.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 1 - RGBW");
  }
  if (nbBands == 1) {
    // Configurer la couleur de la LED spécifiée
    strip2.setPixelColor(ledIndex, strip2.Color(green, red, blue, white));
    strip2.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 2 - RGBW");
  }
  if (nbBands == 2) {
    // Configurer la couleur de la LED spécifiée
    strip3.setPixelColor(ledIndex, strip3.Color(green, red, blue, white));
    strip3.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 3 - RGBW");
  }
  if (nbBands == 3) {
    // Configurer la couleur de la LED spécifiée
    strip4.setPixelColor(ledIndex, strip4.Color(red, green, blue));
    strip4.show();
    // Retourner un accusé de réception
    Serial.println("OK: LED mise à jour BAND 4 - RGB");

    if (red == 0 and green == 0 and blue == 0) {
      //power off led uv
      Serial.println("PWER OFF LED UV");
      digitalWrite(LED_PIN_PWR_UV, LOW);  // POWER OFF LED UV

    } else {
      //power on led uv
      Serial.println("PWER LED UV");
      digitalWrite(LED_PIN_PWR_UV, HIGH);  // POWER ON LED UV
    }
  }
  delay(10);
}


/*
Si commande : 200,2025,6,0,0,0,10
numéro band = 2025 -> efface toutel les bandes
*/
void all_black(void) {

  //effacer les bands
  for (i = 0; i < MAX_LEDS; i++) {
    strip1.setPixelColor(i, strip1.Color(0, 0, 0, 0));
  }
  strip1.show();
  delay(10);

  for (i = 0; i < MAX_LEDS; i++) {
    strip2.setPixelColor(i, strip1.Color(0, 0, 0, 0));
  }
  strip2.show();
  delay(10);

  for (i = 0; i < MAX_LEDS; i++) {
    strip3.setPixelColor(i, strip1.Color(0, 0, 0, 0));
  }
  strip3.show();
  delay(10);

  for (i = 0; i < MAX_LEDS; i++) {
    strip4.setPixelColor(i, strip1.Color(0, 0, 0));
  }
  strip4.show();
  delay(10);

  //power off led uv
  digitalWrite(LED_PIN_PWR_UV, LOW);  // POWER OFF LED UV
}




void all_black_init_led(void) {

  //effacer les bands
  for (i = 0; i < MAX_LEDS; i++) {
    strip1.setPixelColor(i, strip1.Color(0, 0, 0, 0));
  }

  for (i = 0; i < MAX_LEDS; i++) {
    strip2.setPixelColor(i, strip1.Color(0, 0, 0, 0));
  }

  for (i = 0; i < MAX_LEDS; i++) {
    strip3.setPixelColor(i, strip1.Color(0, 0, 0, 0));
  }

  for (i = 0; i < MAX_LEDS; i++) {
    strip4.setPixelColor(i, strip1.Color(0, 0, 0));
  }

  //power off led uv
  digitalWrite(LED_PIN_PWR_UV, LOW);  // POWER OFF LED UV
}


