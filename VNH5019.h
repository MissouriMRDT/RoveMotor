#ifndef VNH5019_H_
#define VNH5019_H_

//TODO: Read current values
//      Adding in structure to support passing in RPM instead of power percent
class VNH5019
{
  private:
    const int INA_PIN, INB_PIN, PWM_PIN;
    int currentPower;
    
    bool invert = false;
    
    //move function which passes in power percent (which is converted to phase and PWM) to move device
    //could in future be changed to RPM
    void move(uint8_t motor_percent); 
    
    //brake function, in which the percent of motor used to break can specified
    void VNH5019::brake(uint8_t brake_percent)
        
    //tells device to stop
    void stop();
    
  public:
  
    //Inputs: pwm generator reference to output a pwm wave on the pwm pin,
    //        pin assignments for hardware pins,
    //        a bool to determine the orientation of the motor.
    //Pin numbers based ons the roveboard standard
    VNH5019(const int PwmPin, const int InaPin, const int InbPin, bool upsideDown);
    
    //returns the last power percentage this device got commanded.
    long getCurrentMove();
};

#endif