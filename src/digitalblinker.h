#ifndef DIGITALBLINKER_H
#define DIGITALBLINKER_H

#include <Arduino.h>
class blinker
{
public:

bool enable;
void init(uint8_t, uint8_t, bool, bool, bool);
void poll(uint16_t);

private:

unsigned long lastblink;
bool inv1 = false, inv2 = false;
uint8_t pin1, pin2;
// uint16_t blinktime;
// uint8_t convertDvToBt(uint16_t);

};


#endif