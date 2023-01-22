#ifndef PWMMOTOR_H
#define PWMMOTOR_H

#include "RoveMotor.h"

class PWMMotor : public RoveMotor {

private:

	int m_forwardPort, m_reversePort;
	int boundDecipercent(int decipercent);

public:

	PWMMotor(int forwardPort, int reversePort) : m_forwardPort(forwardPort), m_reversePort(reversePort) {}

	void configFrequency(unsigned int frequency);

	void drive(int decipercent);

};

#endif