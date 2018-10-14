#ifndef VNH5019_H_
#define VNH5019_H_


class VNH5019
{
  private:
    const int INA_PIN, INB_PIN, PWM_PIN;
    int currentPower;
    
    bool invert = false;
    
    //move function which passes in power percent (which is converted to phase and PWM) to move device
    //could in future be changed to RPM
    void move(const long movement); 
        
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