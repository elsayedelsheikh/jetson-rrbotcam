#ifndef SERVOS_H
#define SERVOS_H

#ifdef USE_SERVOS
#include <Servo.h>

#define panServoPin 10  // Servo #1
#define tilServoPin 9  // Servo #2

int tiltMinLim = 10;
int tiltMaxLim = 110;

int panMinLim = 0;
int panMaxLim = 180;

Servo panServo;
Servo tilServo;

void initServos();
void setServosAngles(int pan_angle, int tilt_angle);

#endif  // USE_SERVOS
#endif  // SERVOS_H