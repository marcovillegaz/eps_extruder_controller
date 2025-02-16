#include <Arduino.h>
#include "RelayHandler.h"

// Relay pins for heating elements
#define RELAY_T1_PIN 22 // Relay for T1 heating element
#define RELAY_T2_PIN 23 // Relay for T2 heating element

// Function to initialize relay pins
void setupRelays()
{
    pinMode(RELAY_T1_PIN, OUTPUT);
    pinMode(RELAY_T2_PIN, OUTPUT);
}

// Control the SSR based on PID output. hreshold to activate SSR (e.g., when output > 50)

void controlRelayT1(double outputT1)
{
    if (outputT1 >= 50)
    {
        digitalWrite(RELAY_T1_PIN, HIGH); // Turn on T1 heating element (AC current flows)
    }
    else
    {
        digitalWrite(RELAY_T1_PIN, LOW); // Turn off T1 heating element (no AC current)
    }
}

void controlRelayT2(double outputT2)
{
    if (outputT2 >= 50)
    {
        digitalWrite(RELAY_T2_PIN, HIGH); // Turn on T2 heating element (AC current flows)
    }
    else
    {
        digitalWrite(RELAY_T2_PIN, LOW); // Turn off T2 heating element (no AC current)
    }
}
