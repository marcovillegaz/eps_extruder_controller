#include "ThermocoupleHandler.h"
#include <max6675.h>

// Shared CLK and DO for both thermocouples
#define MAX6675_CLK 8 // Serial Clock (SCK) = Clock (CLK)
#define MAX6675_DO 9  // Serial Out (SO) = Data Out (DO)

// Unique Chip Select (CS) for each thermocouple
#define MAX6675_T1_CS 10 // Chip Select for Thermocouple 1
#define MAX6675_T2_CS 11 // Chip Select for Thermocouple 2

// This are public variables
// Thermo cuple 1 (T1)
MAX6675 thermocouple1(MAX6675_CLK, MAX6675_T1_CS, MAX6675_DO);
// Thermo cuple 2 (T2)
MAX6675 thermocouple2(MAX6675_CLK, MAX6675_T2_CS, MAX6675_DO);

float T1 = 0, T2 = 0; // Initialize values

void setupThermocouples()
{
    Serial.print("Thermocouple are initialized");
}

void readTemperatures()
{
    T1 = thermocouple1.readCelsius();
    T2 = thermocouple2.readCelsius();

    Serial.print("Thermocouple 1: ");
    Serial.print(T1);
    Serial.println(" °C");

    Serial.print("Thermocouple 2: ");
    Serial.print(T2);
    Serial.println(" °C");

    Serial.println("---------------------------");
}
