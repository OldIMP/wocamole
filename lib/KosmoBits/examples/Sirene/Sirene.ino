#include <KosmoBits_Pins.h>

const int buzzerPin = KOSMOBITS_BUZZER_PIN;
const int FREQ_MIN = 440;
const int FREQ_MAX = 660;
const int DELAY = 4;

int freq = FREQ_MIN; // Frequenz des Tones, der ausgegeben wird.

void setup() {
  // Nichts zu tun
}

void loop() {
  tone(buzzerPin, freq);
  delay(DELAY);
  ++freq;
  if (freq > FREQ_MAX) {
    freq = FREQ_MIN;
  }
}
