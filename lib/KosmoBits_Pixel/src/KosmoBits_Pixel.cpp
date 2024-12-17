#define PIXEL_PIN 5


#include <KosmoBits_Pixel.h>

KosmoBits_Pixel::KosmoBits_Pixel()
  : _neoPixel(1, 5, NEO_GRB + NEO_KHZ800), _numPixels(1)
{
  _neoPixel.begin();
}

KosmoBits_Pixel::KosmoBits_Pixel(int numPixels)
  : _neoPixel(numPixels, 5, NEO_GRB + NEO_KHZ800), _numPixels(numPixels)
{
  _neoPixel.begin();
}


void KosmoBits_Pixel::setColor(int rot, int gruen, int blau, int helligkeit)
{
  _neoPixel.setBrightness(helligkeit);
  for (int i = 0; i < _numPixels; ++i) {
    _neoPixel.setPixelColor(i , _neoPixel.Color(rot, gruen, blau));
  }
  _neoPixel.show();
}
