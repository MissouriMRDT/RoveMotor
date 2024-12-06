#ifndef ROVEVNH_H
#define ROVEVNH_H

#include "RoveMotor.h"

#include <cstdint>


class RoveVNH : public RoveMotor {

private:

    uint8_t m_pwmPin, m_forwardPin, m_reversePin, m_csPin;
    bool m_hasCS;
    float m_csGain = 1;

public:

    /**
     * @brief Construct a new RoveHBridge object, without current sensing.
     * 
     * @param pwmPin Arduino pin number for the pwm signal. Must be PWM capable.
     * @param forwardPin Arduino pin number for the forward digital output.
     * @param reversePin Arduino pin number for the reverse digital output.
     */
    RoveVNH(const uint8_t pwmPin, const uint8_t forwardPin, const uint8_t reversePin);

    /**
     * @brief Construct a new RoveHBridge object, with current sensing.
     * 
     * @param pwmPin Arduino pin number for the pwm signal. Must be PWM capable.
     * @param forwardPin Arduino pin number for the forward digital output.
     * @param reversePin Arduino pin number for the reverse digital output.
     * @param csPin Arduino pin number for the current sense input. Must be an analog input pin.
     */
    RoveVNH(const uint8_t pwmPin, const uint8_t forwardPin, const uint8_t reversePin, const uint8_t csPin);

    /**
     * @brief Initialize hardware.
     * 
     */
    void init();

    /**
     * @brief Configure the frequency used for the PWM signal.
     * 
     * @param frequency Desired frequency, in Hz.
     */
    void configFrequency(const float frequency);

    /**
     * @brief Configure the scale of the current sensor.
     * 
     * @param gain Conversion factor from CS voltage to motor current (Amps/Volt).
     */
    void configCSScale(float gain);

    /**
     * @brief Read the current draw of the motor.
     * 
     */
    float readCurrent();

    /**
     * @brief Write the provided drive signal to the motor.
     * 
     * @param decipercent Motor output [-1000, 1000].
     */
    void drive(int16_t decipercent) const;

};



#endif /* ROVEVNH_H */