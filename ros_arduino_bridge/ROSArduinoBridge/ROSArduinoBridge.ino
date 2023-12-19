/*********************************************************************
 *  ROSArduinoBridge

    A set of simple serial commands to control a differential drive
    robot and receive back sensor and odometry data. Default
    configuration assumes use of an Arduino Mega + Pololu motor
    controller shield + Robogaia Mega Encoder shield.  Edit the
    readEncoder() and setMotorSpeed() wrapper functions if using
    different motor controller or encoder method.

    Created for the Pi Robot Project: http://www.pirobot.org
    and the Home Brew Robotics Club (HBRC): http://hbrobotics.org

    Authors: Patrick Goebel, James Nugen

    Inspired and modeled after the ArbotiX driver by Michael Ferguson

    Software License Agreement (BSD License)

    Copyright (c) 2012, Patrick Goebel.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above
       copyright notice, this list of conditions and the following
       disclaimer in the documentation and/or other materials provided
       with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
#define USE_BASE
#define USE_SERVOS

#ifdef USE_BASE
#define L298_SHEILD_MOTOR_DRIVER
#include "motor_driver.h"
#endif

#ifdef USE_SERVOS
#include "servos.h"
#endif

/* Include definition of serial commands */
#include "commands.h"

/* Serial port baud rate */
#define BAUDRATE 57600

/* ==================== Commands ==================== */
/* Variable initialization */
// A pair of varibles to help parse serial commands (thanks Fergs)
int arg = 0;
int index = 0;

// Variable to hold an input character
char chr;

// Variable to hold the current single-character command
char cmd;

// Character arrays to hold the first and second arguments
char argv1[16];
char argv2[16];

// The arguments converted to integers
long arg1;
long arg2;

/* Clear the current command parameters */
void resetCommand() {
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  arg1 = 0;
  arg2 = 0;
  arg = 0;
  index = 0;
}

/* Run a command.  Commands are defined in commands.h */
int runCommand() {
  int i = 0;
  char *p = argv1;
  char *str;
  arg1 = atoi(argv1);
  arg2 = atoi(argv2);

  switch (cmd) {
    case GET_BAUDRATE:
      Serial.println(BAUDRATE);
      break;

    case RESET:
#ifdef USE_BASE
      initMotorController();
#endif
#ifdef USE_SERVOS
      initServos();
#endif
      break;

#ifdef USE_SERVOS
    case SERVO_WRITE:
      setServosAngles(arg1, arg2);
      Serial.println("OK");
      break;
    case SERVO_READ:
      Serial.print(panServo.read());
      Serial.print(" ");
      Serial.println(tilServo.read());
      break;
#endif

#ifdef USE_BASE
    case MOTOR_SPEEDS:
      setMotorSpeeds(arg1, arg2);
      Serial.println("OK");
      break;

#endif
    default:
      Serial.println("Invalid Command");
      break;
  }
}

/* ==================== Setup ==================== */
void setup() {
  Serial.begin(BAUDRATE);
#ifdef USE_BASE
  initMotorController();
#endif

#ifdef USE_SERVOS
  initServos();
#endif
}

/* ==================== Loop ==================== */
void loop() {
  while (Serial.available() > 0) {
    // Read the next character
    chr = Serial.read();

    // Terminate a command with a CR "carriage"
    if (chr == 13) {
      if (arg == 1)
        argv1[index] = NULL;
      else if (arg == 2)
        argv2[index] = NULL;
      runCommand();
      resetCommand();
    }
    // Use spaces to delimit parts of the command
    else if (chr == ' ') {
      // Step through the arguments
      if (arg == 0)
        arg = 1;
      else if (arg == 1) {
        argv1[index] = NULL;
        arg = 2;
        index = 0;
      }
      continue;
    } else {
      if (arg == 0) {
        // The first arg is the single-letter command
        cmd = chr;
      } else if (arg == 1) {
        // Subsequent arguments can be more than one character
        argv1[index] = chr;
        index++;
      } else if (arg == 2) {
        argv2[index] = chr;
        index++;
      }
    }
  }
}