#include "analogblinker.h"

void analogblinker::init(uint8_t _pin1, uint8_t _pin2, uint8_t _polltime, bool _sync, bool _enable)
{
    pin1 = _pin1;
    pin2 = _pin2;
    polltime = _polltime;
    sync = _sync;
    enable = _enable;
}

void analogblinker::poll(uint16_t blinkTime)
{
    if (!enable)
    {
        return;
    }
    else if (millis() - lastpoll > polltime)
    {
        step = 256 / ( blinkTime / polltime);
        dutycycle += step;
        if (dutycycle >= 511)
        {
            dutycycle = 0;
        }
        uint16_t pwm = dutycycle > 255 ? 511 - dutycycle : dutycycle;
        analogWrite(pin1, pwm);
        if (sync)
            analogWrite(pin2, pwm);
        else
            analogWrite(pin2, 255 - pwm);
        lastpoll = millis();
    }
}


