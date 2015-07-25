/*
==============================================================
 TurboTrig Library
==============================================================
 i.bilux@gmail.com (C) 2015
 
 This is a library to quickly do common trigonometry functions
 on Arduinos/other microprocessors.
 
 This file is the main code file.
==============================================================

#include "TurboTrig.h"

#define DEC1 10
#define DEC2 100
#define DEC3 1000
#define DEC4 10000
#define DEC4 10000


//Sin Lookup table
// values for first quadrant, other quadrants calculated by symmetry
const PROGMEM uint16_t SIN_TABLE[181] = {
 0,524,1047,1571,2094,2617,3140,3663,4185,4708,5229,5751,6272,6792,7312,7832,8350,8869,9386,9903,10419,10934,11449,11962,12475,12986,13497,14007,14515,15023,15529,16034,16538,17041,17542,18042,18541,19038,19534,20028,20521,21012,21502,21990,22476,22961,23444,23925,24404,24882,25357,25831,26302,26772,27239,27705,28168,28630,29089,29545,30000,30452,30902,31350,31795,32238,32678,33116,33552,33984,34415,34842,35267,35689,36109,36526,36940,37351,37759,38165,38567,38967,39364,39757,40148,40535,40920,41301,41680,42055,42426,42795,43160,43522,43881,44237,44589,44937,45283,45624,45963,46297,46629,46956,47281,47601,47918,48231,48541,48847,49149,49448,49742,50033,50320,50603,50883,51158,51430,51698,51962,52221,52477,52729,52977,53221,53460,53696,53928,54155,54378,54598,54813,55024,55230,55433,55631,55825,56015,56200,56382,56558,56731,56899,57063,57223,57378,57529,57676,57818,57956,58089,58218,58342,58462,58578,58689,58795,58898,58995,59088,59177,59261,59341,59416,59487,59553,59614,59671,59724,59772,59815,59854,59888,59918,59943,59963,59979,59991,59998,60000
} ;


/*
  acos lookup table is split into three parts, which has a higher accuracy nearer acos(1).
    - 0 to 0.9 is done in steps of 0.0079 rads. (1/127)
    - 0.9 to 0.99 is done in steps of 0.0008 rads. (0.01/127)
    - 0.99 to 1 is done in steps of 0.0002 rads. (0.01/64)	
*/
const PROGMEM uint8_t ACOS_TABLE[278] = {
  255, 254, 252, 251, 250, 249, 247, 246, 245, 243, 242, 241, 240, 238, 237, 236, 234, 233, 232, 231, 229, 228, 227, 225, 224, 223,
  221, 220, 219, 217, 216, 215, 214, 212, 211, 210, 208, 207, 206, 204, 203, 201, 200, 199, 197, 196, 195, 193, 192, 190, 189, 188,
  186, 185, 183, 182, 181, 179, 178, 176, 175, 173, 172, 170, 169, 167, 166, 164, 163, 161, 160, 158, 157, 155, 154, 152, 150, 149,
  147, 146, 144, 142, 141, 139, 137, 135, 134, 132, 130, 128, 127, 125, 123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 103, 101,
  98, 96, 94, 92, 89, 87, 84, 81, 79, 76, 73, 73, 73, 72, 72, 72, 71, 71, 71, 70, 70, 70, 70, 69, 69, 69, 68, 68, 68, 67, 67, 67,
  66, 66, 66, 65, 65, 65, 64, 64, 64, 63, 63, 63, 62, 62, 62, 61, 61, 61, 60, 60, 59, 59, 59, 58, 58, 58, 57, 57, 57, 56, 56, 55,
  55, 55, 54, 54, 53, 53, 53, 52, 52, 51, 51, 51, 50, 50, 49, 49, 48, 48, 47, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 42, 42, 41,
  41, 40, 40, 39, 39, 38, 37, 37, 36, 36, 35, 34, 34, 33, 33, 32, 31, 31, 30, 29, 28, 28, 27, 26, 25, 24, 23, 23, 23, 23, 22, 22,
  22, 22, 21, 21, 21, 21, 20, 20, 20, 19, 19, 19, 19, 18, 18, 18, 17, 17, 17, 17, 16, 16, 16, 15, 15, 15, 14, 14, 13, 13, 13, 12,
  12, 11, 11, 10, 10, 9, 9, 8, 7, 6, 6, 5, 3, 0
};

//============================================================
//  _   _ _   _ _ _ _   _             
// | | | | |_(_) (_) |_(_) ___  ___ _ 
// | | | | __| | | | __| |/ _ \/ __(_)
// | |_| | |_| | | | |_| |  __/\__ \_ 
//  \___/ \__|_|_|_|\__|_|\___||___(_)
// 

Speed_Trig::Speed_Trig() {
}

int Speed_Trig::floatToInt(float input) {
  //Rounding a number avoiding truncation:
  return (int)(input + 0.5);
}

//============================================================

float Speed_Trig::sinx(int deg) {
    int sign = 1;
    deg *=2;
    if (deg < 0) {
        deg = -deg;
        sign = -1;
    }
    while(deg > 360) {
        deg -= 360;
        sign *= -1;
    }
    if (deg > 180)
        deg = 360 - deg;
    return (sign * (pgm_read_word_near(SIN_TABLE + deg)/6e4));
}

float Speed_Trig::cosx(int deg) {
  return sinx(90-deg);
}

float Speed_Trig::sin(float rad) {
	return TurboTrig.sinx((180 / PI * rad));
}

float Speed_Trig::cos(float rad) {
	return TurboTrig.cosx((180 / PI * rad));
}

//The acos function uses a lookup table for corresponding output. 
//Output data are stored as byte values (0 - 255), they are scaled down to float number (0.0 - 1.0) for output.
float Speed_Trig::acos(float num) {
  float rads = 0;
  bool negative = false;
  uint8_t step = 0;
  
  //Get sign of input
  if(num < 0) {
    negative = true;
    num = -num;
  }
  
  if((num >= 0) && (num < 0.9)) {
    //num between 0 and 0.9.
    step = TurboTrig.floatToInt(num * DEC4 / 79);
  } else if ((num >= 0.9) && (num < 0.99)) {
    //num between 0.9 and 0.99.
    step = TurboTrig.floatToInt((num * DEC4 - 9000) / 8) + 114;
  } else if ((num >= 0.99) && (num <= 1)) {
    //num between 0.99 and 1.0.
    step = TurboTrig.floatToInt((num * DEC4 - 9900) / 2) + 227;
  }
  
  rads = (float)((uint8_t)pgm_read_word_near(ACOS_TABLE + step) * 0.00616);
  
  //Account for the negative sign if required.
  if(negative) {
    rads = PI - rads;
  }
  
  return rads;
}

float Speed_Trig::asin(float num) {
	return (PI/2)-acos(num);
}

float Speed_Trig::atan(float opp, float adj) {
  float hypt = sqrt(adj * adj + opp * opp);
  float rad = TurboTrig.acos(adj / hypt);
  
  if(opp < 0) {
    rad = -rad;
  }
  
  return rad;
}

//Initialize TurboTrig object:
Speed_Trig TurboTrig;
