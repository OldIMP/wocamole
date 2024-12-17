/**
 * BuntesLicht
 * 
 * (c) Felix Homann
 */

#include <Adafruit_NeoPixel.h>
#include <KosmoBits_Pixel.h>


KosmoBits_Pixel pixel;

int rot = 0;
int gruen = 0;
int blau = 0;
int helligkeit = 0;
  
void setup() {
  // Hier ist nichts zu tun.
}

void loop() {
  // 50 ist ein guter Helligkeitswert.
  // Die höchste Helligkeitsstufe ist 255.
  // Das blendet aber schon sehr! 
  helligkeit = 50;

  // rot
  rot = 255;
  gruen = 0;
  blau = 0;
  pixel.setColor(rot, gruen, blau, helligkeit);
  delay(500);

  // grün
  rot = 0;
  gruen = 255;  
  blau = 0;
  pixel.setColor(rot, gruen, blau, helligkeit);
  delay(500);

  // blau
  rot = 0;
  gruen = 0;
  blau = 255;
  pixel.setColor(rot, gruen, blau, helligkeit);
  delay(500);

  // lila
  rot = 255;
  gruen = 0;
  blau = 255;
  pixel.setColor(rot, gruen, blau, helligkeit);
  delay(500);
  
  // türkis
  rot = 0;
  gruen = 255;
  blau = 255;
  pixel.setColor(rot, gruen, blau, helligkeit);
  delay(500);

  // gelb
  rot = 255;
  blau = 0;
  gruen = 255;
  pixel.setColor(rot, gruen, blau, helligkeit);
  delay(500);

  // weiß
  rot = 255;
  blau = 255;
  gruen = 255;
  pixel.setColor(rot, gruen, blau, helligkeit);
  delay(500);  
}
