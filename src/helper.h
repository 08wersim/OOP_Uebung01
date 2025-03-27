#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>
#include "analogblinker.h"

class button
{
public:

    // Member-Variable(n)
    bool rising = false;
    bool falling = false;
    bool longpress = false;

    // Methode(n)
    // Pin-Nummer, true = negative Logik, Debounce-Zeit [ms], Zeitgrenze für langen Druck [ms]
    void init(uint8_t, bool, uint8_t, uint16_t);

    void poll();

private:

    bool db_last = false;
    unsigned long lasttime = 0;
    unsigned long last_rising = 0;
    bool last = false;
    bool in = false;
    bool neg = false;
    bool debounced = false;

    uint8_t pinNr = 0;
    uint8_t debounce_time = 20;
    uint16_t longpress_time = 1000;

    // wenn Debounce-Zeit = 0, dann kein Debounce
    void debounce();
    void check_edge();
    void check_longpress();
};


#endif