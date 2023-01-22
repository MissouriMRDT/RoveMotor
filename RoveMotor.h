#ifndef ROVEMOTOR_H
#define ROVEMOTOR_H

class RoveMotor {

protected:

    bool m_inverted = false;
    int m_maxDecipercent = 1000, m_minDecipercent = -1000;

public:

    void configInvert(bool invert);
    void configOutputLimits(int maxDecipercent, int minDecipercent);

    virtual void drive(int decipercent) = 0;

};

#endif