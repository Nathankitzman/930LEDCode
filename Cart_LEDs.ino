#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <Wire.h>
//Required libraries to run leds and recieve I2C data.
#define PIN 6
#define STRIP_NUMPIXELS 55
//DA-Green-4
//CL-Yellow-5
//Parameter 1 = number of pixels in strip
//Parameter 1 = number of pixels in strip
//Parameter 2 = Arduino pin number (most are valid)
//Parameter 3 = pixel type flags, add together as needed:
Adafruit_DotStar strip(STRIP_NUMPIXELS, DOTSTAR_BGR);
uint32_t red = strip.Color(50, 0, 0);
uint32_t red_orange = strip.Color(50, 8, 0);
uint32_t orange = strip.Color(50, 13, 0);
uint32_t yellow_orange = strip.Color(50, 23, 0);
uint32_t gold = strip.Color(50, 28, 0);
uint32_t yellow = strip.Color(50, 50, 0);
uint32_t yellow_green = strip.Color(28, 50, 0);
uint32_t green = strip.Color(0, 50, 0);
uint32_t teal = strip.Color(0, 50, 25);
uint32_t blue = strip.Color(0, 10, 50);
uint32_t purple = strip.Color(25, 0, 50);
uint32_t violet = strip.Color(30, 15, 40);
uint32_t white = strip.Color(50, 50, 50);
uint32_t black = strip.Color(0, 0, 0);
int pick;
int choice;
void setup() {
  Wire.begin(4);                 //join i2c bus with address #4
  Wire.begin(84);
  Wire.onReceive(receiveEvent);  //register event
  strip.begin();
  strip.setBrightness(150);
  strip.show(); 
  
}
void loop() {
  pick = 1; 
   //Some example procedures showing how to display to the pixels:
  if(pick == 1){
  colorWipe(red, 258);
  colorWipe(red_orange, 100);
  colorWipe(orange, 100);
  colorWipe(yellow_orange, 100);
  colorWipe(gold, 100);
  colorWipe(yellow, 100);
  colorWipe(yellow_green, 100);
  colorWipe(green, 100);
  colorWipe(teal, 100);
  colorWipe(blue, 100);
  colorWipe(purple, 100);
  colorWipe(violet, 100);
  colorWipe(white, 100);
  }
  if(pick == 2){
  colorWipe(strip.Color(0, 50, 0), 50);  //Green
  }
  if(pick == 3){
  colorWipe(strip.Color(0, 0, 50), 50);  //Blue
  }
  if(pick == 4){
  theaterChase(strip.Color(5, 5, 5), 100);  //White
  }
  if(pick == 5){
  theaterChase(strip.Color(25, 0, 0), 25);  //Red
  }
  if(pick == 6){
  theaterChase(strip.Color(0, 0, 25), 25);  //Blue
  }
  if(pick == 7){
  rainbow(20);
  }
  if(pick == 8){
  rainbowCycle(20);
  }
  if(pick == 9){
  theaterChaseRainbow(5);
  }
  
}
void receiveEvent(){
 while(Wire.available())
 {
  int c = Wire.read();
  if(c == 72){
   choice = 1; 
  }
    if(c == 76){
   choice = 2; 
  }
  }
 }

 //Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
void rainbowSteps(int wait){
  int colorStep = strip.numPixels();
  strip.fill(red);
  strip.show();
  delay(1000);
  strip.fill(red_orange,4);
  strip.show();
  delay(1000);
  strip.fill(orange,8);
  strip.show();
  delay(1000);
  strip.fill(yellow_orange,12);
  strip.show();
  delay(1000);
  strip.fill(gold,16);
  strip.show();
  delay(1000);
  strip.fill(yellow,20);
  strip.show();
  delay(1000);
  strip.fill(yellow_green,24);
  strip.show();
  delay(1000);
  strip.fill(green,28);
  strip.show();
  delay(1000);
  strip.fill(teal,32);
  strip.show();
  delay(1000);
  strip.fill(blue,36);
  strip.show();
  delay(1000);
  strip.fill(purple,40);
  strip.show();
  delay(1000);
  strip.fill(violet,44);
  strip.show();
  delay(1000);
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
 //Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) {  //5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
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
