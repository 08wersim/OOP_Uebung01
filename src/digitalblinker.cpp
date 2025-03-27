#include "digitalblinker.h"
#include <Arduino.h>

// Pin1, Pin2, blinktime [ms],  enable
void blinker::init(uint8_t _pin1, uint8_t _pin2, bool _enable, bool _inv1, bool _inv2)
{
    pin1 = _pin1,
    pin2 = _pin2;
    // blinktime = _blinktime;
    enable = _enable;
    inv1 = _inv1;
    inv2 = _inv2;
}
void blinker::poll()
{
    if (enable)
    {
        if (((inv1 == true) && (inv2 == false)) || ((inv1 == false) && (inv2 == true)))
        {
            // if (millis() - lastblink > blinktime)
            // {
                digitalWrite(pin1, !digitalRead(pin1));
                digitalWrite(pin2, digitalRead(pin1));

                lastblink = millis();
            // }
        }
        else
        {
            // if (millis() - lastblink > blinktime)
            // {
                // Serial.println("vorher");
                // Serial.println(pin1);
                // Serial.println(pin2);

                digitalWrite(pin1, !digitalRead(pin1));
                digitalWrite(pin2, !digitalRead(pin1));

                // // Serial.println("nacher");
                // Serial.println(pin1);
                // Serial.println(pin2);

    
                lastblink = millis();
            // }
        }
    }

    else
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
    }
}
