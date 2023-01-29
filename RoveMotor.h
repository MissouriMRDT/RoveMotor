#ifndef ROVEMOTOR_H
#define ROVEMOTOR_H

#include <cstdint>


class RoveMotor {

protected:

    bool m_inverted = false;
    int16_t m_maxDecipercent = 1000, m_minDecipercent = -1000;

    /**
     * @brief Clamp the input decipercent between the configured maximum and minimum values, and invert if necessary.
     * 
     * @param decipercent Decipercent value to bound.
     * @return Decipercent bounded to [m_minDecipercent, m_maxDecipercent].
     */
    int16_t boundDecipercent(int16_t decipercent);

public:

    /**
     * @brief Configure whether to invert the motor when driven.
     * 
     * @param invert
     */
    void configInvert(const bool& invert);

    /**
     * @brief Set the maximum and minimum decipercent values written by drive().
     * 
     * @param maxDecipercent maximum motor output [0, 1000].
     * @param minDecipercent minimum motor output [-1000, 0].
     */
    void configOutputLimits(const int16_t& maxDecipercent, const int16_t& minDecipercent);

    /**
     * @brief Write the provided drive signal to the motor.
     * 
     * @param decipercent Motor output [-1000, 1000].
     */
    virtual void drive(int16_t decipercent) = 0;

};


#endif