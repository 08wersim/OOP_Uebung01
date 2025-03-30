
// ****************************************************************************
// *                                                                          *
// * Aufgabe:                                                                 *
// *                                                                          *
// * -> Schreib ein Programm mit folgenden Eigenschaften:                     *
// *    Es gibt zwei Taster (TASTER1, TASTER2), zwei LEDs (LED1, LED2) und    *
// *    ein Potentiometer. Taster1 schaltet einen digitalen Blinker auf die   *
// *    beiden LEDs, Taster2 schaltet einen analogen Blinker auf die beiden   *
// *    LEDs. Die Geschwindigkeit des Blinkers soll mit dem Poti zwischen     *
// *    50ms und 1000ms eingestellt werden können. Ein langer Tastendruck     *
// *    auf einen der beiden Taster toggelt die Blinkfunktion ein/aus.        *
// *                                                                          *
// * -> Suche dir ein/zwei Mitarbeiter und forke dieses Projekt               *
// * -> Teile die Arbeit auf die Mitarbeiter so auf, dass ein fast-forward-   *
// *    merge ermöglicht wird.                                                *
// * -> Fülle die bestehenden Header-Dateien und erzeuge die entsprechenden   *
// *    Implementierungen (cpp-Dateien). Verwende ausschließlich Klassen!     *
// *                                                                          *
// * -> Erstelle einen pull-request                                           *
// *                                                                          *
// *                                                                          *
// ****************************************************************************

#include <Arduino.h>

#define LED1 5    // leuchtet mit high
#define LED2 6    // leuchtet mit high
#define TASTER1 7 // LOW wenn gedrückt
#define TASTER2 8 // LOW wenn gedrückt
#define POT1 A7 
#define TIME_LONGPRESS 1000 // [ms]

#include "analogblinker.h"
#include "helper.h"
#include "digitalblinker.h"

button taster1;
button taster2;

analogblinker analogbl;

blinker digiblinker;

uint16_t blinktime = 500;

uint16_t convertDvToBt(uint16_t n)
{
    uint16_t bt = 950.f/1023 * n + 50;
    return bt;
};

void setup()
{
    Serial.begin(115200); // Baud rate
    Serial.println("..Start..\n");

    pinMode(TASTER1, INPUT_PULLUP);
    pinMode(TASTER2, INPUT_PULLUP);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    taster1.init(TASTER1, true, 20, TIME_LONGPRESS);
    taster2.init(TASTER2, true, 20, TIME_LONGPRESS);

    analogbl.init(LED1, LED2, 25, true, false);

    digiblinker.init(LED1, LED2, false, false, false);
}


bool canBlink = 0;


void loop()
{
    blinktime = convertDvToBt(analogRead(POT1));

    taster1.poll();
    taster2.poll();

    if (taster1.longpress || taster2.longpress)
    {
        canBlink = !canBlink;
    }

    if (!canBlink)
    {
        digiblinker.enable = false;
        analogbl.enable = false;
    }

    else 
    {
        if (taster1.rising)
        {
            analogbl.enable = true;
            digiblinker.enable = false;
        }
    
        else if (taster2.rising)
        {
            analogbl.enable = false;
            digiblinker.enable = true;
        }
    }


    analogbl.poll(blinktime);
    digiblinker.poll(blinktime);
}
