#include "Arduino.h"
#include "ColorManager.h"

//Sets all HSV presets
ColorManager::ColorManager():
  red {0, 255, 200}
  //need to update HSV values
  /*
  red_orange {2500, 255, 255},
  orange {4000, 255, 255},
  yellow_orange {7000, 255, 255},
  gold {26760, 255, 255},
  yellow {10800, 255, 255},
  yellow_green {28, 50, 0},
  green {0, 50, 0},
  teal {0, 50, 25},
  blue {43690, 255, 255},
  purple {25, 0, 50},
  violet {30, 15, 40},
  white {0, 0, 255},
  black {0, 0, 0}
  */
{}

//Associates string input to an array, not case-sensitive
int* ColorManager::getColor(String colorInput){
  //Returns a pointer to the array object
  int* color;
  if(colorInput.equalsIgnoreCase("red")) {
    color = red;
  }
  /*
  else if(colorInput.equalsIgnoreCase("red_orange")){
    color = red_orange;
  }
  else if(colorInput.equalsIgnoreCase("orange")){
    color = orange;
  }
  else if(colorInput.equalsIgnoreCase("yellow_orange")){
    color = yellow_orange;
  }
  else if(colorInput.equalsIgnoreCase("gold")){
    color = gold;
  }
  else if(colorInput.equalsIgnoreCase("yellow")){
    color = yellow;
  }
  else if(colorInput.equalsIgnoreCase("yellow_green")){
    color = yellow_green;
  }
  else if(colorInput.equalsIgnoreCase("green")){
    color = green;
  }
  else if(colorInput.equalsIgnoreCase("teal")){
    color = teal;
  }
  else if(colorInput.equalsIgnoreCase("blue")){
    color = blue;
  }
  else if(colorInput.equalsIgnoreCase("purple")){
    color = purple;
  }
  else if(colorInput.equalsIgnoreCase("violet")){
    color = violet;
  }
  else if(colorInput.equalsIgnoreCase("white")){
    color = white;
  }*/
  else{
    color = black;
  }
  return color;
}
