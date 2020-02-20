/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MRDT 2019 => Energia Texas Instruments Tiva C ST Microelectronics VNHxxx series brushed dc motor driver ic
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RoveStmVnhPwm.h"
#include "Arduino.h"

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveStmVnhPwm::attach( uint8_t          ina_pin,
                            uint8_t          inb_pin,
                            uint8_t          pwm_pin,
                            bool        invert_motor,
                            int       bus_millivolts,
                            int  scale_to_millivolts,
                            uint8_t          adc_pin,
                            int  scale_to_milliamps )
{ 
  this->ina_pin               =               ina_pin;
  this->inb_pin               =               inb_pin;
  this->pwm_pin               =               pwm_pin;
  this->invert_motor          =          invert_motor;
  this->scale_pwm_decipercent = ( 1000*scale_to_millivolts ) / bus_millivolts;
  this->adc_pin               =               adc_pin;
  this->scale_adc_milliamps   =    scale_to_milliamps;


  pinMode(   this->pwm_pin,    OUTPUT );
  pinMode(   this->ina_pin,    OUTPUT );
  pinMode(   this->inb_pin,    OUTPUT );
  if (       this->adc_pin  != 0      )
  { pinMode( this->adc_pin,    INPUT ); } 
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveStmVnhPwm::writeCommand( bool ina_value, bool inb_value, int pwm_value )
{
  if( this->invert_motor && (ina_value == true || inb_value == true)) //for Valkyrie moco's to have the LEDS correspond to actual signal
  { ina_value=!ina_value;                                             //we can't invert 0 because then the motors seem to always be on
    inb_value=!inb_value; }

  if( this->scale_pwm_decipercent == 0 ){ pwm_value = map( abs( pwm_value ), 0, 1000, 0,   255 ); }
  else                                  { pwm_value = map( abs( pwm_value ), 0, 1000, 0, ( 255*this->scale_pwm_decipercent ) / 1000 ); }

  analogWrite( this->pwm_pin, pwm_value);
  digitalWrite( this->ina_pin, ina_value );
  digitalWrite( this->inb_pin, inb_value );
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
  { return ~(0); }
  else 
  { return map( analogRead( this->adc_pin ), 0, 1024, 0, this->scale_adc_milliamps ); }
}