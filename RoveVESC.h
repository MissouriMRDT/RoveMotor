#ifndef ROVEVESC_H
#define ROVEVESC_H

#include "RoveMotor.h"

#include <cstdint>

#include <Arduino.h>
#include <VescUart.h>

struct VescValues {
    float avgMotorCurrent;
    float avgInputCurrent;
    float dutyCycleNow;
    float rpm;
    float inpVoltage;
    float ampHours;
    float ampHoursCharged;
    float wattHours;
    float wattHoursCharged;
    long tachometer;
    long tachometerAbs;
    float tempMosfet;
    float tempMotor;
    float pidPos;
    uint8_t id;
    mc_fault_code error;
};

class RoveVESC : public RoveMotor {

private:

    mutable VescUart m_vesc;

public:

    /**
     * @brief Construct a new RoveVESC object.
     * 
     * @param SerialPort Arduino serial port, i.e. Serial1
     */
    RoveVESC(Stream* SerialPort);

    /**
     * @brief Write the provided drive signal to the motor via Arduino analogWrite().
     * 
     * @param decipercent Motor output [-1000, 1000].
     */
    void drive(int16_t decipercent) const override;

    VescValues getVescTelemetry();

};


#endif /* ROVEVESC_H*/