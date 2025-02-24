#include "RoveVESC.h"

RoveVESC::RoveVESC(Stream* SerialPort) {
    m_vesc.setSerialPort(SerialPort);
}

void RoveVESC::drive(int16_t decipercent) const {
    decipercent = applyConfigs(decipercent);

    float duty = (float) decipercent / 1000.0;
    m_vesc.setDuty(duty);

    // RPM control
    /*
    // map to [0, 750] RPM
    float rpm = decipercent * 750 / 1000.0;
    rpm *= 9; // motor must spin 9x faster to spin the wheel at the desired RPM
    rpm /= 14; // engine RPM = rpm * #poles 

    m_vesc.setRPM(rpm);
    */
}

RoveVESC RoveVESC::getVescTelemetry() {
    VescValues ret;
    m_vesc.getVescValues();
    ret.avgMotorCurrent = m_vesc.data.avgMotorCurrent;
    ret.avgInputCurrent = m_vesc.data.avgInputCurrent;
    ret.dutyCycleNow = m_vesc.data.dutyCycleNow;
    ret.rpm = m_vesc.data.rpm;
    ret.inpVoltage = m_vesc.data.inpVoltage;
    ret.ampHours = m_vesc.data.ampHours;
    ret.ampHoursCharged = m_vesc.data.ampHoursCharged;
    ret.wattHours = m_vesc.data.wattHours;
    ret.wattHoursCharged = m_vesc.data.wattHoursCharged;
    ret.tachometer = m_vesc.data.tachometer;
    ret.tachometerAbs = m_vesc.data.tachometerAbs;
    ret.tempMosfet = m_vesc.data.tempMosfet;
    ret.tempMotor = m_vesc.data.tempMotor;
    ret.pidPos = m_vesc.data.pidPos;
    ret.id = m_vesc.data.id;
    ret.error = m_vesc.data.error;
    return ret;
}
