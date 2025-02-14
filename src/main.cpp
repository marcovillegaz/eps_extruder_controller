#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

// Prototipe
void updateDisplay();
void set_mode();

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Rotary Encoder Pins
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 3
#define ENCODER_BUTTON_PIN 4

float temp_step = 1;

Encoder myEnc(ENCODER_PIN_A, ENCODER_PIN_B);

// This variables are modified
int currentOption = 0; // 0 = T1, 1 = T2
int lastEncoderPosition = -1;
bool buttonPressed = false;
bool setMode = false; // If true, the encoder adjusts the target temperature

// Example temperatures
float T1 = 432.69, T2 = 227.56;     // Read from sensors in real application
float set_T1 = 30.0, set_T2 = 35.0; // Adjustable target temperatures

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
  updateDisplay();
}

// Ternary operators (condition ? value_if_true : value_if_false;)

void loop()
{
  int newEncoderPosition = myEnc.read() / 2; // Adjust sensitivity

  // Move between options
  if (newEncoderPosition != lastEncoderPosition)
  {
    // If button is pressed, setMode is true
    if (setMode)
    {
      // Set T1 temperature
      if (currentOption == 0)
      {
        set_T1 += (newEncoderPosition > lastEncoderPosition) ? -temp_step : temp_step;
      }
      // Set T2 temperature
      else if (currentOption == 1)
      {
        set_T2 += (newEncoderPosition > lastEncoderPosition) ? -temp_step : temp_step;
      }
      set_mode(); // Update display while adjusting
    }
    else
    {
      // Switch between T1 and T2 selection
      currentOption = (newEncoderPosition > lastEncoderPosition) ? 1 : 0;
      updateDisplay(); // Update selection
    }

    lastEncoderPosition = newEncoderPosition;
  }

  // Handle Button Press to Toggle Set Mode
  if (digitalRead(ENCODER_BUTTON_PIN) == LOW)
  {
    if (!buttonPressed)
    {
      buttonPressed = true;
      setMode = !setMode; // Toggle mode
      if (!setMode)
      {
        updateDisplay(); // Immediately refresh when exiting set mode
      }
      else
      {
        set_mode(); // Show SetMode sreen
      }
    }
  }
  else
  {
    buttonPressed = false;
    // updateDisplay();
  }
}

// This function update the display
void updateDisplay()
{
  lcd.clear();

  // First row - T1
  lcd.setCursor(0, 0);
  lcd.print(currentOption == 0 ? ">T1:" : " T1:");
  lcd.setCursor(5, 0);
  lcd.print(T1, 1);
  lcd.print((char)223);
  lcd.print("C ");
  // lcd.setCursor(11, 0);
  // lcd.print("Set:"); lcd.print(setTempT1, 1);

  // Second row - T2
  lcd.setCursor(0, 1);
  lcd.print(currentOption == 1 ? ">T2:" : " T2:");
  lcd.setCursor(5, 1);
  lcd.print(T2, 1);
  lcd.print((char)223);
  lcd.print("C ");
  // lcd.setCursor(11, 1);
  // lcd.print("Set:"); lcd.print(setTempT2, 1);
}

void set_mode()
{
  // Set T1
  if (currentOption == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set T1:");
    lcd.setCursor(5, 1);
    lcd.print(set_T1);
  }
  // Set T2
  else if (currentOption == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set T2:");
    lcd.setCursor(5, 1);
    lcd.print(set_T2);
  }
  // updateDisplay();
}