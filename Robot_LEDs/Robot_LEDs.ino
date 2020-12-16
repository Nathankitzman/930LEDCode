//Required libraries to run leds
#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <FastLED.h>
#include "ColorManager.h"

//Values presets for team set
#define RED_TEAM 0
#define BLUE_TEAM 1
//Values when accessing array for HSV values
#define HUE 0
#define SAT 1
#define VAL 2

//Defined strip data
#define STRIP_LEDS 60
#define DATA_PIN 11
#define CLOCK_PIN 13 //Only for 4-pin Dotstar
#define STRIP_BRIGHTNESS 40 //Dotstar: , Neopixel: 

//Use listed constants to assign the ACTIVE_LEDS const
#define DOT_STAR 1 //4 pin strip 
#define NEO_PIXEL 0 //3 pin strip (WS2812B)
#define ACTIVE_LEDS NEO_PIXEL

//Parameter 1 = number of LEDs in the strip
//Parameter 2 = sets order color data is sent-rearrange if colors are not correct
//Pins are defaulted: data(green)=11; clock(yellow)=13 
Adafruit_DotStar strip(STRIP_LEDS, DOTSTAR_BGR);

//Paremeter 1 = number of LEDs in the strip
CRGB leds[STRIP_LEDS];

//Object for the custom color library
ColorManager colors;

//Starts strips for use
void setup() {
  if (ACTIVE_LEDS == DOT_STAR) {
    strip.begin();
    strip.setBrightness(STRIP_BRIGHTNESS);
  }
  else if (ACTIVE_LEDS == NEO_PIXEL) {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, STRIP_LEDS);
  }
}

//Runs functions specified on loop
void loop() {
  preset();
}

//Color set function with an LED position and all HSV values as parameters
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

//Color set function with an LED position and string representing a valid color, not case-sensitive
void colorSet(int pos, String color) {
  int* tempColor = colors.getColor(color);
  if(tempColor != NULL){
    if (ACTIVE_LEDS == DOT_STAR) {
      strip.setPixelColor(pos, strip.ColorHSV(tempColor[HUE], tempColor[SAT], tempColor[VAL]));
      strip.show();
    }
    else if (ACTIVE_LEDS == NEO_PIXEL) {
      leds[pos] = CHSV(tempColor[HUE] / 256, tempColor[SAT], tempColor[VAL]);
      FastLED.show();
    } 
  }
}

//Runs a series of presets to test all patterns
void preset() {
  for (int i=0; i< 50; i++) {
    twoColorAnimation("purple", "red", 100);
  }
  colorWipe("green", 100);
  delay(1000);
  allianceSet(RED_TEAM);
  for (int i=0; i< 2; i++) {
    rainbowWheel(50);
  }
  for (int i=0; i< 50; i++) {
    twoColorAnimation("yellow", "teal", 100);
  }
  for (int i=0; i< 3; i++) {
    movingSegment("orange", 8, 100);
  }
  for (int i=0; i< 50; i++) {
    theaterChase("white", 100);
  }
}

//Sets the strips to the alliance color
void allianceSet(int team) {
  if (team == RED_TEAM) {
    colorWipe("red", 10);
  } else if (team == BLUE_TEAM) {
    colorWipe("blue", 10);
  }
}

//Fill the dots one after the other with a color with a variable delay
void colorWipe(String color, int wait) {
  for(uint16_t i=0; i<STRIP_LEDS; i++) {
    colorSet(i, color);
    delay(wait);
  }
}

//A segment moving down the length of the LED strip and continuing from the start
void movingSegment(String color, int segLength, int wait) {
  //Changes position one over
  for(int i=0; i <= STRIP_LEDS; i++) {
    //Writes the length of the strip
    for(int j=0; j < segLength; j++) {
      //Places overflow to the beginning
      if(j+i<STRIP_LEDS) {
        colorSet(j + i, color);
      } else {
        //colorSet((j+i), ColorManagerOBJ.getColor("red")[HUE], ColorManagerOBJ.getColor("red")[SAT], ColorManagerOBJ.getColor("red")[VAL];
        colorSet((j + i) - STRIP_LEDS, color);
      }
    }
    
    delay(wait);
    strip.clear();
  }
}

