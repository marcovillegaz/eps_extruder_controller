#include "EncoderHandler.h"
#include "DisplayHandler.h" // Now calls updateDisplay() from here

// Why this are defining here?
Encoder myEnc(ENCODER_PIN_A, ENCODER_PIN_B); // Encoder object

// Variables for encoder handling
int lastEncoderPosition = -1; // Last encoder position
bool buttonPressed = false;   // Button press flag
bool setMode = false;         // Set mode flag
int currentOption = 0;        // 0 for T1, 1 for T2

// Predefined temperature set points
double set_T1 = 25; // Default set point for T1
double set_T2 = 25; // Default set point for T2

void setupEncoder()
{
    pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP); // Enable pull-up resistor
    lastEncoderPosition = myEnc.read() / 4;    // Initialize encoder position
}

// This could be atomized into smaller functions?
void handleEncoder()
{
    int newEncoderPosition = myEnc.read() / 4; // Reduce resolution to 90 degrees

    // Serial print encoder position for debugging
    // Serial.print("Encoder: ");
    // Serial.println(newEncoderPosition);

    // Handle encoder rotation
    if (newEncoderPosition != lastEncoderPosition)
    {
        if (setMode) // Set mode enabled
        {
            if (currentOption == 0)
            { // Set T1
                set_T1 += (newEncoderPosition > lastEncoderPosition) ? -TEMP_STEP : TEMP_STEP;
            }
            else
            { // Set T2
                set_T2 += (newEncoderPosition > lastEncoderPosition) ? -TEMP_STEP : TEMP_STEP;
            }
            set_mode(); // Call display update from DisplayHandler
        }
        else
        { // Normal mode, change between rows
            currentOption = (newEncoderPosition > lastEncoderPosition) ? 1 : 0;
            updateDisplay(); // Call display update from DisplayHandler
        }

        lastEncoderPosition = newEncoderPosition;
    }

    // Handle button press
    if (digitalRead(ENCODER_BUTTON_PIN) == LOW)
    {
        if (!buttonPressed) // Check if button was not pressed before
        {
            buttonPressed = true;
            setMode = !setMode;

            if (!setMode)
            {
                updateDisplay(); // Exit set mode, refresh screen
            }
            else
            {
                set_mode(); // Enter set mode
            }
        }
    }
    else
    {
        buttonPressed = false; // Reset button press flag
    }
}
