#include "TriOmni_Bot.h"
#include <Arduino.h>
#include "TriOmniServoDrive.cpp"
#include "CommandReceiver.cpp"

#define servoPinA 10
#define servoPinB 11
#define servoPinC 12

TriOmniServoDrive drive;
CommandReceiver commandReceiver;
float speed = 1;
float rotationSpeed = 1;
char input[20];
int dataSize;

void setup() {
  drive.setup(servoPinA, servoPinB, servoPinC);
  delay(3000);
}

void loop() {
  bool result = commandReceiver.poll();
  if(result){
    handleControls();
  }
  // drive.updateJoystick(0, 1);
  drive.updateDirectional(1.5708, 1);
  // put your main code here, to run repeatedly:
}

float degToRad(float degrees){
  return degrees*(PI/180);
}

void handleControls(){
  commandReceiver.getData(input);
  dataSize = commandReceiver.getBufferSize();
  switch (input[0])
  {
    case 0x00:
      //STOP PACKET: packet(0x00, /r, /n)
      drive.stop();
      break;
    case 0x01:
      //1 Joystick. Variable -1 to 1 on X and Y axis. Sent as packet(0x01, X(byte), Y(byte), /r, /n)
      if(dataSize == 5){ //don't do anything if the length is not correct
        drive.updateJoystick(input[1], input[2]);
      }
      break;
    case 0x02:
      //WSAD. Hardcoded -1 to 1 in X and Y axis, with mixing if multiple are pressed (Sent as packet(0x02, char, /r,/n))
      //Speed UP/DOWN: u/j
      //Turn Speed UP/DOWN: i/k
      //stop: x
      if(dataSize == 4){ //don't do anything if the length is not correct
        handleKeyControl();
      }
      break;
    case 0x03:
      //RAW: Raw motor control. Value range, -1 to 1, translated from -100 to 100 via 
      //packet(0x03, A(byte), B(byte), C(byte), /r, /n)
      if(dataSize == 5){ //don't do anything if the length is not correct
        //TODO
      }
      break;
    //TODO case 0x04: bitmap of all the keys in one byte, to actually use WSAD like a tophat that accepts multiple inputs
    default:
      drive.stop(); //lets just treat this as a queue to stop...
      break;
  }
}

void handleKeyControl(char key){
  //numpad style control
  /*
  789
  4 6
  123

  8 forward
  2 backward
  4 left
  6 right
  */
  switch (key)
  {
    case '8': //forward
      drive.updateDirectional(degToRad(90), speed);
      break;
    case '2': //backward
      drive.updateDirectional(degToRad(270), speed);
      break;
    case '4': //strafe left
      drive.updateDirectional(degToRad(180), speed);
      break;
    case '6': //strafe right
      drive.updateDirectional(degToRad(0), speed);
      break;
    case '7': //forward-left
      drive.updateDirectional(degToRad(45), speed);
      break;
    case '9': //forward-right
      drive.updateDirectional(degToRad(135), speed);
      break;
    case '1': //back-left
      drive.updateDirectional(degToRad(225), speed);
      break;
    case '3': //back-right
      drive.updateDirectional(degToRad(315), speed);
      break;

    case 'a': //rotate left
      drive.rotate(1, rotationSpeed);
      break;
    case 'd': //rotate right
      drive.rotate(-1, rotationSpeed);
      break;

    case 'u': //linear speed up
      speed += .1f;
      if(speed > 1)
        speed = 1;
      break;
    case 'j': //linear speed down
      speed -= .1f;
      if(speed < -1)
        speed = -1;
      break;

    case 'i': //rotational speed up
      rotationSpeed += .1f;
      if(rotationSpeed > 1)
        rotationSpeed = 1;
      break;
    case 'k': //rotational speed down
      rotationSpeed -= .1f;
      if(rotationSpeed < -1)
        rotationSpeed = -1;
      break;

    case 'x':
      drive.stop();
      break;
      
    default:

      break;
  }
}