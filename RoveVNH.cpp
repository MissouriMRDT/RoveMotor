#include "RoveVNH.h"


RoveVNH::RoveVNH(const uint8_t pwmPin, const uint8_t forwardPin, const uint8_t reversePin) {
    m_pwmPin = pwmPin;
    m_forwardPin = forwardPin;
    m_reversePin = reversePin;

    m_hasCS = false;
}

RoveVNH::RoveVNH(const uint8_t pwmPin, const uint8_t forwardPin, const uint8_t reversePin, const uint8_t csPin) {
    m_pwmPin = pwmPin;
    m_forwardPin = forwardPin;
    m_reversePin = reversePin;
    m_csPin = csPin;

    m_hasCS = true;
}



#if defined(ARDUINO)
#include <Arduino.h>


void RoveVNH::init() {
    pinMode(m_forwardPin, OUTPUT);
    pinMode(m_reversePin, OUTPUT);
    pinMode(m_pwmPin, OUTPUT);
    digitalWrite(m_forwardPin, LOW);
    digitalWrite(m_reversePin, LOW);
    analogWrite(m_pwmPin, 0);

    if (m_hasCS) {
        pinMode(m_csPin, INPUT);
    }
}

void RoveVNH::configFrequency(const float frequency) {
    analogWriteFrequency(m_pwmPin, frequency);
}

void RoveVNH::configCSScale(float gain) {
    m_csGain = gain * 3.3 / 1023.0; // convert to ADC scale instead of volts
}

float RoveVNH::readCurrent() {
    delayNanoseconds(50);
    float current = analogRead(m_csPin) * m_csGain;

    return current;
}

void RoveVNH::drive(int16_t decipercent) const {
    decipercent = applyConfigs(decipercent);
    uint8_t pwm = decipercent * 255 / 1000;

    if (decipercent > 0) {
        digitalWrite(m_reversePin, LOW);
        digitalWrite(m_forwardPin, HIGH);
    } else if (decipercent < 0) {
        digitalWrite(m_forwardPin, LOW);
        digitalWrite(m_reversePin, HIGH);
    } else {
        digitalWrite(m_forwardPin, LOW);
        digitalWrite(m_reversePin, LOW);
    }

    analogWrite(m_forwardPin, pwm);
}


#endif