#ifndef _potentiometer_h_
#define _potentiometer_h_

//include <config.h>

#include <LiquidCrystal.h>

// Change to 434.0 or other frequency, must match RX's freq!
class POTENTIOMETER {
    private:
        //LCD pins (rs, enable, d4, d5, d6, d7)
        int pin;
        float limit_max;
        float limit_min;
        float potValue;
        
    public:
        bool set(int pinin, float limit_maxin, float limit_minin);
        float read();
    
};

bool POTENTIOMETER::set(int pinin, float limit_maxin, float limit_minin){
    pin = pinin;
    limit_max = limit_maxin;
    limit_min = limit_minin;
    return true;
}

// Function for printing PID values onto LCD display
float POTENTIOMETER::read(){
  
    potValue = analogRead(pin) / 1023.0f * (limit_max-limit_min) + limit_min;
    return potValue;
}


#endif
