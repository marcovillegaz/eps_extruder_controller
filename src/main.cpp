// #include <Arduino.h> included in other files

#include "ThermocoupleHandler.h"
#include "DisplayHandler.h"
#include "EncoderHandler.h"
#include "PIDHandler.h"
#include "RelayHandler.h"

unsigned long previousTemperatureMillis = 0; // To track temperature update time
unsigned long previousEncoderMillis = 0;     // To track encoder update time
unsigned long previousPIDMillis = 0;         // To track PID control time

const long temperatureInterval = 2000; // Interval for temperature update (1000ms)
const long encoderInterval = 100;      // Interval for encoder update (100ms)
const long pidInterval = 500;          // Interval for PID updates (ms)

void setup()
{
    // Initialize Serial Monitor for debugging
    Serial.begin(9600);
    Serial.println("System Initialized");

    setupDisplay();
    setupEncoder();
    setupThermocouples();
    setupPID();

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

    // Perform PID control every 500ms
    if (currentMillis - previousPIDMillis >= pidInterval)
    {
        previousPIDMillis = currentMillis;

        // Set PID inputs from current temperatures
        setPIDInput(T1, T2); // Introduces the lecture from the thermocouples to the PID

        // Update PID calculations
        updatePID();

        // Control relays based on PID outputs
        controlRelayT1(getPIDOutputT1());
        controlRelayT2(getPIDOutputT2());
    }
    // Add other logic for button presses or other actions if needed
    // For example: handle button press, toggle modes, etc.

    delay(10); // Optional delay, small delay to reduce CPU load
}