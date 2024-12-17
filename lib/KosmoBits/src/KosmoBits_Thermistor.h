#ifndef KOSMOBITS_THERMISTOR
#define KOSMOBITS_THERMISTOR

#include <math.h>

const float thermistor_messwert_in_celsius(int messwert) {
  const float R1 = 10000.f;
  const float B = 3950.f;
  const float T0 = 273.15; // 0° Celsius in Kelvin
  const float T25 = 25 + T0; // 25° Celsius in Kelvin
  const float R25 = 5000.f;

  float Rt = R1 * (1023.f / messwert - 1); // Thermistor-Widerstand
  float temperatur = 1.f / T25 + 1.f / B  * log(Rt/R25); // Kehrwert der Temperatur
                                                         // in Kelvin
  temperatur = 1.0 / temperatur - T0; // Celsius
  return temperatur;
}

#endif
