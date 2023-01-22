#ifndef EXAMPLEMOTOR_H
#define EXAMPLEMOTOR_H

#include "RoveMotor.h"

class ExampleMotor : public RoveMotor {

private:

	int m_port;

public:

	ExampleMotor(int port) : m_port(port) {}

	void drive(int decipercent);
	
};

#endif