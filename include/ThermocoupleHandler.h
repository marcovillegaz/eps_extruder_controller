#ifndef THERMOCOUPLE_HANDLER_H
#define THERMOCOUPLE_HANDLER_H

#include <Arduino.h>

extern double T1, T2; // Declare global variables

void setupThermocouples();
void readTemperatures();

#endif
