#include "ExampleMotor.h"


#if defined(ARDUINO)
#include <Arduino.h>


void ExampleMotor::drive(int decipercent) {
    Serial.print("Port ");
    Serial.print(m_port);
    Serial.print(" driving at ");
    Serial.println((m_inverted? -decipercent : decipercent));
}


#else
#include <iostream>


void ExampleMotor::drive(int decipercent) {
	std::cout << "Port " << m_port << " driving at " << (m_inverted? -decipercent : decipercent) << std::endl;
}


#endif