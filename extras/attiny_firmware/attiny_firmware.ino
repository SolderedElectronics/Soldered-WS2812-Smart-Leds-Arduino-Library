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

// Here is only 1 LED
#define NUMLEDS 1
byte pixels[NUMLEDS * 3];

// Create neopixel object
tinyNeoPixel led = tinyNeoPixel(1, PIN_PA5, NEO_GRB, pixels);

// Declare variables used in the interrupt function
volatile byte color[3] = {0, 0, 0}; // R, G and B color
volatile bool colorChange;

// Default address is 0x30
int addr = DEFAULT_ADDRESS;

void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);

    // Define LED pin as output and turn the LED off (set color to 0, 0, 0)
    pinMode(PIN_PA5, OUTPUT);
    led.setPixelColor(0, led.Color(0, 0, 0));
    led.show();
}

void loop()
{
    // If the change occurs
    if (colorChange)
    {
        // Set the color to the received color
        led.setPixelColor(0, color[0], color[1], color[2]);
        led.show();
        colorChange = 0;
    }
}

// A function that runs when attiny receives any data on I2C
void receiveEvent(int howMany)
{
    // Set colorChange flag to 1
    colorChange = 1;
    byte i = 0;

    // Receive incoming bytes
    while (Wire.available() > 0)
    {
        color[i] = Wire.read();
        i++;
    }
}
