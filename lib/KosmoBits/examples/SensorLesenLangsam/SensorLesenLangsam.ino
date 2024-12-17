/*
 * KosmoBits - SensorLesenLangsam
 * 
 */
 
#include <KosmoBits_Pins.h>

const int sensorPin = KOSMOBITS_SENSOR_PIN;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  int wert = analogRead(sensorPin);

 
  Serial.print("Messwert: ");
  Serial.println(wert);
  delay(500);
}
