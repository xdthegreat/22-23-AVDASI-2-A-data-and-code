#ifndef _motor_h_
#define _motor_h_


/*
<ESP32Servo.h>
-author
John K. Bennett
https://github.com/madhephaestus/ESP32Servo
*/

#include "config.h"
// On standard servos, parameter values 1000 fully counterclockwise, 2000 fully clockwise, 1500 in the middle

class MOTOR_BASE{
    protected:
        int standardisedPwm = motor_minPwm;
        int astandardisedPwm = motor_minPwm;
    public:
        int getStandardisedPwm(){return standardisedPwm;};
        int getAStandardisedPwm(){return astandardisedPwm;};
        void setStandardisedPwm(int pwm){standardisedPwm = constrain(pwm, motor_minPwm, motor_maxPwm);};
        void setStandardisedPwmRun(int pwm){standardisedPwm = constrain(pwm, motor_minPwmRunning, motor_maxPwm);};
        void setAStandardisedPwm(int pwm){astandardisedPwm = pwm;};
        void setStandardisedPwm_write();
};


#ifdef pwmm
    #include <Servo.h>
    
    class MOTOR:public MOTOR_BASE{
        private:
            Servo m;
        public:
            MOTOR(int);
            void setStandardisedPwm_write(int, bool);
    };

    MOTOR::MOTOR(int pin){
        m.attach(pin, motor_minPwm, motor_maxPwm);
    }

    void MOTOR::setStandardisedPwm_write(int pwm, bool running){
        if(running) setStandardisedPwmRun(pwm);
        else setStandardisedPwm(pwm);
        m.writeMicroseconds(standardisedPwm);
    }

#endif



MOTOR motorA(motorA_pin);
MOTOR motorB(motorB_pin);
MOTOR motorC(motorC_pin);
MOTOR motorD(motorD_pin);


#endif
