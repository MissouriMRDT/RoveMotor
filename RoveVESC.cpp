#include "RoveVESC.h"

RoveVESC::RoveVESC(Stream* SerialPort) {
    m_vesc.setSerialPort(SerialPort);
}

void RoveVESC::drive(int16_t decipercent) const {
    decipercent = applyConfigs(decipercent);

    float duty = (float) decipercent / 1000.0;
    m_vesc.setDuty(duty);
}

void RoveVESC::driveRPM(float normalizedSpeed) const {
    float rpm = normalizedSpeed * m_maxRPM;
    rpm *= (m_poles / 2.0f) * m_gearRatio;

    m_vesc.setRPM(rpm);
}


VescValues RoveVESC::getVescTelemetry() const {
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

void RoveVESC::setMaxRPM(float maxRPM) {
    m_maxRPM = maxRPM;
}

float RoveVESC::getMaxRPM() const {
    return m_maxRPM;
}

void RoveVESC::setPoles(uint8_t poles) {
    m_poles = poles;
}

uint8_t RoveVESC::getPoles() const {
    return m_poles;
}

void RoveVESC::setGearRatio(float gearRatio) {
    m_gearRatio = gearRatio;
}

float RoveVESC::getGearRatio() const {
    return m_gearRatio;
}
