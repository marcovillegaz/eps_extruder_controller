#include <Arduino.h>
#include "PIDHandler.h"

/*
Study PID.
error = setpoint - input;
P = Kp * error;
I = Ki * integral_of_error;
D = Kd * derivative_of_error;
output = P + I + D;
*/

// Define PID parameters
double Kp = 2.0, Ki = 5.0, Kd = 1.0; // Example PID constants, adjust as needed

// Setpoint temperatures (setT1 and SetT2 are defined in EncoderHandler.cpp)
// double setpointT1 = 25.0; // Target temperature for T1
// double setpointT2 = 25.0; // Target temperature for T2

// Input and output variables for PID control
double inputT1 = 0.0, inputT2 = 0.0;
double outputT1 = 0.0, outputT2 = 0.0;

// Initialize PID controllers. Why this is here? setT1 are fixed by the user, only should be
// set using the encoder.

PID pidT1(&inputT1, &outputT1, &set_T1, Kp, Ki, Kd, DIRECT);
PID pidT2(&inputT2, &outputT2, &set_T2, Kp, Ki, Kd, DIRECT);

// Function to initialize PID controllers
void setupPID()
{
    // Set PID output limits (optional, depending on your control logic)
    pidT1.SetOutputLimits(0, 100); // Example: 0-100 (scale for SSR control)
    pidT2.SetOutputLimits(0, 100); // Example: 0-100 (scale for SSR control)

    pidT1.SetMode(AUTOMATIC);
    pidT2.SetMode(AUTOMATIC);

    // Serial print PID parameters for debugging
    Serial.println("PID Controllers Initialized");
    Serial.print("Kp: ");
    Serial.println(Kp);
    Serial.print("Ki: ");
    Serial.println(Ki);
    Serial.print("Kd: ");
    Serial.println(Kd);
    Serial.println("---------------------------");
}

// Function to set input values for PID controllers
void setPIDInput(double T1, double T2)
{
    inputT1 = T1;
    inputT2 = T2;
}

// Compute output values for PID controllers
void updatePID()
{
    pidT1.Compute();
    pidT2.Compute();

    // Print the control output to the serial monitor (for debugging)
    Serial.print("PID T1 Output: ");
    Serial.println(outputT1);
    Serial.print("PID T2 Output: ");
    Serial.println(outputT2);
    Serial.println("---------------------------");
}

double getPIDOutputT1()
{
    return outputT1;
}

double getPIDOutputT2()
{
    return outputT2;
}
