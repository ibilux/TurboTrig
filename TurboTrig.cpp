/*
==============================================================
 TurboTrig Library
==============================================================
 i.bilux@gmail.com (C) 2015
 
 This is a library to quickly do common trigonometry functions
 on Arduinos/other microprocessors.
 
 This file is the main code file.
==============================================================
*/

#include "TurboTrig.h"

#define DEC1 10
#define DEC2 100
#define DEC3 1000
#define DEC4 10000
#define DEC4 10000


//Sin Lookup table
// values for first quadrant, other quadrants calculated by symmetry
const PROGMEM float SIN_TABLE[361] = {
	0,0.0174524064372835,0.0348994967025010,0.0523359562429438,0.0697564737441253,0.0871557427476582,0.104528463267653,0.121869343405147,0.139173100960065,0.156434465040231,0.173648177666930,0.190808995376545,0.207911690817759,0.224951054343865,0.241921895599668,0.258819045102521,0.275637355816999,0.292371704722737,0.309016994374947,0.325568154457157,0.342020143325669,0.358367949545300,0.374606593415912,0.390731128489274,0.406736643075800,0.422618261740699,0.438371146789077,0.453990499739547,0.469471562785891,0.484809620246337,0.500000000000000,0.515038074910054,0.529919264233205,0.544639035015027,0.559192903470747,0.573576436351046,0.587785252292473,0.601815023152048,0.615661475325658,0.629320391049837,0.642787609686539,0.656059028990507,0.669130606358858,0.681998360062499,0.694658370458997,0.707106781186548,0.719339800338651,0.731353701619171,0.743144825477394,0.754709580222772,0.766044443118978,0.777145961456971,0.788010753606722,0.798635510047293,0.809016994374948,0.819152044288992,0.829037572555042,0.838670567945424,0.848048096156426,0.857167300702112,0.866025403784439,0.874619707139396,0.882947592858927,0.891006524188368,0.898794046299167,0.906307787036650,0.913545457642601,0.920504853452440,0.927183854566787,0.933580426497202,0.939692620785908,0.945518575599317,0.951056516295154,0.956304755963035,0.961261695938319,0.965925826289068,0.970295726275997,0.974370064785235,0.978147600733806,0.981627183447664,0.984807753012208,0.987688340595138,0.990268068741570,0.992546151641322,0.994521895368273,0.996194698091746,0.997564050259824,0.998629534754574,0.999390827019096,0.999847695156391,1
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

Turbo_Trig::Turbo_Trig() {
}

int Turbo_Trig::floatToInt(float input) {
  //Rounding a number avoiding truncation:
  return (int)(input + 0.5);
}

//============================================================

float Turbo_Trig::sinx(int deg) {
    int sign = 1;
    if (deg < 0) {
        deg = -deg;
        sign = -1;
    }
    while(deg > 180) {
        deg -= 180;
        sign *= -1;
    }
    if (deg > 90)
        deg = 180 - deg;
    return (sign * (pgm_read_float_near(SIN_TABLE + deg)));
}

float Turbo_Trig::cosx(int deg) {
  return sinx(90-deg);
}

float Turbo_Trig::sin(float rad) {
	return TurboTrig.sinx((180 / PI * rad));
}

float Turbo_Trig::cos(float rad) {
	return TurboTrig.cosx((180 / PI * rad));
}

//The acos function uses a lookup table for corresponding output. 
//Output data are stored as byte values (0 - 255), they are scaled down to float number (0.0 - 1.0) for output.
float Turbo_Trig::acos(float num) {
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

float Turbo_Trig::asin(float num) {
	return (PI/2)-acos(num);
}

float Turbo_Trig::atan(float opp, float adj) {
  float hypt = sqrt(adj * adj + opp * opp);
  float rad = TurboTrig.acos(adj / hypt);
  
  if(opp < 0) {
    rad = -rad;
  }
  
  return rad;
}

//Initialize TurboTrig object:
Turbo_Trig TurboTrig;
