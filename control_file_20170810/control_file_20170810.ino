// Import library
#include <Adafruit_FloraPixel.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

//Configuration
uint8_t Brightness = 30;
uint8_t Pixels = 120;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(Brightness);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  rainbowCycleFlame(5);
}

void originalLoop() {
  // Some example procedures showing how to display to the pixels:
  // From August 10th, 2017
  colorWipe(strip.Color(255, 0, 0), 25); // Red
  rainbowCycle(1);
  colorWipe(strip.Color(0, 255, 0), 25); // Green
  rainbow(5);
  colorWipe(strip.Color(0, 0, 255), 25); // Blue
  rainbow(5);
  colorWipe(strip.Color(255, 255, 0), 25);
  rainbow(5); 
  colorWipe(strip.Color(0, 255, 255), 25);
  rainbow(5);
  colorWipe(strip.Color(255, 0, 255), 25);
  rainbowCycle(1);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
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

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

//
//FOR FLAME JACKET
//

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t WheelFlame(byte WheelPos) {
  if(WheelPos < 127.5) {
   return strip.Color(WheelPos * 2, 255 - WheelPos * 2, 0);
  } else {
   WheelPos -= 127.5;
   return strip.Color(255 - WheelPos * 2, WheelPos * 2, 0);
  }
}

void rainbowFlame(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, WheelFlame((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycleFlame(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, WheelFlame(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
