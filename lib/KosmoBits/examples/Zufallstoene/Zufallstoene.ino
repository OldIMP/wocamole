
#include <KosmoBits_Pins.h>

const int buzzerPin = KOSMOBITS_BUZZER_PIN;

void setup() {
  randomSeed(analogRead(12));
}

void loop() {
  int freq = random(110,1000);
  int dauer = random(10, 150);
  tone(buzzerPin,freq);
  delay(dauer);
}
