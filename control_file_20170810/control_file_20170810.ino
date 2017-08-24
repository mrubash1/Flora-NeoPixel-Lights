// Import library
#include <Adafruit_NeoPixel.h>

#define PIN 6

//Configuration
uint8_t Brightness = 20;
uint8_t Pixels = 71;
uint8_t SingleColorCycleSpeed = 30;
uint8_t RainbowColorCycleSpeed = 15;

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
  // Some example procedures showing how to display to the pixels:
  // From August 10th, 2017
  rainbowCycle(RainbowColorCycleSpeed);
  flash(10,10,15,255,0,0); //flash red
  rainbowCycle(RainbowColorCycleSpeed);
  colorWipe(strip.Color(153, 0, 255), SingleColorCycleSpeed); // scroll Purple
  rainbow(RainbowColorCycleSpeed);
  rainbowCycle(RainbowColorCycleSpeed);
  flash(10,10,15,255,255,0); //flash yellow
  rainbowCycle(RainbowColorCycleSpeed);
  colorWipe(strip.Color(255, 0, 255), SingleColorCycleSpeed); // scroll Pink
  rainbowCycle(RainbowColorCycleSpeed);
  flash(10,10,15,255,0,153); //flash orange
}

void flash(uint8_t speed, uint8_t cycles, uint8_t wait, uint8_t r, uint8_t g, uint8_t b) {
  uint16_t i,j,k;
  for(k=0; k<cycles; k++) {
    for(j=0; j<(256/speed); j++) {
      for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color((j*speed % 255) * r/255, (j*speed % 255) * g/255, (j*speed % 255) * b/255));
      }
      delay(wait);
      strip.show();
    }
  }
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

  for(j=0; j<256; j++) {
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