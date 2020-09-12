#include "TriOmni_Bot.h"
#include <Arduino.h>
#include "TriOmniServoDrive.cpp"

/*
 * Made for Platform.IO, but may work on Arduino IDE with little modifications
 * 3 Omni Wheel Setup,  120 degrees apart
 *
 * Wheel positions
 *   B   A
 *    \ /
 *     |
 *     C
 * 
 * Coordinate system (Degrees)
 *       90
 *       |
 * 180 -- -- 0
 *       |
 *      270
 * 
 * Wheel Axle Directions (Degrees)
 * A: 30 degrees
 * B: 150 degrees
 * C: 270 degrees
 * 
 * Forward Direction:
 * 90 degrees OR pi/2 radians
 * Wheel directions:
 * 
 *    A
 *  (+)
 *    \
 *    (-)
 * 
 *    B
 *    (-)
 *    /
 *  (+)    
 *     
 *    C
 * (+)-(-)
 * 
 * Forms of control (a byte is assumed here to be sent as -100 to 100 unless otherwise specified):
 * - 1 Joystick. Variable -1 to 1 on X and Y axis. Sent as packet(0x01, X(byte), Y(byte), /r, /n)
 * - WSAD. Hardcoded -1 to 1 in X and Y axis, with mixing if multiple are pressed (Sent as packet(0x02, char, /r,/n))
 * - STOP PACKET: packet(0x00, /r, /n)
 * - RAW: Raw motor control. Value range, -1 to 1, translated from -100 to 100 via packet(0x03, A(byte), B(byte), C(byte), /r, /n)
 * 
 * Servo Pins: 
 * A: D10
 * B: D11
 * C: D12
 * 
 * NOTE: any speed calculations for wheels are done in radians
 */

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
