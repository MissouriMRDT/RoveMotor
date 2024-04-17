#ifndef ROVEVESC_H
#define ROVEVESC_H

#include "RoveMotor.h"

#include <cstdint>

#include <Arduino.h>
#include <VescUart.h>


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
	void drive(int16_t decipercent) const;

};


#endif /* ROVEVESC_H*/