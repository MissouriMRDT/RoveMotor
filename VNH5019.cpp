#include "VNH5019"

static const int PWM_MIN = 0, PWM_MAX = 255;

VNH5019::VNH5019(const int PwmPin, const int InaPin, const int InbPin, bool upsideDown): INA_PIN(InaPin), INB_PIN(InbPin), PWM_PIN(PwmPin)
{
  pinMode(INA_PIN, OUTPUT);
  pinMode(INB_PIN, OUTPUT);
  
  //brake motor by default
  digitalWrite(INA_PIN, LOW);
  digitalWrite(INB_PIN, LOW);
  
  if(upsideDown)
  {
    invert = true;
  }
}

void VNH5019::drive(uint8_t motor_percent)
{
  int percent = motor_percent;
  int pwm = 0;
    //if mounted upside down then invert the signal passed to it and move accordingly
  if (invert)
  {
    percent *=-1;
  }

  currentPower = percent;

  //if supposed to move backwards
  if(percent < 0)
  {
    percent = abs(percent);
    pwm = map(percent, 0, 100, PWM_MIN, PWM_MAX); //map percentage into pwm

    //set InB to 0 and InA to 1 for "reverse" rotation
    digitalWrite(INA_PIN, HIGH);
    digitalWrite(INB_PIN, LOW);
  
    analogWrite(PWM_PIN, pwm);
  }

  //if forwards
  else if(percent > 0)
  {
    pwm = map(percent, 0, 100, PWM_MIN, PWM_MAX); //map percentage into pwm
  
    //set InB to 1 and InA to 0 for forward rotation
    digitalWrite(INA_PIN, LOW);
    digitalWrite(INB_PIN, HIGH);
  
    analogWrite(PWM_PIN, pwm);
  }

  //stop
  else if(percent == 0)
  {
    stop();
  }
  
  return;
}

void VNH5019::brake(uint8_t brake_percent)
{ 
  pwm = map(brake_speed, 0, 100, PWM_MIN, PWM_MAX); //map percentage into pwm
  
  digitalWrite(INA_PIN, HIGH);
  digitalWrite(INB_PIN, HIGH); 
  analogWrite(PWM_PIN, pwm);
}

long VNH5019::getCurrentMove()
{
  if(invert) //if we're inverted, then we technically move negatively even if we're moving in the 'positive' direction. The direction is the important part
  {
    return(currentPower * -1); 
  }
  else
  {
    return(currentPower);
  }
}

void VNH5019::stop()
{
  digitalWrite(INA_PIN, LOW);
  digitalWrite(INB_PIN, LOW);
  
  currentPower = 0;
}