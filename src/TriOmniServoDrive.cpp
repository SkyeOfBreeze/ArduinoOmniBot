#include <Servo.h>
#include "OmniDrive.cpp"
#include "math.h"
#include <Arduino.h>

class TriOmniServoDrive{
    private:
    OmniDrive drive;
    Servo servoA;
    Servo servoB;
    Servo servoC;
    long map(float x, float in_min, float in_max, float out_min, float out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    
    public:
    void setup(int pinA, int pinB, int pinC){
        servoA.attach(pinA);
        servoB.attach(pinB);
        servoC.attach(pinC);
        float array[3] = {30, 150, 270}; //degrees
        for(int i = 0; i < 3; i++){
           array[i] = array[i]*(M_PI/180); //convert to radians
        }
        drive.registerWheels(array, 3);
    }

    void updateJoystick(float x, float y){
        drive.supplyJoy(x, y);
        driveServos();
    }

    void updateDirectional(float theta, float r){
        drive.supplyDirectional(theta, r);
        driveServos();
    }

    void rotate(float direction, float speed){
        float vel = map(direction*speed, -1.0, 1.0, 0, 180.0);
        servoA.write(vel);
        servoB.write(vel);
        servoC.write(vel);
    }

    void driveServos(){
        float A = map(drive.getWheelSpeed(0), -1.0, 1.0, 0, 180.0);
        float B = map(drive.getWheelSpeed(1), -1.0, 1.0, 0, 180.0);
        float C = map(drive.getWheelSpeed(2), -1.0, 1.0, 0, 180.0);
        servoA.write(A);
        servoB.write(B);
        servoC.write(C);
    }

    void stop(){
        drive.zero();
        driveServos();
    }
};