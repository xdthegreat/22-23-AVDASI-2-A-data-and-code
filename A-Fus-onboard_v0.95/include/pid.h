#ifndef _pid_h_
#define _pid_h_

#include "config.h"


#define dtermFilter

class PID {
  private:
    // output limit  
    int limitP;
    int limitI;
    int limitD;
    int limitO;
    float arrayPID[3];
    float integral = 0;
    float pre_error = 0;
    float pre_derivative_out = 0;
  public:
    float getPid(PIDD);
    float getIntegral();
    void setIntegral(float);
    void setPid(float, float, float);
    void setPid_one(PIDD, float);

    int calculate(float, float, float);
    int calculate(float, float, float, SimpleKalmanFilter*);
    int calculate(float, float, float, SimpleKalmanFilter*, bool);
    PID(float, float, float, int, int, int);
};


PID::PID(float p, float i, float d, int lp, int li, int ld){
  arrayPID[P] = p;
  arrayPID[I] = i;
  arrayPID[D] = d;
  limitP = lp;
  limitI = li;
  limitD = ld;
}

void PID::setIntegral(float t){
  integral = t;
}

float PID::getIntegral(){
  return integral;
}

void PID::setPid(float p, float i, float d){
  arrayPID[P] = p;
  arrayPID[I] = i;
  arrayPID[D] = d;
}

void PID::setPid_one(PIDD which, float data){
  arrayPID[which] = data;
}


float PID::getPid(PIDD which){
  return arrayPID[which];
}



int PID::calculate(float set_point, float measure, float dt){
  // error
  float cur_error = set_point - measure;

  // propotion
  float propotion_out = cur_error * arrayPID[P];
  propotion_out = constrain(propotion_out, -limitP, limitP);

  // intergral
  integral = integral + (cur_error / 1000 * dt);
  integral = constrain(integral, (float)-limitI/arrayPID[I], (float)limitI/arrayPID[I]);
  float integral_out = integral * arrayPID[I];

  // derivative
  float derivative_out = (cur_error - pre_error) * arrayPID[D] / dt;
  derivative_out = constrain(derivative_out, -limitD, limitD) * 0.90 + pre_derivative_out * 0.10;
  pre_derivative_out = derivative_out;
  pre_error = cur_error;

  // out
  float out = (propotion_out + integral_out + derivative_out);
  return out;
}

int PID::calculate(float set_point, float measure, float dt, SimpleKalmanFilter *filterD){
  // error
  float cur_error = set_point - measure;

  
  // propotion
  float propotion_out = cur_error * arrayPID[P];
  propotion_out = constrain(propotion_out, -limitP, limitP);

  // intergral
  integral = integral + (cur_error / 1000 * dt);
  integral = constrain(integral, (float)-limitI/arrayPID[I], (float)limitI/arrayPID[I]);
  float integral_out = integral * arrayPID[I];

  // derivative
  float derivative_out = (cur_error - pre_error) * arrayPID[D] / dt;
  derivative_out = filterD->updateEstimate(constrain(derivative_out, -limitD, limitD));

  pre_derivative_out = derivative_out;
  pre_error = cur_error;

  // Serial.print(arrayPID[P]);
  // Serial.print(" ");
  // Serial.print(arrayPID[I]);
  // Serial.print(" ");
  // Serial.print(arrayPID[D]);
  // Serial.print(" ");

  // out
  float out = (propotion_out + integral_out + derivative_out);

  // Serial.print(out);
  // Serial.print("\n"); 
  return out;
}

// The first three parameters are k(pid). The last three are the pwm output limits for each controller.
PID pidX(50.6f, 0.0f, 50.0f, 900, 900, 900);

#endif