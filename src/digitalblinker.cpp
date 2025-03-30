#include "digitalblinker.h"
#include <Arduino.h>

// Pin1, Pin2, invertiert pin1, invertiert pin2,  enable
void blinker::init(uint8_t _pin1, uint8_t _pin2, bool _inv1, bool _inv2, bool _enable)
{
    pin1 = _pin1,
    pin2 = _pin2;
    // blinktime = _blinktime;
    inv1 = _inv1;
    inv2 = _inv2;
    enable = _enable;
}
void blinker::poll(uint16_t blinktime)
{

    if (enable)
    {
        if (((inv1 == true) && (inv2 == false)) || ((inv1 == false) && (inv2 == true)))
        {
            if (millis() - lastblink > blinktime)
            {
                digitalWrite(pin1, !digitalRead(pin1));
                digitalWrite(pin2, digitalRead(pin1));

                lastblink = millis();
            }
        }
        else
        {
            if (millis() - lastblink > blinktime)
            {
                // Serial.println("vorher");
                // Serial.println(pin1);
                // Serial.println(pin2);

                digitalWrite(pin1, !digitalRead(pin1));
                digitalWrite(pin2, !digitalRead(pin1));
                // Serial.println("vorgang ausgeführt");

                // // Serial.println("nacher");
                // Serial.println(pin1);
                // Serial.println(pin2);

    
                lastblink = millis();
            }
        }
    }

    else
    {
        return;
    }
}
