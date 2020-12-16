#ifndef ColorManager_h
#define ColorManager_h

#include "Arduino.h"

//Defines all members of the class
class ColorManager
{
  public:
    ColorManager();
    int* getColor(String color);
  private:
    int red[3];
    int red_orange[3];
    int orange[3];
    int yellow_orange[3];
    int gold[3];
    int yellow[3];
    int yellow_green[3];
    int green[3];
    int teal[3];
    int blue[3];
    int purple[3];
    int violet[3];
    int white[3];
    int black[3];
};

#endif
