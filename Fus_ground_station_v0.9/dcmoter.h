#ifndef _dcmoter_h_
#define _dcmoter_h_

//include <config.h>

#include <LiquidCrystal.h>

// Change to 434.0 or other frequency, must match RX's freq!
class DCMOTER {
    private:
        //LCD pins (rs, enable, d4, d5, d6, d7)
        static const int Enable_1 = 11;
        static const int input_1 = 8;
        static const int input_2 = 7;

    public:
        bool dc_rotation(int rotation);
        void begin();
};

void DCMOTER::begin(){
    pinMode(Enable_1, OUTPUT);
    pinMode(input_1, OUTPUT);
    pinMode(input_2, OUTPUT);
    
    // Initial state -Motors
    digitalWrite(input_1, LOW);
    digitalWrite(input_2, LOW);
  
     //Dc motor Voltage Value >> -255 to +255
}

// Function for printing PID values onto LCD display
bool DCMOTER::dc_rotation(int rotation){ 
    if (rotation > 0) {
        digitalWrite(input_1, LOW);
        digitalWrite(input_2, HIGH);
        }
    else {
        digitalWrite(input_1, HIGH);
        digitalWrite(input_2, LOW);
        }
    
    analogWrite(Enable_1, abs(rotation)); 
    return true;
}

DCMOTER dc_moter;

#endif