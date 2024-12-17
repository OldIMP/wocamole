/**
 * AufTastenDruck -
 * Beispiel für den KosmoBits-Controller mit
 * dem Interaction-Board.
 * 
 * Felix Homann, 2015
 * 
 * Dieser Code darf auf jede erdenkliche Weise frei verwendet, verteilt
 * und kopiert werden werden.
 */


#include <Adafruit_NeoPixel.h>
#include <KosmoBits_Pixel.h>
#include <KosmoBits_Pins.h>

const int taste1 = KOSMOBITS_TASTE_1_PIN;
const int taste2 = KOSMOBITS_TASTE_2_PIN;

int rot = 0;
int gruen = 0;
int blau = 0;
const int helligkeit = 50;

KosmoBits_Pixel pixel;

void setup() {
  pinMode(taste1, INPUT);
  pinMode(taste2, INPUT);
}

void loop() {
  
  if (digitalRead(taste1) == LOW) {
    rot = 255;
  } else {
    rot = 0;
  }

  if (digitalRead(taste2) == LOW) {
    blau = 255;
  } else {
    blau = 0;
  }
  pixel.setColor(rot, gruen, blau, helligkeit);
  
  delay(50);
}
