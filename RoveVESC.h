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
    uint8_t m_poles = 14;
    float m_maxRPM = 5000;
    float m_gearRatio = 1; // Input over output

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

    /**
     * @brief Write the provided RPM to the motor.
     * 
     * @param normalizedSpeed Motor output [-1.0, 1.0].
     */
    void driveRPM(float normalizedSpeed) const;

    /**
     * @brief Query the VESC for telemetry.
     * 
     * @return VESC telemetry as a VescValues struct.
     */
    VescValues getVescTelemetry() const;

    /**
     * @brief Set the maximum RPM. Default is 5000.
     * 
     * @param maxRPM Maximum output RPM.
     */
    void configMaxRPM(float maxRPM);

    /**
     * @brief Get the maximum RPM set for this RoveVESC.
     * 
     * @return The maximum RPM
     */
    float getMaxRPM() const;

    /**
     * @brief Set the number of motor poles. Default is 14.
     * 
     * @param poles The number of motor poles.
     */
    void configMotorPoles(uint8_t poles);

    /**
     * @brief Get the number of motor poles for this RoveVESC.
     * 
     * @return The number of motor poles.
     */
    uint8_t getPoles() const;

    /**
     * @brief Set the gear ratio of the gearbox. Default is 1.
     * 
     * @param gearRatio Gear ratio computed as (input turns / output turns).
     */
    void configGearRatio(float gearRatio);

    /**
     * @brief Get the gear ratio for this RoveVESC
     * 
     * @return The gear ratio computed as (input turns / output turns).
     */
    float getGearRatio() const;

};


#endif /* ROVEVESC_H*/