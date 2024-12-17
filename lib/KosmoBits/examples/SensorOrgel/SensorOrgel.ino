#include <KosmoBits_Pins.h>

const int sensorPin = KOSMOBITS_SENSOR_PIN;
const int buzzerPin = KOSMOBITS_BUZZER_PIN;
const int tasterPin = KOSMOBITS_TASTE_2_PIN;

const float tonleiter[] = {1.f, 9.f/8, 5.f/4, 4.f/3, 3.f/2, 5.f/3, 15.f/8, 2.f};
const int freqGrundton = 220; // Das ist der Ton A.

const int messwertMin = 300;
const int messwertMax = 400;
const int skalierung = (messwertMax - messwertMin) / 9;

const int N = 10; // Anzahl der Werte, die gemittelt werden
int werte[N] = {}; // Hier werden die letzten 10 Werte gespeichert.
int index = 0;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(tasterPin, INPUT);
}

void loop() {
  // Lese einen neuen Wert vom Sensor und speichere ihn in werte[]
  werte[index] = analogRead(sensorPin);
  
  // Erhöhe den Index um 1, damit der nächste Wert an der nächsten Stelle
  // im Feld werte[] gespeichert werden kann
  ++index;

  // Wenn index == N ist, ist das Array voll beschrieben.
  // index wird dann auf 0 gesetzt, damit im nächsten Durchlauf
  // der älteste Wert überschrieben wird. 
  if (index == N) {
      index = 0;
  }

  // Jetzt wird der Mittelwert der letzten N Messwerte berechnet
  int mittelwert  = 0; // Starte mit dem Wert 0

  // Summiere die letzten 10 gemessenen Werte.
  for (int i = 0; i < N; ++i) {
    mittelwert = mittelwert + werte[i];
  }
  // Teile die Summe durch die Zahl der Werte.
  mittelwert = mittelwert / N;  
  
  int tonIndex = (mittelwert - messwertMin) / skalierung;

  // tonIndex darf nicht kleiner 0 und nicht größer 7 sein:
  if (tonIndex < 0) {
    tonIndex = 0;
  } else if (tonIndex > 7) {
    tonIndex = 7;
  }
  
  // Ton ausgeben
  if (digitalRead(tasterPin) == LOW) {
    tone(buzzerPin, tonleiter[tonIndex] * freqGrundton);
    delay(10);
  } else {
    noTone(buzzerPin);
    delay(1);
  }
}
