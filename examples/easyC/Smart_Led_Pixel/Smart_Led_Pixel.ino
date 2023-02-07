/**
 **************************************************
 * @file        Smart_Led_Pixel.ino
 * @brief       Simple example of controlling the WS2812B LED pixel breakout with easyC.
 *              Connect WS2812B breakout with easyC to Dasduino or Inkplate board with easyC cable.
 *
 *              Don't have Dasduino/Inkplate/easyC? Get it here:
 *              Dasduino: https://soldered.com/categories/dasduino-arduino/
 *              Inkplate: https://soldered.com/categories/inkplate/
 *              easyC:    https://soldered.com/product/easyc-cable-20cm/
 *
 *              Looking to get support? Write on our forums: https://forum.soldered.com/
 *
 * @link        www.solde.red/333187
 * @authors     Karlo Leksic for Soldered
 ***************************************************/

#include "WS2812-SOLDERED.h" //Include Soldered library

WS2812 pixel; // If the pixel is easyC, you don't need to specify any parameters

uint32_t pink = pixel.Color(255, 0, 150); // Example for makeing color variables

byte effect;                // Variable to know which effect is currently active
long time1, timeout = 6000; // Variables to change effects periodically

void setup()
{
    pixel.begin(0x30);       // Set the default I2C address (0x30)
    pixel.setBrightness(50); // Set the pixel brightness (0 - 255)
    time1 = millis();        // Set millis to the beginning value
    effect = 0;              // Start with the first effect
}

void loop()
{
    // Running effect 1 when the effect variable is  equal to 1
    if (effect == 0)
    {
        blinking(pink, 500);
    }

    // Running effect 2 when the effect variable is  equal to 2
    if (effect == 1)
    {
        rainbowColors(20);
    }

    // Running effect 3 when the effect variable is  equal to 3
    if (effect == 2)
    {
        rgbBlinking(500);
    }

    // Periodicly change the effect variable every 6 seconds
    if ((unsigned long)(millis() - time1) > timeout)
    {
        effect++;
        if (effect > 2)
        { // There are 3 effects so the effect variable going from 0 to 2
            effect = 0;
        }
        time1 = millis();
    }
}

/**
 * @brief            Turning the LED on and off
 *
 * @param color      Color in pixel.Color(R, G, B) format.
 *                   Each color is from 0 to 255 (byte).
 *
 * @param delayTime  Time to delay between turning on and off the LED
 *
 * @return           None
 */
void blinking(uint32_t color, int delayTime)
{
    pixel.setPixelColor(0, color); // Set the pixel color to the color passed in the function
    delay(delayTime);              // Delay before turning off the pixel
    pixel.clear();                 // Turn off the pixel (same as pixel.Color(0, 0, 0, 0);)
    delay(delayTime);              // Delay before turning on the pixel
}

/**
 * @brief            Turning the LED on and off and changing RGB color
 *
 * @param delayTime  Time to delay between turning on and off the LED
 *
 * @return           None
 */
void rgbBlinking(int delayTime)
{

    uint32_t colors[3] = {
        // Color array
        pixel.Color(255, 0, 0), // red
        pixel.Color(0, 255, 0), // green
        pixel.Color(0, 0, 255)  // blue
    };

    for (int i = 0; i < 3; ++i)
    {                                      // Pass 3 times through the loop because there are 3 colors (r, g, and b)
        pixel.setPixelColor(0, colors[i]); // Set pixel color to one from the colors array
        delay(delayTime);                  // Delay before turning off the pixel
        pixel.clear();                     // Turn off the pixel (same as pixel.Color(0, 0, 0, 0);)
        delay(delayTime);                  // Delay before turning on the pixel
    }
}

/**
 * @brief            Changing the color of the LED to rainbow colors
 *
 * @param delayTime  Time to delay before increasing the HUE
 *
 * @return           None
 */
void rainbowColors(int delayTime)
{
    static int hue = 0;                   // Static hue variable
    uint32_t color = pixel.ColorHSV(hue); // Color variable with custom hue
    pixel.setPixelColor(0, color);        // Set the pixel color to the color passed in the function
    delay(delayTime); // The delay between changing the color hue (number must be small to see changes e.g. c 20ms)
    hue += 256;       // The HUE values are between 0 and 65535 and this is the step of changing those values
}
