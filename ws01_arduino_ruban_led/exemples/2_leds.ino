#include <Adafruit_NeoPixel.h>

#define PIN  6 // partout ou on écrira PIN on aura 6
#define BRIGHTNESS 1

// on va controler les 10 premières LED
// la guirlande est branchée sur la pin6, 
// la guirlande marche en GRB et pas en RVB
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, 6, NEO_GRB + NEO_KHZ800); 

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(BRIGHTNESS * (255 - WheelPos * 3), 0, BRIGHTNESS * WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, BRIGHTNESS * WheelPos * 3, BRIGHTNESS * (255 - WheelPos * 3));
  }
  WheelPos -= 170;
  return strip.Color(BRIGHTNESS * WheelPos * 3, BRIGHTNESS * (255 - WheelPos * 3), 0);
}



void setup()
{
   Serial.begin(115200); // initialise la liaison série pour communiquer avec l'ordi. va être utile pour afficher des messages. le nombre : c'est la vitesse en bits par secondes. On peut mettre n'importe laquelle parmi la liste du moniteur série. Si cable très long marchera pas forcément du coup  
   uint32_t couleur = strip.Color(102, 51, 51); // on déclare une couleur 
   strip.begin(); // initialise bande de LED

   // Deux manières d'assigner un couleur à une LED:
   strip.setPixelColor(0, couleur); // on set la 1ère LED de la guirlande avec la couleur déclarée au dessus
   strip.setPixelColor(1, Wheel(12)); // on set la 2ème LED de la guirlande avec cette fois-ci la fonction Wheel
   
   strip.show();
}


void loop()
{
  // écrit "allo" pleins de fois. Sert juste à comprendre comment on débuggue
  Serial.println("allo");
}
