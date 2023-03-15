//Libraries
#include "reciever.h"
#include "display.h"
#include "dcmoter.h"
#include "potentiometer.h"
#include <SimpleKalmanFilter.h>

//pins for teensy
const int P_pin = A9;
const float P_max = 10.0f;
const float P_min = 0.0f;

const int I_pin = A8;
const float I_max = 10.0f;
const float I_min = 0.0f;

const int D_pin = A7;
const float D_max = 10.0f;
const float D_min = 0.0f;

const int angle_pin = A6;
const float angle_max = 40.0f;
const float angle_min = 0.0f;
const float hand_angle_max = 40.0f;
const float hand_angle_min = 0.0f;

const int mode_switch_pin = 41;
//LCD pins (rs, enable, d4, d5, d6, d7)
//LiquidCrystal lcd(27, 28, 29, 30, 31, 32);

float real_angle;

bool mode;  //true for PID, can change later

float pid_raw[3]; // x, y, z
float angle_raw;
float hand_angle_raw;

int display_flag;
//"Memory" of old value
float old_raw[3];
float old_angle_raw;
bool old_mode;
LiquidCrystal lcd(27, 28, 29, 30, 31, 32);

SimpleKalmanFilter dtermFilterp(0.001f, 0.001f, 0.25); // p Controller filtering
SimpleKalmanFilter dtermFilteri(0.000001f, 0.000001f, 0.25); // i Controller filtering
SimpleKalmanFilter dtermFilterd(0.0000001f, 0.0000001f, 0.25); // d Controller filtering
SimpleKalmanFilter dtermFiltera(0.1f, 0.1f, 0.25); // angle Controller filtering
SimpleKalmanFilter dtermFilterh(0.1f, 0.1f, 0.25); // hand angle Controller filtering
POTENTIOMETER angle_in;
POTENTIOMETER hand_angle_in;
POTENTIOMETER p_in;
POTENTIOMETER i_in;
POTENTIOMETER d_in;

int display_key = A14;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  lcd.begin(16, 2);
  lcd.clear();
  radio.begin();
  angle_in.set(angle_pin, angle_max, angle_min);
  hand_angle_in.set(angle_pin, hand_angle_max, hand_angle_min);
  p_in.set(P_pin, P_max, P_min);
  i_in.set(I_pin, I_max, I_min);
  d_in.set(D_pin, D_max, D_min);

  old_angle_raw = angle_in.read();
}

void loop() {
  pid_raw[0] = (int)(100.0*dtermFilterp.updateEstimate(p_in.read())+0.5)/100.0;
  pid_raw[1] = (int)(100.0*dtermFilteri.updateEstimate(i_in.read())+0.5)/100.0;
  pid_raw[2] = (int)(100.0*dtermFilterd.updateEstimate(d_in.read())+0.5)/100.0;
  angle_raw = (int)(100.0*dtermFiltera.updateEstimate(angle_in.read())+0.5)/100.0;
  hand_angle_raw = (int)(100.0*dtermFiltera.updateEstimate(hand_angle_in.read())+0.5)/100.0;
  Serial.println(analogRead(display_key));

  mode = digitalRead(mode_switch_pin);
  if (old_mode != mode) {
    Serial.print("Mode changed to: ");
    old_mode = mode;
  }
  
  if (analogRead(display_key)<5) {
    display_flag = 20;
    display2(pid_raw[0], pid_raw[1], pid_raw[2]);
    old_raw[0] = pid_raw[0];
    old_raw[1] = pid_raw[1];
    old_raw[2] = pid_raw[2];
    radio.send('P', old_raw[0]);
    radio.send('I', old_raw[1]);
    radio.send('D', old_raw[2]);
  }
  else {
    if (old_angle_raw != angle_raw) {
      old_angle_raw = angle_raw;
      if (mode){
        radio.send('A', angle_raw);
        display1(angle_raw, real_angle);
      }
      else{
        radio.send('H', hand_angle_raw);
        display1(hand_angle_raw, real_angle);
      }
    }
  }

  if (radio.receive()){
    real_angle = *radio.data;
  }

  display_flag--;
  delay(100);
  // put your main code here, to run repeatedly:
}

// Function for printing PID values onto LCD display
bool display1(float set_angle, float real_angle){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Act angle: " + String(real_angle));
  lcd.setCursor(0,2);
  if (mode){
    lcd.print("Set angle: " + String(set_angle));
  }
  else{
    lcd.print("Ele angle: " + String(set_angle));
  }
  return true;
}

bool display2(float k_P, float k_I, float k_D) {
  String mode_string;
  if (mode){
    mode_string = "Pitch";
  }
  else {
    mode_string = "Elev";
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("P: " + String(k_P) + ", I: " + String(k_I));
  lcd.setCursor(0,2);
  lcd.print("D: " + String(k_D) + ", M: " + String(mode_string));
  return true;
}
