#include "CommandReceiver.h"
class CommandReceiver
{
private:
    int MAX_INPUT = 20;
    char input_line[20];
    unsigned int input_pos = 0;

public:
    void setup(){
        Serial.begin(9600);
    }

    /**
     * Poll new data if available. Updates Serial, and returns true if data is ready to process
     */
    bool poll()
    {
        if (Serial.available() > 0)
        {
            char inByte = Serial.read ();
            return processByte(inByte);
        }
    }

    /**
    * Process a byte from a given input.
    * @returns true if this is the end of a packet, false otherwise
    */
    bool processByte(unsigned char inByte)
    {
        switch (inByte)
        {
        case '\n':                     // end of text
            input_line[input_pos] = 0; // terminating null byte

            // terminator reached! process input_line here ...
            Serial.println(input_line);
            // reset buffer for next time
            input_pos = 0;
            return true;
            break;

        case '\r': // discard carriage return
            break;
        default:
            if (isBufferEndReached()) // keep adding if not full ... allow for terminating null byte
                input_line[input_pos++] = inByte;
            break;

        } // end of switch
        return false;
    }

    bool isBufferEndReached()
    {
        return input_pos < (MAX_INPUT - 1);
    }

    void clearBuffer()
    {
        input_pos = 0;
    }

    short getBufferSize()
    {
        return input_pos + 1;
    }

    void getData(char data[]){
        strcpy(data,input_line);
    }
};