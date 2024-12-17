/** Geisteraugen (mit Geräusch)

    (c) Felix Homann, 2016
*/

#include <KosmoBits_Pins.h>

const int buzzerPin = KOSMOBITS_BUZZER_PIN;
const int rotPin = 11;
const int gruenPin = 6;

void setup() {
  randomSeed(analogRead(3));
  pinMode(rotPin, OUTPUT);
  pinMode(gruenPin, OUTPUT);
}

void loop() {
  // Blinken
  analogWrite(rotPin, random(0, 256));
  analogWrite(gruenPin, random(0, 256));
  delay(200);

  // Rauschen
  if (random(0, 1000) > 900) {
    for (int i = 0; i < 3000; ++i) {
      analogWrite(buzzerPin, random(0, 256));
    }
  }
}


