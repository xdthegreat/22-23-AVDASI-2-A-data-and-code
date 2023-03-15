#include "include/inclu.h"
#include <EEPROM.h>
#include "include/reciever.h"
#include <SD.h>
#include <SPI.h>
#include <TimeLib.h>

// Servo connected to pin14
// mpu6050 connected to pin18, 19
// Please add the two libraries in lib to ide
// Wait for mpu chip calibration for power on

// Multi-threaded function
void task_main(void*);   // Main functions
void task_serial(void*);  // Serial Print
float setAngles[3]; // PID Target angle x，y，z
float hand_Angles; // PID Target angle x，y，z

File myFile;
const int chipSelect = BUILTIN_SDCARD;
String data_string;

void setup() {
  Serial.begin(250000); // Setting the serial port communication rate
  setAngles[X] = 0;
  hand_Angles =99.9f;

  radio.begin();
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  myFile = SD.open("fus_log.csv", FILE_WRITE);
  time_t now_time = now(); // store the current time in time variable t
  String data_string = "Time, mode, Target angle (deg), Actual angle(deg), k_P, k_I, k_D, ";
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


  // pid parameter permanent storage address initialisation
  #ifdef initEEPROM
    for (int i = addr_a_px; i < addr_a_dz + 1; i++) EEPROM.write(i * 4, 0.0);
  #endif
    float read_temp[9];
    for (int i = addr_a_px; i < addr_a_dz + 1; i++) read_temp[i] = EEPROM.read(i * 4);
    pidX.setPid(read_temp[0], read_temp[1], read_temp[2]);

  // Empty cache
  //serverPID.check_if_enable_server();
  //serverOTA.check_if_enable_server();
  
  imu.begin();  // Initial calibration of mpu
}



void loop() {
  
  imu.update();  // mpu data update 
  task_main();  // Main functions
  task_serial();  // Serial Print
  reciever_main();
  logging_data(hand_Angles, setAngles[X], imu.getAngle(X), pidX.getPid(P), pidX.getPid(I), pidX.getPid(D));
  radio.send('A', imu.getAngle(X));
  // It should have been put in a different core for processing here, but this chip is so fast that just running linearly would have been enough

  //For communication
  //  udp();
  //  serverPID.check_if_go_to_setup();
  //  serverOTA.check_if_go_to_setup();
}

// main
void task_main() {

  // Rocker signal conversion
  // setAngles[X] = map(0, recie_minJoyAnalog, recie_maxJoyAnalog, -recie_maxJoyAngleX, recie_maxJoyAngleX);
  
  // setAngles[X] = 0;  // Temporary setting of the ground station signal to 0
  

  // Clear Integral, no need
  //if (reciever.getExtra() == false) {
    // pidX.setIntegral(0);
    // pidY.setIntegral(0);
    // pidZ.setIntegral(0);
  //}


  int pid_out_agl[3] = {0, 0, 0}; // PID Angle loop output x, y, z
  int pid_out_pwm[3] = {0, 0, 0}; // pid Fin output x, y, z, t

  // x, y target angle is the transformed rocker x, y
  if (hand_Angles == 99.90f) {
    pid_out_agl[X] = pidX.calculate(setAngles[X], imu.getAngle(X), pidLoopDelay, &dtermFilterX);
    pid_out_pwm[X] = pid_out_agl[X];
  }
  else {
    float hand_Angles_right = 0.0f;
    if (hand_Angles > hand_Angles_right) {
      hand_Angles_right = hand_Angles*(0.72f);
      }
    else {
      hand_Angles_right = hand_Angles;
    }
    pid_out_agl[X] = hand_Angles_right / tailplan_angle_max * (motor_midPwm - motor_maxPwm);
    pid_out_pwm[X] = pid_out_agl[X];
  }

  
  int motorPwm[3]; //a，b，c are different servos for the corresponding axis
  int motorPwm_zip[3]; //a，b，c
  motorPwm_zip[mA] = pid_out_pwm[X];

  motorPwm_zip[mA] = constrain(motorPwm_zip[mA], -pid_maxPwmOut, pid_maxPwmOut); // range

  int tPwm = 0; // Get the correction angle
  
  motorPwm[mA] = motor_midPwm + tPwm + motorPwm_zip[mA];
  motorPwm[mB] = motor_midPwm + tPwm - motorPwm_zip[mA];

  // Attitude angle greater than 75, Servo back to centre
  bool overAngle = false;
  if (abs(imu.getAngle(X)) > abs(pid_maxAngle)) overAngle = true;

  
  
  // Set the servo pwm output, mA,mB,mC are different servos for the corresponding axis, for the fuselage currently only the x-axis servos are used
  motorA.setAStandardisedPwm(motorPwm[mA]);
  motorB.setAStandardisedPwm(motorPwm[mB]);
  // motorC.setAStandardisedPwm(motorPwm[mC]);
  if (not(overAngle)) {
    motorA.setStandardisedPwm_write(motorPwm[mA], true);
    motorB.setStandardisedPwm_write(motorPwm[mB], true);
    // motorC.setStandardisedPwm_write(motorPwm[mC], true);
  } else {
    motorA.setStandardisedPwm_write(motor_midPwm, false);
    motorB.setStandardisedPwm_write(motor_midPwm, false);
    // motorC.setStandardisedPwm_write(motor_minPwm, false);
  }

  delay(pidLoopDelay);

}

// serial output
void task_serial() {
  int delay_time = serial_zip();  // For serial port printing details see seriale.h
}

// serial output
void reciever_main() {
  if (radio.receive()) {
    switch(*radio.flag){
      case 'F':
        break;
      case 'S':
        setAngles[X] = *radio.data;
        Serial.println(setAngles[X]);
        hand_Angles = 99.9f;
        break;
      case 'H':
        hand_Angles = *radio.data;
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

bool logging_data(float hand_Angles, float target_AoA, float Actual_AoA, float k_P, float k_I, float k_D)
{
  int log_time = millis();
  SD.begin(chipSelect);
  myFile = SD.open("fus_log.csv", FILE_WRITE);
  String data_string = String(log_time) + ", " + String(hand_Angles) + ", " + String(target_AoA) + ", " + String(Actual_AoA) + ", " + String(k_P) + ", " + String(k_I) + ", " + String(k_D);
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
