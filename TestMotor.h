#ifndef TESTMOTOR_H
#define TESTMOTOR_H

#include "RoveMotor.h"

#include <cstdint>


class TestMotor : public RoveMotor {

private:

	uint8_t m_pin;

public:

	/**
	 * @brief Construct a new TestMotor object.
	 * 
	 * @param pin An arbitrary pin number to identify the TestMotor.
	 */
	TestMotor(const uint8_t& pin) : m_pin(pin) {}

	/**
	 * @brief Print the motor's pin number and the provided drive signal.
	 * 
	 * @param decipercent Motor output [-1000, 1000].
     * @param timestamp Current timestamp in seconds.
	 */
	void drive(int16_t decipercent, float timestamp) const;
	
};


#endif