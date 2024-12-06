#ifndef ROVEHBRIDGE_H
#define ROVEHBRIDGE_H

#include "RoveMotor.h"

#include <cstdint>


class RoveHBridge : public RoveMotor {

private:

    uint8_t m_forwardPin, m_reversePin;

public:

    /**
     * @brief Construct a new RoveHBridge object.
     * 
     * @param forwardPin The Arduino pin number for the forward PWM signal.
     * @param reversePin The Arduino pin number for the reverse PWM signal.
     */
    RoveHBridge(const uint8_t forwardPin, const uint8_t reversePin) : m_forwardPin(forwardPin), m_reversePin(reversePin) {}

    /**
     * @brief Configure the Arduino analogWriteFrequency() for the forward and reverse pins.
     * 
     * @param frequency Desired frequency, in Hz.
     */
    void configFrequency(const float frequency);

    /**
     * @brief Write the provided drive signal to the motor via Arduino analogWrite().
     * 
     * @param decipercent Motor output [-1000, 1000].
     */
    void drive(int16_t decipercent) const;

};


#endif