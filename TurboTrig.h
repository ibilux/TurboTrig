/*
==============================================================
 TurboTrig Library
==============================================================
 i.bilux@gmail.com (C) 2015
 
 This is a library to quickly do common trigonometry functions
 on Arduinos/other microprocessors.
 
 This is the main header file.
==============================================================
*/

//Include Guard:
#ifndef TurboTrig_h
#define TurboTrig_h

//Arduino libraries:
#include "Arduino.h"

class Speed_Trig {
  public:
    Speed_Trig();
    int floatToInt(float input);
    float sin(float rad);
    float cos(float rad);
    float sinx(int deg);
    float cosx(int deg);
    float acos(float num);
	float asin(float num);
    float atan(float opp, float adj);
};

//Create class to use:
extern Speed_Trig TurboTrig;

#endif //#ifndef TurboTrig_h

