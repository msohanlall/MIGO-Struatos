#ifndef _smoothJoystick_h_
#define _smoothJoystick_h_
  
#include "Arduino.h";
  
// define our stepper class
class joystick {
  public:
    joystick(byte analogPin, unsigned int initialVal);
    unsigned int smoothRead(void);
    unsigned int smoothedVal; // smoothed analog value
  private:
    unsigned int _buffer[512]; // array of analog data; careful about memory issues
    byte _analogPin; // pin on which joystick values are being read
    unsigned long _bufferSum; // total sum of all analog values in buffer
    unsigned int _bufferIndex; // index counter for which value to replace in buffer
    unsigned int _bufferSize; // total number of analog values to keep track of
    unsigned int _initialVal; // initial value for smoothed array average (center position of joystick)
};
  
  
#endif
