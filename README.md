# TurboTrig
 Simple Arduino library that speeds up trigonometry functions.<br>
 It's based on work by Oscar Liang.<br>

### To work
 To add the TurboTrig library, simply drag the main folder into the libraries subdirectory of your Arduino IDE sketch folder.<br>
 
### Example
 #include <TurboTrig.h><br>
 void setup() {<br>
    Serial.begin(9600);<br>
    Serial.println("sin(15): ");<br>
    Serial.println(sin(PI/6));<br>
    Serial.println("TurboTrig.sin(PI/6): ");<br>
    Serial.println(TurboTrig.sin(15));<br>
    Serial.println("TurboTrig.sinx(180/6): ");<br>
    Serial.println(TurboTrig.sinx(15));<br>
 }<br>
 void loop() {<br>
 }<br>
 
### Features
 The TurboTrig library containes:<br>
    sin  : which is a sin function in radian;<br>
    cos  : which is a cos function in radian;<br>
    sinx : which is a sin function in degree;<br>
    cosx : which is a cos function in degree;<br>
    acos : which is a acos function;<br>
    asin : which is a asin function;<br>
    atan : which is a atan function;<br>
    
