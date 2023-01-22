#include "RoveMotor.h"


void RoveMotor::configInvert(bool invert) {
    m_inverted = invert;
}

void RoveMotor::configOutputLimits(int maxDecipercent, int minDecipercent) {
    if (maxDecipercent <= 1000 && maxDecipercent >= 0) m_maxDecipercent = maxDecipercent;
    if (minDecipercent >= -1000 && minDecipercent <= 0) m_minDecipercent = minDecipercent;
}