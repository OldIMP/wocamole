/**
 * KosmoBits - FingerDisko
 */
#include <Adafruit_NeoPixel.h>
#include <KosmoBits_Pins.h>
#include <KosmoBits_Pixel.h>

const int sensorPin = KOSMOBITS_SENSOR_PIN;
KosmoBits_Pixel pixel;

int ruhewert = 0;

/*
 * Misst 20-mal den aktuellen Sensorwert und bestimmt
 * Mittelwert.
 */
int bestimmeRuhewert() {
  const int N = 20; // Zahl der Messwerte
  float mittelwert = 0;
  for (int i = 0; i < 20; ++i) {
    mittelwert = mittelwert + analogRead(sensorPin);
    delay(10);
  }
  mittelwert = mittelwert / N;
  return mittelwert;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  pixel.setColor(0, 0, 0, 0);
  ruhewert = bestimmeRuhewert();
}

void loop() {
  int wert = analogRead(sensorPin);
  int differenz;
  if (wert >= ruhewert) {
    differenz = wert - ruhewert;
  } else {
    differenz = ruhewert - wert;
  }
  
  pixel.setColor(2 * differenz, 100 - 2 * differenz,0, differenz);
  delay(10);
}



