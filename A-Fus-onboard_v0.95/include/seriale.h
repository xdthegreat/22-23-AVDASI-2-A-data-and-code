#ifndef _seriale_h_
#define _seriale_h_

#include "config.h"

int serial_zip(){
    
    int delay_time = 10; 
    static char str = '1';
    if (Serial.available() > 0) str = Serial.read();

    // Open the serial plotter and enter the corresponding case to print the sensor data
    switch (str) {
      // print angle
      case 'a':
        Serial.print(imu.getAngle(X));
        Serial.print("   ");
        Serial.print(imu.getAngle(Y));
        Serial.print("   ");
        Serial.println(imu.getAngle(Z));
        break;
      // print gyro
      case 'b':
        Serial.print(imu.getGyro(X));
        Serial.print("   ");
        Serial.print(imu.getGyro(Y));
        Serial.print("   ");
        Serial.println(imu.getGyro(Z));
        break;
      // print acc
      case 'c':
        Serial.print(imu.getAcc(X));
        Serial.print("   ");
        Serial.print(imu.getAcc(Y));
        Serial.print("   ");
        Serial.println(imu.getAcc(Z));
        break;
      // sample count
      case 'd':
        Serial.println(imu.getSampleCount(true));
        delay_time = 1000;
        break;  
      // servo outputs
      case 'e':
        Serial.print("B:");
        Serial.print(motorB.getAStandardisedPwm());
        Serial.print("  A:");
        Serial.print(motorA.getAStandardisedPwm());
        Serial.print("  D:");
        Serial.print(motorD.getAStandardisedPwm());
        Serial.print("  C:");
        Serial.println(motorC.getAStandardisedPwm());
        break;    
        
      case 'g':
        Serial.print("x: ");
        Serial.print(imu.getAccAngle(X));
        Serial.print("  y: ");
        Serial.println(imu.getAccAngle(Y));
        break; 

    }
    
    return delay_time;
}
#endif