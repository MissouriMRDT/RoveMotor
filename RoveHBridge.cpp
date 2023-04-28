#include "RoveHBridge.h"


#if defined(ARDUINO)
#include <Arduino.h>


void RoveHBridge::configFrequency(const uint16_t& frequency) {
	analogWriteFrequency(m_forwardPin, frequency);
	analogWriteFrequency(m_reversePin, frequency);
}

void RoveHBridge::drive(int16_t decipercent, float timestamp) const {
    if (m_inverted) decipercent = -decipercent;
	decipercent = applyRamp(boundDecipercent(decipercent), timestamp);
    
	uint8_t forwardPWM, reversePWM;
	if (decipercent >= 0) {
		forwardPWM = decipercent * 255 / 1000;
		reversePWM = 0;
	}
	else {
		reversePWM = -decipercent * 255 / 1000;
		forwardPWM = 0;
	}

	analogWrite(m_forwardPin, forwardPWM);
	analogWrite(m_reversePin, reversePWM);

    m_lastDecipercent = decipercent;
    m_lastDriveTimestamp = timestamp;
}


#endif