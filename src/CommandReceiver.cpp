#include "CommandReceiver.h"
class CommandReceiver
{
private:
    unsigned int MAX_INPUT = 20;
    char input_line[20];
    unsigned int input_pos = 0;
    unsigned int mark = 0; //mark the end of the array

public:
    void setup(){
        Serial.begin(115200);
        while(!Serial) { 
            delay(100); 
        }
    }

    /**
     * Poll new data if available. Updates Serial, and returns true if data is ready to process
     */
    bool poll()
    {
        if (Serial.available() > 0)
        {
            char inByte = Serial.read ();
            Serial.write(inByte);
            return processByte(inByte);
        }
        return false;
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
            mark = input_pos;
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

    bool isBufferEndReached(){
        return input_pos < (MAX_INPUT - 1);
    }

    void clearBuffer()
    {
        input_pos = 0;
    }

    short getBufferSize()
    {
        return mark + 1;
    }

    void getData(char data[]){
        strcpy(data,input_line);
    }
};