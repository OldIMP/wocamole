/*
 * KosmoBits - Schubladenwächter
 * 
 * (c) 2015, Felix Homann
 * 
 */
 
#include <Adafruit_NeoPixel.h>
#include <KosmoBits_Pins.h>
#include <KosmoBits_Pixel.h>

const int sensorPin = KOSMOBITS_SENSOR_PIN;
const int taste1Pin = KOSMOBITS_TASTE_1_PIN;
const int taste2Pin = KOSMOBITS_TASTE_2_PIN;

int taste1 = HIGH;
int taste2 = HIGH;
int sensorWert = 0;

enum Modus {LEERLAUF, COUNTDOWN, WARTE_BIS_DUNKEL, GESCHLOSSEN, OFFEN};
Modus modus = LEERLAUF;

const int DUNKEL_WERT = 5; // Ist der Sensorwert größer als DUNKEL_WERT,
                             // gilt die Schublade als offen.
unsigned long zaehler = 0;   // Zählt, wie oft geöffnet wurde
KosmoBits_Pixel pixel;

// Setzt in den Grundzustand zurück
void reset() {
  pixel.setColor(0, 0, 0, 0); // Pixel aus
  modus = LEERLAUF;
  zaehler = 0;
  Serial.println("Reset!");
}

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(taste1Pin, INPUT);
  pinMode(taste2Pin, INPUT);
  Serial.begin(115200);
  reset(); // zurück setzen, siehe unten
}

/**
 * Die Hauptschleife unterscheidet zwischen verschiedenen Betriebszuständen.
 * Der aktuelle Zustand wird in der Variablen 'modus' gespeichert.
 */
void loop() {
  switch(modus) {
  case LEERLAUF:
    loopLeerlauf();
    break;
  case COUNTDOWN:
    loopCountdown();
    break;
  case WARTE_BIS_DUNKEL:
    loopBisDunkel();
    break;
  case GESCHLOSSEN:
    loopGeschlossen();
    break;
  case OFFEN:
    loopOffen();
    break; 
  }
}



/**
 * Im Leerlauf wartet der Controller darauf, dass Taste 1 gedrückt wird.
 * Beim Loslassen der Taste startet nach einem Countdown die Überwachung.
 */
void loopLeerlauf() {
  Serial.println("Leerlauf");
  bool gedrueckt = false;
  while(digitalRead(taste1Pin) == LOW) {
    // Taste 1 wurde gedrückt. 
    // Warte, bis sie wieder losgelassen wird.
    pixel.setColor(0, 0, 255, 25);
    gedrueckt = true;
    delay(50);
  }
  if (gedrueckt) {
    modus = COUNTDOWN;
  }
}

/**
 * Der NeoPixel blinkt 5-mal kurz grün und einmal lange rot,
 * bevor die Überwachung beginnt.
 */
void loopCountdown() {
  const int COUNTDOWN_ZAHL = 5;
  Serial.println("Countdown");
  pixel.setColor(0, 0, 0, 0); // Pixel aus
  delay(500);
  // Der eigentliche Countdown: Wie Blink.
  for (int i = 0; i < COUNTDOWN_ZAHL; ++i) {
    pixel.setColor(0, 255,0, 25); // Grün
    delay(500);
    pixel.setColor(0, 0, 0, 0); // Pixel aus
    delay(500);
  }
  pixel.setColor(255, 0, 0, 25); // Rot
  delay(1000);
  pixel.setColor(0, 0, 0, 0); // Pixel aus
  modus = WARTE_BIS_DUNKEL;
}

/**
 * Ist der Countdown abgelaufen, wartet der Controller mit der Überwachung noch, bis
 * es dunkel ist.
 */
void loopBisDunkel() {
  Serial.println("Warte bis dunkel");
  
  while (analogRead(sensorPin) > DUNKEL_WERT) {
    delay(10);
  }
  modus = GESCHLOSSEN;
  delay(1000);
}


/**
 * Die ist die eigentliche Überwachungsschleife.
 */
void loopGeschlossen() {
  Serial.println("Im Dunkeln.");
  sensorWert = analogRead(sensorPin);
  if (sensorWert < DUNKEL_WERT) {  // Es ist noch dunkel
    delay(1000); // Warte 1 Sekunde, loop() ruft diese Funktion dann wieder auf.
  } else {
    // Es ist hell! Kontrolliere nach 0,5 Sekunden noch einmal
    delay(500); 
    if (analogRead(sensorPin) >= DUNKEL_WERT) {
      // Es ist hell:Schublade geöffnet!
      modus = OFFEN;
    }
  }
}

/**
 * Die Schublade wurde geöffnet. Wenn sie wieder geschlossen wird, wird dies
 * als Öffnung gezählt. Bleibt es hell, kann mit Taste 2 die Überwachung beendet
 * und das Ergebnis ausgegeben werden.
 */
void loopOffen() {
  Serial.println("geöffnet");
  delay(50);
  taste2 = digitalRead(taste2Pin);
  sensorWert = analogRead(sensorPin);
  
  if (taste2 == LOW) {
    ausgabe();
  } else if (sensorWert < DUNKEL_WERT) {
    // Schublade wieder zu
    ++zaehler;
    modus = GESCHLOSSEN;
  }
}

/**
 * Hier wird das Ergebnis der Überwachung ausgegeben.
 * Zum einen mittels NeoPixel:
 *   - rot: Die Schublade ist geöffnet worden.
 *   - grün: Die Schublade ist nicht geöffnet worden.
 * 
 * Über den seriellen Monitor wir zusätzlich ausgegeben, wie oft
 * die Schublade geöffnet wurde.
 * 
 */
void ausgabe() {  
  Serial.print("Die Schublade wurde ");
  Serial.print(zaehler);
  Serial.print("-mal geöffnet!\n");
  if (zaehler > 0) {
    pixel.setColor(255, 0, 0, 25);
  } else {
    pixel.setColor(0, 255, 0, 25);
  }
  delay(2000);
  reset();
}



