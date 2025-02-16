#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H

#include <Arduino.h>
#include <Encoder.h>

// Encoder pins
#define ENCODER_PIN_A 2      // CLK
#define ENCODER_PIN_B 3      // DT
#define ENCODER_BUTTON_PIN 4 // SW

#define TEMP_STEP 1 // Step size for temperature adjustment

extern bool setMode;
extern int currentOption;
extern double set_T1, set_T2;

// Function declarations
void setupEncoder();    // Initialize encoder
void handleEncoder();   // Read encoder state
bool isButtonPressed(); // Check if the button is pressed

extern int selectedThermocouple; // T1 = 0, T2 = 1

#endif
