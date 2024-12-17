/**
 * Klatschschalter
 * 
 */

#include <KosmoBits_Pins.h>
#include <Adafruit_NeoPixel.h>
#include <KosmoBits_Pixel.h>

const int sensorPin = KOSMOBITS_SENSOR_PIN;
const int schwelle = 500;

KosmoBits_Pixel pixel;

bool an = false;

void setup() {
  pinMode(sensorPin, INPUT);
  pixel.setColor(0, 0, 0, 0);
}

void loop() {
  int sensorWert = analogRead(sensorPin);
  Serial.println(sensorWert);
  if (sensorWert > schwelle) {
    umschalten();
    delay(200);
  }
}

void umschalten() {
  if (an) {
    pixel.setColor(0, 0, 0, 0);
    an = false;
  } else {
    pixel.setColor(255, 0, 0, 30);
    an = true;
  }
}

