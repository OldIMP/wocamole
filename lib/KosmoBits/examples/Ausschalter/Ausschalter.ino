/**
 * Ausschalter -
 * Die LED auf dem KosmoBits-Controller wird  mit Hilfe
 * eines Jumper Kabels ein und ausgeschaltet.
 * 
 * Um die LED auszuschalten, muss Pin 9 mit einem der Gnd
 * Pins verbunden werden.
 * 
 */

int ledPin = 13;
int schalterPin = 9;
int schalterWert = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(schalterPin, INPUT_PULLUP);
}

void loop() {
  schalterWert = digitalRead(schalterPin);
  digitalWrite(ledPin, schalterWert);
  
  delay(50);
}
