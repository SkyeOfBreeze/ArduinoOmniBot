#include "TriOmni_Bot.h"
#include <Arduino.h>
#include "TriOmniServoDrive.cpp"
#include "CommandReceiver.cpp"

#define servoPinA 10
#define servoPinB 11
#define servoPinC 12

TriOmniServoDrive drive;
CommandReceiver commandReceiver;
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
  //TODO Might have to break it up into a numpad style control for all of the available motion...
  switch (key)
  {
    case 'w':
      
      break;
    case 's':
      
      break;
    case 'a':
      
      break;
    case 'd':
      
      break;
    case 'u':
      
      break;
    case 'j':
      
      break;
    case 'i':
      
      break;
    case 'k':
      
      break;
    case 'x':
      
      break;
    default:

      break;
  }
}