#include "RoveHBridge.h"


#if defined(ARDUINO)
#include <Arduino.h>


void RoveHBridge::configFrequency(const uint16_t& frequency) {
	analogWriteFrequency(m_forwardPin, frequency);
	analogWriteFrequency(m_reversePin, frequency);
}

void RoveHBridge::drive(int16_t decipercent) {
	decipercent = boundDecipercent(decipercent);

	uint8_t forwardPWM, reversePWM;

	if (decipercent > 0) {
		forwardPWM = decipercent * 255 / 1000;
		reversePWM = 0;
	}
	else {
		reversePWM = decipercent * 255 / 1000;
		forwardPWM = 0;
	}

	analogWrite(m_forwardPin, forwardPWM);
	analogWrite(m_reversePin, reversePWM);
}


#endif