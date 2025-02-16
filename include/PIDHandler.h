#ifndef PIDHANDLER_H
#define PIDHANDLER_H

#include <PID_v1.h>

// Function prototypes
void setupPID();
void updatePID();
void setPIDInput(double T1, double T2);
double getPIDOutputT1();
double getPIDOutputT2();

extern PID pidT1;
extern PID pidT2;
extern double set_T1;
extern double set_T2;
extern double inputT1;
extern double inputT2;
extern double outputT1;
extern double outputT2;

#endif
