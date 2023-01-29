#include "RoveMotor.h"


int16_t RoveMotor::boundDecipercent(int16_t decipercent) {
	if (decipercent > m_maxDecipercent) decipercent = m_maxDecipercent;
	else if (decipercent < m_minDecipercent) decipercent = m_minDecipercent;

	if (m_inverted) decipercent = -decipercent;

	return decipercent;
}

void RoveMotor::configInvert(const bool& invert) {
    m_inverted = invert;
}

void RoveMotor::configOutputLimits(const int16_t& maxDecipercent, const int16_t& minDecipercent) {
    if (maxDecipercent <= 1000 && maxDecipercent >= 0) m_maxDecipercent = maxDecipercent;
    if (minDecipercent >= -1000 && minDecipercent <= 0) m_minDecipercent = minDecipercent;
}