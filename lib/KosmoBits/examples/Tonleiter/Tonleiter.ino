
#include <KosmoBits_Pins.h>

const int buzzerPin = KOSMOBITS_BUZZER_PIN;
const int freqGrundton = 220; // Das ist der Ton A.

float tonleiter[] = {1.f, 9.f/8, 5.f/4, 4.f/3, 3.f/2, 5.f/3, 15.f/8, 2.f};

void setup() {
 for (int i = 0; i < 8; ++i) {
    tone(buzzerPin, tonleiter[i] * freqGrundton);
    delay(500);
  }
  noTone(buzzerPin);
}

void loop() {
  // Hier wird nichts gemacht.
}
