#include "math.h"
#include <Arduino.h>
struct OmniDrive
{
    /* data */
    private:
    float wheel[10];
    float wheelCount;
    float xJoy, yJoy;
    float thetaJoy, rJoy;
    float speed;

    public:
    float maxSpeed = .6f;
    float b = 1; //TODO this is a constant defined to scale based on https://robotics.stackexchange.com/questions/7829
    
    void supplyJoy(float x, float y){
        xJoy = x;
        yJoy = y;
        thetaJoy = atan2(xJoy, yJoy);
        rJoy = sqrt(yJoy*yJoy + xJoy*xJoy);
        speed = maxSpeed*rJoy/b;
    }

    void supplyDirectional(float theta, float r){
        thetaJoy = theta;
        rJoy = r;
        speed = maxSpeed*rJoy/b;
    }

    void registerWheels(float wheelAngles[], int size){
        OmniDrive::wheelCount = size;
        for(int i = 0; i < size; i++){
            wheel[i] = wheelAngles[i];
        }
    }

    float getWheelSpeed(int wheelPos){
        float theta = wheel[wheelPos] - thetaJoy;
        return speed*sin(theta);
    }

    void zero(){
        xJoy = 0;
        yJoy = 0;
        thetaJoy = atan2(xJoy, yJoy);
        rJoy = sqrt(yJoy*yJoy + xJoy*xJoy);
        speed = 0;
    }
};
