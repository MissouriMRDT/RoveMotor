#include "TestMotor.h"


#if defined(ARDUINO)
#include <Arduino.h>

void TestMotor::drive(int16_t decipercent) const {
    decipercent = applyConfigs(decipercent);

    Serial.print("Pin ");
    Serial.print(m_pin);
    Serial.print(" driving at ");
    Serial.println(decipercent);
}

#else
#include <iostream>

void TestMotor::drive(int16_t decipercent) const {
    decipercent = applyConfigs(decipercent);

	std::cout << "Pin " << m_pin << " driving at " << decipercent << std::endl;
}

#endif