//A segment moving down the length of the LED strip and continuing from the start
//Needs to be worked on
/*
void movingPong(String color, int segLength, int wait) {
  //Changes position one over
  for(int i=0; i <= STRIP_LEDS-segLength; i++) {
    //Writes the length of the strip
    for(int j=0; j < segLength; j++) {
      colorSet(j + i, color);
    }
    
    delay(wait);
    strip.clear();
  }
  //changes direction
  for(int i=0; i <= STRIP_LEDS; i++) {
    //Writes the length of the strip
    for(int j=0; j < segLength; j++) {
      //Places overflow to the beginning
      if(j+i<STRIP_LEDS) {
        colorSet(j + i, color);
      } else {
        colorSet((j + i) - STRIP_LEDS, color);
      }
    }
    
    delay(wait);
    strip.clear();
  }
}*/

//Alternates two colors along the strip
void twoColorAlt(String color1, String color2) {
  String twoColors[2] = {color1, color2};
  //Changes between both colors
  for(int i=0; i < STRIP_LEDS; i++) {
    colorSet(i, twoColors[i%2]);
  }
}

//Alternates two colors along the strip and swaps their position at a given speed
void twoColorAnimation(String color1, String color2, int wait) {
  //Shifts pattern back and forth
  twoColorAlt(color1, color2);
  delay(wait);
  twoColorAlt(color2, color1);
  delay(wait);
}

//Theatre-style crawling lights with custom color
void theaterChase(uint32_t color, int wait) {
  //Shifts pattern over
  for(int j=0; j <= 3; j++) {
    //Fills every third LED
    for (int i=j; i < STRIP_LEDS; i+=3) {
      strip.setPixelColor(i, color);
    }
    delay(wait);
    strip.clear();
  }
}

/*
 * this is the start of the theaterChaseRainbow using HSV
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow2(int wait) {
  //Splits hue spectrum equally to all pixels
  uint16_t dif = 65536/(STRIP_LEDS*3);
  //Shifts pattern over
  for(int j=0; j <= 3; j++) {
    //Fills every 3 LEDs
    for (int i=j; i < STRIP_LEDS; i+=3) {
      strip.setPixelColor(i, color);
    }
    
    delay(wait);
    strip.clear();
        //Wraps pattern to create a "wheel"
        if (i+k < STRIP_LEDS) {
          strip.setPixelColor(i+k, strip.ColorHSV((i*dif)+j, 255, 255));
        } else {
          strip.setPixelColor((i+k)-STRIP_LEDS, strip.ColorHSV((i*dif)+j, 255, 255));
        }
  }
}
*/

//Slightly different, this makes the rainbow equally distributed throughout
void rainbowWheel(int wait) {
  //Splits hue spectrum equally to all pixels
  uint16_t dif = 65536/STRIP_LEDS;
  //Shifts LEDs backwards to keep fluid motion
  for(int k=0; k < STRIP_LEDS; k++) {
    //Adjusts color slowly
    for(int j=0; j < dif; j+=1000) {
      //Fills all LEDs in the strip
      for(int i=0; i < STRIP_LEDS; i++) {
        //Wraps pattern to create a "wheel"
        if (i-k >= 0) {
          colorSet(i-k, (i*dif)+j, 255, 255);
        } else {
          colorSet((i-k)+STRIP_LEDS, (i*dif)+j, 255, 255);
        }
      }
      
      delay(wait);
    }
  }
}


//Theatre-style crawling lights with rainbow effect
//Old theater chase rainbow-being used as template for HSV conversion
/*
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {      //cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < STRIP_LEDS; i=i+3) {
        Wheel( (i+j) % 255)
      }
      
      delay(wait);
      for (uint16_t i=0; i < STRIP_LEDS; i=i+3) {
        colorSet(i+q, "kill me");        //turn every third pixel off
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
}*/
