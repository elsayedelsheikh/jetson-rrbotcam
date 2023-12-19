/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#ifdef L298_SHEILD_MOTOR_DRIVER
#include <AFMotor.h>

#define LFWD_MOTOR 1  // M1
#define RFWD_MOTOR 4  // M4
#define LBWD_MOTOR 2  // M2
#define RBWD_MOTOR 3  // M3

int motorMaxPWM = 100;
int motorMinPWM = 50;

AF_DCMotor m_lf(LFWD_MOTOR);
AF_DCMotor m_lb(LBWD_MOTOR);
AF_DCMotor m_rf(RFWD_MOTOR);
AF_DCMotor m_rb(RBWD_MOTOR);

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);

#endif  // L298_SHEILD_MOTOR_DRIVER
#endif  // MOTOR_DRIVER_H