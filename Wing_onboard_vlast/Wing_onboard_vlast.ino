//Libraries
#include "reciever.h"
#include "dcmoter.h"
#include "potentiometer.h"
#include "pid.h"
#include <SimpleKalmanFilter.h>
#include <SD.h>
#include <SPI.h>
#include <TimeLib.h>


File myFile;
const int chipSelect = BUILTIN_SDCARD;
String data_string;


#define pidLoopDelay 5 // Run pid every 5ms
#define pid_maxOut 250 // Maximum pwm adjustable value per servo


SimpleKalmanFilter dtermFilterX(4.0f, 4.0f, 0.25); // x Controller filtering

//pins for teensy
const int angle_pin = A6;
const float angle_max = 47.0f;
const float angle_min = -23.0f;

//LCD pins (rs, enable, d4, d5, d6, d7)
//LiquidCrystal lcd(27, 28, 29, 30, 31, 32);

float set_angle = 0;

float pid_raw[3]; // x, y, z
float angle_raw;

//"Memory" of old value
int rotation;


SimpleKalmanFilter dtermFiltera(4.0f, 4.0f, 0.25); // angle Controller filtering
POTENTIOMETER angle_in;

int display_key = A14;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dc_moter.begin();
  radio.begin();
  angle_in.set(angle_pin, angle_max, angle_min);


  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  myFile = SD.open("wing_v_last.csv", FILE_WRITE);
  time_t now_time = now(); // store the current time in time variable t
  
  String data_string = "Time, Target angle (deg), Actual angle(deg), k_P, k_I, k_D, ";
  data_string = data_string+ String(now_time);
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(data_string);
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }

}

void loop() {
  angle_raw = 0.9f * (dtermFiltera.updateEstimate(angle_in.read()) + 8);

  float pid_out_rotation = pidX.calculate(set_angle, angle_raw, pidLoopDelay, &dtermFilterX);
  int pid_out_zip = pid_out_rotation;

  pid_out_zip = constrain(pid_out_zip*2, -pid_maxOut, pid_maxOut);
  //Serial.print(pid_out_zip);
  //Serial.print("\n");
  dc_moter.dc_rotation(pid_out_zip);

  logging_data(set_angle, angle_raw, pidX.getPid(P), pidX.getPid(I), pidX.getPid(D));
  reciever_main();
  radio.send('A', angle_raw);
  delay(pidLoopDelay);
  // put your main code here, to run repeatedly:
}


// serial output
void reciever_main() {
  if (radio.receive()) {
    //Serial.print("in");
    switch (*radio.flag) {
      case 'F':
        break;
      case 'S':
        set_angle = *radio.data;
        Serial.print(set_angle);
        break;
      case 'P':
        pidX.setPid_one(P, *radio.data);
        break;
      case 'I':
        pidX.setPid_one(I, *radio.data);
        break;
      case 'D':
        pidX.setPid_one(D, *radio.data);
        break;
    }
  }
}



bool logging_data(float target_AoA, float Actual_AoA, float k_P, float k_I, float k_D)
{
  int log_time = millis();
  SD.begin(chipSelect);
  myFile = SD.open("wing_v_last.csv", FILE_WRITE);
  String data_string = String(log_time) + ", " + String(target_AoA) + ", " + String(Actual_AoA) + ", " + String(k_P) + ", " + String(k_I) + ", " + String(k_D);
  //Serial.println(data_string);
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(data_string);
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
}
