#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// External variables (from EncoderHandler)
extern bool setMode;
extern int currentOption;

// External variables (from TemperatureHandler)
extern int set_T1, set_T2;
extern float T1, T2;

void setupDisplay();
void updateTemperature(float T1, float T2);
void updateDisplay();
void set_mode();

#endif