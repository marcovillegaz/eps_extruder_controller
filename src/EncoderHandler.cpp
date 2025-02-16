#include "EncoderHandler.h"
#include "DisplayHandler.h" // Now calls updateDisplay() from here

Encoder myEnc(ENCODER_PIN_A, ENCODER_PIN_B);

int lastEncoderPosition = -1;
bool buttonPressed = false;
bool setMode = false;
int currentOption = 0;
int set_T1 = 25;
int set_T2 = 25;

void setupEncoder()
{
    pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP); // Enable pull-up resistor
    lastEncoderPosition = myEnc.read() / 4;    // Initialize encoder position
}

void handleEncoder()
{
    int newEncoderPosition = myEnc.read() / 4; // Adjust sensitivity

    Serial.print("Encoder: ");
    Serial.println(newEncoderPosition);

    if (newEncoderPosition != lastEncoderPosition)
    {
        if (setMode)
        {
            if (currentOption == 0)
            {
                set_T1 += (newEncoderPosition > lastEncoderPosition) ? -TEMP_STEP : TEMP_STEP;
            }
            else
            {
                set_T2 += (newEncoderPosition > lastEncoderPosition) ? -TEMP_STEP : TEMP_STEP;
            }
            set_mode(); // Call display update from DisplayHandler
        }
        else
        {
            currentOption = (newEncoderPosition > lastEncoderPosition) ? 1 : 0;
            updateDisplay(); // Call display update from DisplayHandler
        }

        lastEncoderPosition = newEncoderPosition;
    }

    // Handle button press
    if (digitalRead(ENCODER_BUTTON_PIN) == LOW)
    {
        if (!buttonPressed)
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
        buttonPressed = false;
    }
}
