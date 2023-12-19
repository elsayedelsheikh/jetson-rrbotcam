#ifndef SERVOS_H
#define SERVOS_H

#ifdef USE_SERVOS
#include <Servo.h>

#define tilServoPin 10  // Servo #1
#define panServoPin 9   // Servo #2

int tiltMaxLim = 90;
int tiltMinLim = 10;

Servo panServo;
Servo tilServo;

void initServos();
void setServosAngles(int pan_angle, int tilt_angle);

#endif  // USE_SERVOS
#endif  // SERVOS_H