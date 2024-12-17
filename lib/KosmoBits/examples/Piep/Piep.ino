/**
 * Piep -
 * Wie Blink nur mit Piep!
 * 
 */

#include <KosmoBits_Pins.h>

const int buzzerPin = KOSMOBITS_BUZZER_PIN;

void setup() {
  // Nichts zu tun.
}

void loop() {
  tone(buzzerPin, 440);
  delay(500);
  noTone(buzzerPin);
  delay(500);
}
