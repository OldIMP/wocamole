/**
 * BlinkWuerfel
 * 
 * (c) Felix Homann
 */

#include <KosmoBits_Pins.h>
#include <Adafruit_NeoPixel.h>
#include <KosmoBits_Pixel.h>

KosmoBits_Pixel pixel;

const int tasterPin = KOSMOBITS_TASTE_1_PIN;
const int blinkDauer = 500; // Millisekunden
const int blinkPause = 250; // Millisekunden
const int helligkeit = 50;


void setup() {
  pinMode(tasterPin, INPUT);
  randomSeed(analogRead(12)); // Startwert für Zufallsgenerator 
  pixel.setColor(0, 0, 255, helligkeit); // Blau signalisiert Betriebsbereitschaft
}

void loop() {
  if (digitalRead(tasterPin) == LOW) {
    wuerfeln();
  }
  
}

void wuerfeln() {
  // Erst einmal Licht aus, um zu zeigen, dass
  // auf den Tastendruck reagiert wird.
  pixel.setColor(0, 0, 0, 0); // Licht aus
  delay(500);
  
  // Erzeuge Zufallszahl
  int zahl = random(1, 7); // Zahlen >= 1 und < 7

  // Blinke (zahl - 1)-mal
  for (int i = 0; i < zahl - 1; ++i) {
    pixel.setColor(0, 255, 0, helligkeit); // Grün
    delay(blinkDauer);
    pixel.setColor(0, 0, 0, 0); // Licht aus
    delay(blinkPause);
  }
  
  // Blinke noch einmal, so dass insgesamt zahl-mal
  // geblinkt wurde
  pixel.setColor(0, 255, 0, helligkeit); // Grün
  delay(2 * blinkDauer); // Letztes Blinken doppelt so lange.
  pixel.setColor(0, 0, 0, 0); // Licht aus

  // Abschluss des Würfelns signalisieren.
  delay(blinkDauer); // Pause am Ende etwas länger
  pixel.setColor(0, 0, 255, helligkeit); // Blau signalisiert Betriebsbereitschaft
}

