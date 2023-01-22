#include "PWMMotor.h"


int PWMMotor::boundDecipercent(int decipercent) {
	if (m_inverted) decipercent = -decipercent;

	if (decipercent > m_maxDecipercent) return m_maxDecipercent;
	else if (decipercent < m_minDecipercent) return m_minDecipercent;

	return decipercent;
}


#if defined(ARDUINO)
#include <Arduino.h>


void PWMMotor::configFrequency(unsigned int frequency) {
	analogWriteFrequency(m_forwardPort, frequency);
	analogWriteFrequency(m_reversePort, frequency);
}

void PWMMotor::drive(int decipercent) {
	boundDecipercent(decipercent);

	int fwdPWM = decipercent * 255 / 1000;
	int rvsPWM = 0;

	if (fwdPWM < 0) {
		rvsPWM = -fwdPWM;
		fwdPWM = 0;
	}

	analogWrite(m_forwardPort, fwdPWM);
	analogWrite(m_reversePort, rvsPWM);
}


#endif