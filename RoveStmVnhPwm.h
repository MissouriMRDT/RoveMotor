/////////////////////////////////////////////////////////////////////////////////////////////////////
// Last update MRDT Jan 2019                                                                       //
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ROVE_STM_VNH_PWM_H
#define ROVE_STM_VNH_PWM_H

#include "RoveBoardMap.h"

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// USE_ENERGIA_ANALOG_WRITE  => Energia analogWrite acquires a general timer (0 ~ 255 units) @ 490 hz => 2040 uS period, 8uS minimum width
// USE_ROVE_PWM_ANALOG_WRITE => roveGenAnalogWrite  acquires a pwm generator (0 ~ 255 units) @ 490 hz => 2040 uS period, 8uS minimum width

//////////////////////////////////////////////////////////
class RoveStmVnhPwm
{
public:
// bool isPinValid ( const uint8_t pin ); todo
// bool isEnergiaAnalogWritePin ( const uint8_t pin ); todo
// bool isPwmAnalogWritePinValid ( const uint8_t pin ); todo

  void attach( const uint8_t ina_pin,
               const uint8_t inb_pin,
               const uint8_t pwm_pin,
               const uint8_t adc_pin              = INVALID,
               const bool    invert_motor         = false,
               const int     bus_millivolts       = 12000, // 12V bus
               const int     scale_pwm_millivolts = 12000, // 12V max = 100.0% scale
               const int     scale_adc_milliamps  = 20000 );
  void drive(  const int     decipercent );
  void brake(  const int     decipercent );
  void coast(); 
  int  readMilliamps();

private:
 enum PWM_MODE { USE_ENERGIA_ANALOG_WRITE  = 1,
                 USE_ROVE_PWM_ANALOG_WRITE = 2, };

  uint8_t pwm_mode              = INVALID;
  uint8_t ina_pin;
  uint8_t inb_pin;
  uint8_t pwm_pin;
  uint8_t adc_pin;
  bool    invert_motor          = false;
  int     scale_pwm_decipercent = 1000;
  int     scale_adc_milliamps   = 20000;

  void writeCommand( bool ina_value, bool inb_value, int pwm_value );
};

#endif // ROVE_STM_VNH_PWM_H