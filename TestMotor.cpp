#include "TestMotor.h"


#if defined(ARDUINO)
#include <Arduino.h>


void TestMotor::drive(int16_t decipercent, float timestamp) const {
    if (m_inverted) decipercent = -decipercent;
    decipercent = applyRamp(boundDecipercent(decipercent), timestamp);

    Serial.print("Pin ");
    Serial.print(m_pin);
    Serial.print(" driving at ");
    Serial.println(decipercent);

    m_lastDecipercent = decipercent;
    m_lastDriveTimestamp = timestamp;
}


#else
#include <iostream>


void TestMotor::drive(int16_t decipercent, float timestamp) const {
    if (m_inverted) decipercent = -decipercent;
    decipercent = applyRamp(boundDecipercent(decipercent), timestamp);

	std::cout << "Pin " << m_pin << " driving at " << decipercent << std::endl;
    
    m_lastDecipercent = decipercent;
    m_lastDriveTimestamp = timestamp;
}


#endif