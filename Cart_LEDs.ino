//Required libraries to run leds
#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <FastLED.h>

//Defined values
#define STRIP_LEDS 60
#define DATA_PIN 11

#define DOT_STAR 1
#define NEO_PIXEL 0

#define ACTIVE_LEDS DOT_STAR

#define RED_TEAM 0
#define BLUE_TEAM 1
//#define HUE 0
//#define SAT 1
//#define VAL 2

//Parameter 1 = number of LEDs in the strip
//Parameter 2 = sets order color data is sent-rearrange if colors are not correct
//Pins are defaulted: data(green)=11; clock(yellow)=13 
Adafruit_DotStar strip(STRIP_LEDS, DOTSTAR_BGR);

//Paremeter 1 = number of LEDs in the strip
CRGB leds[STRIP_LEDS];

//Preset colors
uint32_t red = strip.gamma32(strip.ColorHSV(0, 255, 255));
uint32_t red_orange = strip.gamma32(strip.ColorHSV(2500, 255, 255));
uint32_t orange = strip.gamma32(strip.ColorHSV(4000, 255, 255));
uint32_t yellow_orange = strip.gamma32(strip.ColorHSV(7000, 255, 255));
uint32_t gold = strip.gamma32(strip.ColorHSV(26760, 255, 255));
uint32_t yellow = strip.gamma32(strip.ColorHSV(10800, 255, 255));
uint32_t yellow_green = strip.gamma32(strip.Color(28, 50, 0));
uint32_t green = strip.gamma32(strip.Color(0, 50, 0));
uint32_t teal = strip.gamma32(strip.Color(0, 50, 25));
int blue = strip.gamma32(strip.Color(43690, 255, 255));
uint32_t purple = strip.gamma32(strip.Color(25, 0, 50));
uint32_t violet = strip.gamma32(strip.Color(30, 15, 40));
uint32_t white = strip.gamma32(strip.Color(0, 0, 255));
uint32_t black = strip.ColorHSV(0, 0, 0);

//Starts strips for use
void setup() {
  if (ACTIVE_LEDS == DOT_STAR) {
    strip.begin();
    strip.setBrightness(50);
    strip.show(); 
  }
  else if (ACTIVE_LEDS == NEO_PIXEL) {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, STRIP_LEDS);
  }
}

//Runs function specified
void loop() {
  preset();
}

void colorSet(int pos, uint16_t Hue, uint8_t Saturation, uint8_t Value) {
  if (ACTIVE_LEDS == DOT_STAR) {
    strip.setPixelColor(pos, strip.ColorHSV(Hue, Saturation, Value));
    strip.show();
  }
  else if (ACTIVE_LEDS == NEO_PIXEL) {
    leds[pos] = CHSV(Hue / 257, Saturation, Value);
    FastLED.show();
  }
}

void preset() {
  for (int i=0; i< 50; i++) {
    twoColorAnimation(purple, red, 100);
  }
  colorWipe(green, 100);
  delay(1000);
  for (int i=0; i< 2; i++) {
    rainbowWheel(50);
  }
  for (int i=0; i< 50; i++) {
    twoColorAnimation(yellow, teal, 100);
  }
  for (int i=0; i< 3; i++) {
    movingSegment(orange, 8, 100);
  }
  for (int i=0; i< 50; i++) {
    theaterChase(white, 100);
  }
}

//Sets the strips to the alliance color
void allianceSet(int team) {
  if (team == RED_TEAM) {
    colorWipe(red, 10);
  } else if (team == BLUE_TEAM) {
    colorWipe(blue, 10);
  }
}

//Fill the dots one after the other with a color with a variable delay
void colorWipe(uint32_t color, int wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

//A segment moving down the length of the LED strip and continuing from the start
void movingSegment(uint32_t color, int segLength, int wait) {
  //Changes position one over
  for(int i=0; i <= strip.numPixels(); i++) {
    //Writes the length of the strip
    for(int j=0; j < segLength; j++) {
      //Places overflow to the beginning
      if(j+i<strip.numPixels()) {
        strip.setPixelColor(j + i, color);
      } else {
        //colorSet((j+i), ColorManagerOBJ.getColor("red")[HUE], ColorManagerOBJ.getColor("red")[SAT], ColorManagerOBJ.getColor("red")[VAL];
        strip.setPixelColor((j + i) - strip.numPixels(), color);
      }
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
}

//A segment moving down the length of the LED strip and continuing from the start
void movingPong(uint32_t color, int segLength, int wait) {
  //Changes position one over
  for(int i=0; i <= strip.numPixels()-segLength; i++) {
    //Writes the length of the strip
    for(int j=0; j < segLength; j++) {
      strip.setPixelColor(j + i, color);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  //changes direction
  for(int i=0; i <= strip.numPixels(); i++) {
    //Writes the length of the strip
    for(int j=0; j < segLength; j++) {
      //Places overflow to the beginning
      if(j+i<strip.numPixels()) {
        strip.setPixelColor(j + i, color);
      } else {
        strip.setPixelColor((j + i) - strip.numPixels(), color);
      }
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
}

//Alternates two colors
void twoColorAlt(uint32_t color1, uint32_t color2) {
  uint32_t twoColors[2] = {color1, color2};
  //Changes between both colors
  for(int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, twoColors[i%2]);
  }
  strip.show();
}

//Alternates two colors and swaps their position
void twoColorAnimation(uint32_t color1, uint32_t color2, int wait) {
  //Shifts pattern back and forth
  twoColorAlt(color1, color2);
  strip.show();
  delay(wait);
  twoColorAlt(color2, color1);
  strip.show();
  delay(wait);
}

//Theatre-style crawling lights with custom color
void theaterChase(uint32_t color, int wait) {
  //Shifts pattern over
  for(int j=0; j <= 3; j++) {
    //Fills every 3 LEDs
    for (int i=j; i < strip.numPixels(); i+=3) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
}

/*
 * this is the start of the theaterChaseRainbow using HSV
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow2(int wait) {
  //Splits hue spectrum equally to all pixels
  uint16_t dif = 65536/(strip.numPixels()*3);
  //Shifts pattern over
  for(int j=0; j <= 3; j++) {
    //Fills every 3 LEDs
    for (int i=j; i < strip.numPixels(); i+=3) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(wait);
    strip.clear();
        //Wraps pattern to create a "wheel"
        if (i+k < strip.numPixels()) {
          strip.setPixelColor(i+k, strip.ColorHSV((i*dif)+j, 255, 255));
        } else {
          strip.setPixelColor((i+k)-strip.numPixels(), strip.ColorHSV((i*dif)+j, 255, 255));
        }
  }
}
*/

//Slightly different, this makes the rainbow equally distributed throughout
void rainbowWheel(int wait) {
  //Splits hue spectrum equally to all pixels
  uint16_t dif = 65536/strip.numPixels();
  //Shifts LEDs backwards to keep fluid motion
  for(int k=0; k < strip.numPixels(); k++) {
    //Adjusts color slowly
    for(int j=0; j < dif; j+=1000) {
      //Fills all LEDs in the strip
      for(int i=0; i < strip.numPixels(); i++) {
        //Wraps pattern to create a "wheel"
        if (i-k >= 0) {
          strip.setPixelColor(i-k, strip.ColorHSV((i*dif)+j, 255, 255));
        } else {
          strip.setPixelColor((i-k)+strip.numPixels(), strip.ColorHSV((i*dif)+j, 255, 255));
        }
      }
      strip.show();
      delay(wait);
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {      //cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

 //Input a value 0 to 255 to get a color value.
 //The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}