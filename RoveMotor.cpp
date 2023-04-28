#include "RoveMotor.h"


int16_t RoveMotor::boundDecipercent(int16_t decipercent) const {
    if (decipercent > m_reverseMinDecipercent && decipercent < m_forwardMinDecipercent) decipercent = 0;
	else if (decipercent < m_reverseMaxDecipercent) decipercent = m_reverseMaxDecipercent;
	else if (decipercent > m_forwardMaxDecipercent) decipercent = m_forwardMaxDecipercent;

	return decipercent;
}

int16_t RoveMotor::applyRamp(int16_t decipercent, float timestamp) const {
    if (decipercent == 0) return 0;

    if (m_maxRamp != 0) {
        int32_t ramp = (timestamp - m_lastDriveTimestamp) * m_maxRamp;
        if ((decipercent - m_lastDecipercent) > ramp) {
            decipercent = m_lastDecipercent + ramp;
        }
        else if ((decipercent - m_lastDecipercent) < -ramp) {
            decipercent = m_lastDecipercent - ramp;
        }
    }
    
    return decipercent;
}

void RoveMotor::configInvert(const bool& invert) {
    m_inverted = invert;
}

void RoveMotor::configMaxOutputs(const int16_t& reverseMaxDecipercent, const int16_t& forwardMaxDecipercent) {
    if (reverseMaxDecipercent >= -1000 && reverseMaxDecipercent <= 0) m_reverseMaxDecipercent = reverseMaxDecipercent;
    if (forwardMaxDecipercent <= 1000 && forwardMaxDecipercent >= 0) m_forwardMaxDecipercent = forwardMaxDecipercent;
}

void RoveMotor::configMinOutputs(const int16_t& reverseMinDecipercent, const int16_t& forwardMinDecipercent) {
    if (reverseMinDecipercent >= -1000 && reverseMinDecipercent <= 0) m_reverseMinDecipercent = reverseMinDecipercent;
    if (forwardMinDecipercent <= 1000 && forwardMinDecipercent >= 0) m_forwardMinDecipercent = forwardMinDecipercent;
}

void RoveMotor::configRampRate(const uint16_t& maxRamp) {
    m_maxRamp = maxRamp;
}

int16_t RoveMotor::lastDecipercent() const {
    return m_lastDecipercent;
}