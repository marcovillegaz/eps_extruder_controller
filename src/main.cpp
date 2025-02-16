#include <Arduino.h>
#include "ThermocoupleHandler.h"
#include "DisplayHandler.h"
#include "EncoderHandler.h"

unsigned long previousTemperatureMillis = 0; // To track temperature update time
unsigned long previousEncoderMillis = 0;     // To track encoder update time

const long temperatureInterval = 2000; // Interval for temperature update (1000ms)
const long encoderInterval = 100;      // Interval for encoder update (100ms)

void setup()
{
    // Initialize Serial Monitor for debugging
    Serial.begin(9600);
    Serial.println("System Initialized");

    setupDisplay();
    setupEncoder();
    setupThermocouples();

    updateDisplay(); // Initial display update
}

void loop()
{
    unsigned long currentMillis = millis(); // Get the current time

    // Handle encoder every 100ms
    if (currentMillis - previousEncoderMillis >= encoderInterval)
    {
        previousEncoderMillis = currentMillis;
        handleEncoder(); // Handle encoder inputs and update the display
    }

    // Update temperature every 1000ms
    if (currentMillis - previousTemperatureMillis >= temperatureInterval)
    {
        previousTemperatureMillis = currentMillis;
        if (!setMode)
        {                       // Only update temperatures when not in setMode
            readTemperatures(); // Read temperatures from the sensors
            updateDisplay();    // Update the display with new temperature values
        }
    }

    // Add other logic for button presses or other actions if needed
    // For example: handle button press, toggle modes, etc.

    delay(10); // Optional delay, small delay to reduce CPU load
}