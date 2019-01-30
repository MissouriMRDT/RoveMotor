/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MRDT 2019 => Energia Texas Instruments Tiva C ST Microelectronics VNHxxx series brushed dc motor driver ic
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RoveStmVnhPwm.h"
#include "RoveBoardMap.h"
#include "RovePwmWrite.h"
#include "RovePwmGen.h"

#include <stdint.h>

#include "Energia.h"

/////////////////////////////////////////////////////////////////////////////

void RoveStmVnhPwm::attach( const uint8_t          ina_pin,
                            const uint8_t          inb_pin,
                            const uint8_t          pwm_pin,
                            const uint8_t          adc_pin,
                            const bool        invert_motor,
                            const int       bus_millivolts,
                            const int scale_pwm_millivolts,
                            const int  scale_adc_milliamps )
{ 
  this->ina_pin               =               ina_pin;
  this->inb_pin               =               inb_pin;
  this->pwm_pin               =               pwm_pin;
  this->adc_pin               =               adc_pin;
  this->scale_adc_milliamps   =   scale_adc_milliamps;
  this->invert_motor          =          invert_motor;
  this->scale_pwm_decipercent = ( 1000*scale_pwm_millivolts ) / bus_millivolts;

  if( digitalPinToTimer( pwm_pin ) )
  { this->pwm_mode = USE_ENERGIA_ANALOG_WRITE; }

  else if( roveware::isPwmGenValid( pwm_pin ) )
  { this->pwm_mode = USE_ROVE_PWM_ANALOG_WRITE; }

  else 
  { this->pwm_mode = INVALID; }

  if(            this->pwm_mode != INVALID )
  {   pinMode(   this->pwm_pin,    OUTPUT );
      pinMode(   this->ina_pin,    OUTPUT );
      pinMode(   this->inb_pin,    OUTPUT );
      if (       this->adc_pin  != 0     ){
        pinMode( this->adc_pin,    INPUT );
      } 
} }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveStmVnhPwm::writeCommand( bool ina_value, bool inb_value, int pwm_value )
{
  if( this->invert_motor )
  { ina_value=!ina_value; 
    inb_value=!inb_value; }

  if( this->scale_pwm_decipercent == 0 ){ pwm_value = map( abs( pwm_value ), 0, 1000, 0,   255 ); }
  else                                  { pwm_value = map( abs( pwm_value ), 0, 1000, 0, ( 255*this->scale_pwm_decipercent ) / 1000 ); }

  if(      this->pwm_mode ==  USE_ENERGIA_ANALOG_WRITE ){
            analogWrite( this->pwm_pin, pwm_value);
           digitalWrite( this->ina_pin, ina_value );
           digitalWrite( this->inb_pin, inb_value ); }

  else if( this->pwm_mode == USE_ROVE_PWM_ANALOG_WRITE ){
     rovePwmAnalogWrite( this->pwm_pin, pwm_value );
           digitalWrite( this->ina_pin, ina_value );
           digitalWrite( this->inb_pin, inb_value ); }
}

//////////////////////////////////////////////////////////////////////////
void RoveStmVnhPwm::drive( int decipercent )
{ 
       if ( decipercent  > 0 ) { writeCommand( HIGH, LOW,  decipercent ); }
  else if ( decipercent  < 0 ) { writeCommand( LOW,  HIGH, decipercent ); }
  else if ( decipercent == 0 ) { writeCommand( LOW,  LOW,            0 ); }
}

//////////////////////////////////////////////////////////////////////////
void RoveStmVnhPwm::brake( int decipercent )
{ 
       if ( decipercent  > 0 ) { writeCommand( HIGH, LOW,  decipercent ); }
  else if ( decipercent  < 0 ) { writeCommand( LOW,  HIGH, decipercent ); }
  else if ( decipercent == 0 ) { writeCommand( LOW,  LOW,            0 ); }
}

////////////////////////////////
void RoveStmVnhPwm::coast() 
{ writeCommand( LOW, LOW, 0 ); }

///////////////////////////////////////////////////////////////////////////////////////
int RoveStmVnhPwm::readMilliamps()
{ if( !this->adc_pin ) 
  { return -1; }
  else 
  { return map( analogRead( this->adc_pin ), 0, 1024, 0, this->scale_adc_milliamps ); }
}