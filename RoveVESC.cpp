#include "RoveVESC.h"

RoveVESC::RoveVESC(Stream* SerialPort) {
    m_vesc.setSerialPort(SerialPort);
}

void RoveVESC::drive(int16_t decipercent) const {
    decipercent = applyConfigs(decipercent);

    float duty = (float) decipercent / 1000.0;
    m_vesc.setDuty(duty);
}