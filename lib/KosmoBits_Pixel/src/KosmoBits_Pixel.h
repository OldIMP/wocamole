/*
 * KosmoBits_Pixel - Bibliothek, um die Nutzung des einzelnen NeoPixels auf dem KosmoBits
 * Interaction Board zu vereinfachen. Eigentlich nur ein kleiner Wrapper für die NeoPixel
 * Bibliothek von Adafruit.
 *
 *
 * Copyright 2015: Felix Homann
 *
 * Dies ist trivialer Code unterhalb der Schöpfungshöhe und somit frei in jeder
 * Form verwendbar.
 *
 */

#ifndef KOSMOBITS_PIXEL_H
#define KOSMOBITS_PIXEL_H
#include <Adafruit_NeoPixel.h>

class KosmoBits_Pixel {
public:
  KosmoBits_Pixel();
  explicit KosmoBits_Pixel(int numPixels);
  void setColor(int rot, int gruen, int blau, int helligkeit);

private:
  Adafruit_NeoPixel _neoPixel;
  int _numPixels;
};

#endif
