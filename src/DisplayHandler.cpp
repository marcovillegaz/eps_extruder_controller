#include "DisplayHandler.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Why this are defining here?
// LCD Setup (Adjust address if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupDisplay()
{
    lcd.init();
    lcd.backlight();

    // Display initialization message for debugging
    Serial.println("Display initialized");

    // Display startup message
    lcd.setCursor(0, 0);
    lcd.print("HAZELADD");
    lcd.setCursor(0, 1);
    lcd.print("EPS EXTRUDER v1.0");
    delay(5000);
}

// Set mode inteface
void set_mode()
{
    lcd.clear();

    if (currentOption == 0) // T1
    {
        lcd.setCursor(0, 0);
        lcd.print("Set T1:");
        lcd.setCursor(5, 1);
        lcd.print(set_T1);
    }
    else // T2
    {
        lcd.setCursor(0, 0);
        lcd.print("Set T2:");
        lcd.setCursor(5, 1);
        lcd.print(set_T2);
    }
}

// Update display. This update the temperature values and the position of the cursor
void updateDisplay()
{
    lcd.clear();

    // First row - T1
    lcd.setCursor(0, 0);
    lcd.print(currentOption == 0 ? ">T1:" : " T1:");
    lcd.setCursor(5, 0);
    lcd.print(T1, 1);
    lcd.print((char)223);
    lcd.print("C");

    // Second row - T2
    lcd.setCursor(0, 1);
    lcd.print(currentOption == 1 ? ">T2:" : " T2:");
    lcd.setCursor(5, 1);
    lcd.print(T2, 1);
    lcd.print((char)223);
    lcd.print("C");
}