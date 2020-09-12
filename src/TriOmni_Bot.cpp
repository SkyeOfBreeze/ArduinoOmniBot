#include "TriOmni_Bot.h"
#include <Arduino.h>
#include "TriOmniServoDrive.cpp"

#define servoPinA 10
#define servoPinB 11
#define servoPinC 12

TriOmniServoDrive drive;

void setup() {
  Serial.begin(9600);
  Serial.println("main");
  drive.setup(servoPinA, servoPinB, servoPinC);
  delay(3000);
}

const unsigned int MAX_INPUT = 20;
char input_line [MAX_INPUT];
unsigned int input_pos = 0;

void loop() {
  // drive.updateJoystick(0, 1);
  drive.updateDirectional(1.5708, 1);
  // put your main code here, to run repeatedly:
}

/**
 * Process a byte from a given input.
 * @returns true if this is the end of a packet, false otherwise
 */
bool processByte(unsigned char inByte){
  switch (inByte)
  {
    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte

      // terminator reached! process input_line here ...
      Serial.println (input_line);
      // reset buffer for next time
      input_pos = 0;
      return true;
      break;

    case '\r':   // discard carriage return
      break;
    default:
      if (isBufferEndReached()) // keep adding if not full ... allow for terminating null byte
        input_line [input_pos++] = inByte;
      break;

  }  // end of switch
  return false;
}

bool isBufferEndReached(){
  return input_pos < (MAX_INPUT - 1);
}

void clearBuffer(){
  input_pos = 0;
}

short getBufferSize(){
  return input_pos+1;
}

void parse(){

}
