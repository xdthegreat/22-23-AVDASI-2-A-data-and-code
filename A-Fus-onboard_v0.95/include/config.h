#ifndef _config_h_
#define _config_h_

#pragma once



enum PIDD{P, I, D};
enum XYZT{X, Y, Z, T};
enum V1234{V1, V2, V3, V4};
enum mABCD{mA, mB, mC, mD};



//#define nrff
#define esp32_now
#define pwmm



// filters-----------------------------------------------------------------------------------------------------------------
// Take care that the filtering is as small as possible. The more you filter, the higher the delay.
SimpleKalmanFilter dtermFilterX(4.0f, 4.0f, 0.25); // x Controller filtering
SimpleKalmanFilter dtermFilterY(4.0f, 4.0f, 0.25); // y Controller filtering
SimpleKalmanFilter dtermFilterZ(5.0f, 5.0f, 0.25); // z Controller filtering


#define dmpAngleWeight 0.5 //100hz
#define accAngleWeight 0.002 //1000hz

// imu Angular filtering
//#define angleFilter // Uncomment to use filtering
SimpleKalmanFilter filterX(1.5f, 1.5f, 0.05f);
SimpleKalmanFilter filterY(1.5f, 1.5f, 0.05f);

// imu Angular velocity filtering
#define gyroFilter // Uncomment to use filtering
SimpleKalmanFilter filterGX(5.0f, 5.0f, 0.1f);
SimpleKalmanFilter filterGY(5.0f, 5.0f, 0.1f);
SimpleKalmanFilter filterGZ(5.0f, 5.0f, 0.1f);



// wifi PID Control-----------------------------------------------------------------------------------------------------------------
// Reserved for communication chips, temporarily useless
#define initEEPROM

#define serverNameOTA "MEO-813190"
#define serverPassOTA "b7a5dafa3b"

#ifdef smd 
    #define serverNamePID "esp32smd"
    #define serverPassPID "gtwhhhh111"
#else
    #define serverNamePID "esp32"
    #define serverPassPID "gtwhhhh111"
#endif



// something--------------------------------------------------------------------------------------------------------------
#define pidLoopDelay 5 // Run pid every 5ms
#define recieverLoopDelay 2 // Read receiver every 2ms



// pid----------------------------------------------------------------------------------------------------------------------
#define pid_maxPwmOut 950 // Maximum pwm adjustable value per servo
#define pid_maxAngle 70.0 // Close if x or y attitude is greater than this angle



// motor-------------------------------------------------------------------------------------------------------------------
#define motor_minPwm 500 // pwm minimum
#define motor_minPwmRunning 570 //Preset deflection
#define motor_midPwm 1600 // pwm median
#define motor_maxPwm 2700 // pwm maximum
#ifdef smd
    #define motorA_pin 25
    #define motorB_pin 33
    #define motorC_pin 26
    #define motorD_pin 32
#else
    #define motorA_pin 14
    #define motorB_pin 15
    #define motorC_pin 27
    #define motorD_pin 13
#endif

// mas tailplan angle max
#define tailplan_angle_max 40

// mpu6050--------------------------------------------------------------------------------------------------------
// Assisted setup with serial monitor
#ifdef smd
  //#define mpu_invertX // x = -x
  #define mpu_invertY // y = -y
  // #define mpu_invertZ // z = -z
  #define mpu_swapXY // x = y, y = x
#else
  // #define mpu_invertX // x = -x
  // #define mpu_invertY // y = -y
  // #define mpu_invertZ // z = -z
  // #define mpu_swapXY // x = y, y = x
#endif


// Automatic calibration with each power-up
// If there are already calibration values, uncomment the next line
//#define mpu_manu_gyro_offset
#define mpu_gyro_offsetX  0
#define mpu_gyro_offsetY  0
#define mpu_gyro_offsetZ  0

// If there are already calibration values, uncomment the next line
//#define mpu_manu_acc_offset
#define mpu_acc_offsetX  0
#define mpu_acc_offsetY  0
#define mpu_acc_offsetZ  0



// reciever----------------------------------------------------------------------------------------------------------------------
// Reserved for ground station, temporarily useless
#define recie_timeOut 600 // 超过600ms没接收机信号则判断信号丢失，电机将停转
// 接收机摇杆值是0到255
#define recie_minJoyAnalog 0   // nrf接收机摇杆最低值
#define recie_midJoyAnalog 127 // nrf接收机摇杆中位值
#define recie_maxJoyAnalog 255 // nrf接收机摇杆最大值
// pid目标角度
#define recie_maxJoyAngleX 30 // x pid的最大目标角度。 -30-30
#define recie_maxJoyAngleY 30 // y pid的最大目标角度。 -30-30
#define recie_maxJoyAngleZ 60 // z pid的最大目标角度
// 油门pwm
#define recie_minJoyTpwm 0 // 油门最低pwm
#define recie_maxJoyTpwm 800 // 油门最大pwm

#define recie_joyInnerDeadZoneX 1 //x摇杆角度内圈死区 
#define recie_joyInnerDeadZoneY 1 //y摇杆角度内圈死区 
#define recie_joyInnerDeadZoneZ 14 //z摇杆角度内圈死区

#endif