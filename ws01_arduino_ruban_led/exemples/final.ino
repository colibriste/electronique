#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <math.h>

#define PIN 6
#define EVERY_NTH 1
// #define NB_LED 180
// #define NB_LED 90
/* #define NB_LED 144 */
#define NB_LED 100
#define BRIGHTNESS 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NB_LED, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

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


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t my_color(byte colorWheelPos, float d)
{
  uint32_t c1;

  colorWheelPos = 255 - colorWheelPos;
  if(colorWheelPos < 85) {
    c1 = strip.Color(d * (255 - colorWheelPos * 3), 0, d * colorWheelPos * 3);
  } else if(colorWheelPos < 170) {
    colorWheelPos -= 85;
    c1 = strip.Color(0, d * (colorWheelPos * 3), d * (255 - colorWheelPos * 3));
  } else {
    colorWheelPos -= 170;
    c1 = strip.Color(d * (colorWheelPos * 3), d * (255 - colorWheelPos * 3), 0);
  }

  // c1 = strip.Color(d * 255, 0, 0);

  return c1;
}

float angle = 0;

void okapi(float speed, byte colorWheelPos, float n_waves, float sin_offset, float divisor, int every_nth) {
  uint16_t i, j;
  uint32_t c1, c2;

  // // c1 = strip.Color();
  // c1 = 0x00001000;
  // c2 = 0x00800000;
  double d;

  Serial.print("Hue = ");
  Serial.println(colorWheelPos);

  for (angle=-PI; angle<PI; angle += 1 / speed) {
    for(i=0; i< strip.numPixels(); i++) {


      d = (sin(i * 2 * n_waves * PI / strip.numPixels() + angle) + sin_offset) / divisor;
      if (d < 0) {
        d = 0;
      }
      if (d > 1) {
        d = 1;
      }

      if (i % every_nth) {
        c1 = 0;
      } else {
        // c1 = strip.Color(d * 255, d * 255, d * 255);
        c1 = my_color(colorWheelPos+i, d);
        // c1 = 0x000000ff;
      }

      strip.setPixelColor(i, c1);
    }
    strip.show();
  }

  // for(i=0; i< strip.numPixels(); i++) {
  //   for(j=0; j< strip.numPixels(); j++) {
  //     strip.setPixelColor(j, j == i ? c2 : c1);
  //   }
  //   strip.show();
  //   delay(wait);
  // }
  // // delay(wait);
}

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  Serial.begin(115200);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // rainbowCycle(20);
  int hue = 0;
  int i;

  for (int i = 1; i < strip.numPixels(); i++) {
    Serial.print("Waves = ");
    Serial.println(i);

    for (hue = 0; hue < 256; hue += 16) {
      okapi(4, hue,
             i, // n_wave
          0, // sin_offset
          1, // divisor
          1 // every_nth
      );
      delay(100);
    }
  }
  delay(3000);
  // delay(7000);
  // okapi(1);
}
