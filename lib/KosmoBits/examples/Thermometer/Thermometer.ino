#include <KosmoBits_Pins.h>
#include <KosmoBits_Thermistor.h>

const int sensorPin = KOSMOBITS_SENSOR_PIN;

void setup() {
  pinMode(sensorPin, INPUT);
  
  Serial.begin(115200); // Ausgabe über seriellen Monitor ermöglichen
}

void loop() {
  int messwert = analogRead(sensorPin);
  float celsius = thermistor_messwert_in_celsius(messwert); // Messwert in Grad Celsius umrechnen
  Serial.print(celsius); // Wert von celsius wird ausgegeben
  Serial.println("Grad Celsius"); // Ausgabe von "Grad Celsius" und Zeilenumbruch
  
  delay(1000);
}
