#include "RoveHBridge.h"


#if defined(ARDUINO)
#include <Arduino.h>


void RoveHBridge::configFrequency(const float frequency) {
	analogWriteFrequency(m_forwardPin, frequency);
	analogWriteFrequency(m_reversePin, frequency);
}

void RoveHBridge::drive(int16_t decipercent) const {
    decipercent = applyConfigs(decipercent);
    
	uint8_t forwardPWM, reversePWM;
	if (decipercent >= 0) {
		forwardPWM = decipercent * 255 * 0.95 / 1000;
		reversePWM = 0;
	}
	else {
		reversePWM = -decipercent * 255 * 0.95 / 1000;
		forwardPWM = 0;
	}

	analogWrite(m_forwardPin, forwardPWM);
	analogWrite(m_reversePin, reversePWM);
}


#endif