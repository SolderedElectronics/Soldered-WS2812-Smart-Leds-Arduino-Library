/**
 **************************************************
 *
 * @file        attiny_firmware.ino
 * @brief       ATTINY firmware for WS2812 with easyC
 *

 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>
#include <tinyNeoPixel_Static.h>

#define NUMLEDS 1
byte pixels[NUMLEDS * 3];
tinyNeoPixel led = tinyNeoPixel(1, PIN_PA5, NEO_GRB, pixels);

volatile byte color[4] = {0, 0, 0}; // R, G and B color
volatile bool colorChange;

int addr = DEFAULT_ADDRESS;

void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    pinMode(PIN_PA5, OUTPUT);
    led.setPixelColor(0, led.Color(0, 150, 0));
    led.show();
}

void loop()
{
    if (colorChange)
    {
        led.setPixelColor(0, color[0], color[1], color[2]);
        led.show();
        colorChange = 0;
    }
}


void receiveEvent(int howMany)
{
    colorChange = 1;
    byte i = 0;
    while (Wire.available() > 0)
    {
        color[i] = Wire.read();
        i++;
    }
}

void requestEvent()
{
    int n = 5;

    char a[n];
    Wire.write(a, n);
}
