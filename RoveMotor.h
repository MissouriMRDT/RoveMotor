#ifndef ROVEMOTOR_H
#define ROVEMOTOR_H

#include <cstdint>


class RoveMotor {

protected:

    bool m_inverted = false;
    int16_t m_forwardMaxDecipercent = 1000, m_reverseMaxDecipercent = -1000;
    int16_t m_forwardMinDecipercent = 0, m_reverseMinDecipercent = 0;
    uint16_t m_maxRamp = 0;

    mutable int16_t m_lastDecipercent = 0;
    mutable uint32_t m_lastDriveTimestamp = 0;

    /**
     * @brief Apply the configured invert and ramp rate, then clamp between the configured maximum and minimum values.
     * 
     * @param decipercent Decipercent value to apply configs to.
     * @return Decipercent bounded to [m_reverseMaxDecipercent, m_reverseMinDecipercent] U {0} U [m_forwardMinDecipercent, m_forwardMaxDecipercent].
     */
    int16_t applyConfigs(int16_t decipercent) const;

public:

    /**
     * @brief Configure whether to invert the motor when driven.
     * 
     * @param invert
     */
    void configInvert(const bool invert);

    /**
     * @brief Set the maximum and minimum decipercent values written by drive().
     * 
     * @param reverseMaxDecipercent maximum reverse motor output [-1000, 0].
     * @param forwardMaxDecipercent maximum forward motor output [0, 1000].
     */
    void configMaxOutputs(const int16_t reverseMaxDecipercent, const int16_t forwardMaxDecipercent);

    /**
     * @brief Set the decipercent values between which the output of drive() should be 0.
     * 
     * @param reverseMinDecipercent minimum reverse motor output [-1000, 0].
     * @param forwardMinDecipercent minimum forward motor output [0, 1000].
     */
    void configMinOutputs(const int16_t reverseMinDecipercent, const int16_t forwardMinDecipercent);

    /**
     * @brief Configure the maximum ramp rate of the motor.
     * 
     * @param maxRamp in decipercent per second.
     */
    void configRampRate(const uint16_t maxRamp);

    /**
     * @brief Read the last decipercent value written to the motor via drive(), after applying invert, output limits, and ramp rate.
     * 
     * @return Last motor output [-1000, 1000]
     */
    int16_t lastDecipercent() const;

    /**
     * @brief Write the provided drive signal to the motor.
     * 
     * @param decipercent Motor output [-1000, 1000].
     */
    virtual void drive(int16_t decipercent) const = 0;

};


#endif