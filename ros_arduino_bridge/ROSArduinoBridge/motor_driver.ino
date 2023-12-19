/***************************************************************
   Motor driver definitions

   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   *************************************************************/

#ifdef USE_BASE
#ifdef L298_SHEILD_MOTOR_DRIVER
void initMotorController() {
  m_lf.run(RELEASE);
  m_rf.run(RELEASE);
  m_lb.run(RELEASE);
  m_rb.run(RELEASE);
}

void setMotorSpeed(int i, int spd) {
  unsigned char reverse = 0;

  if (spd < 0) {
    spd = -spd;
    reverse = 1;
  }

  if (spd > motorMaxPWM) spd = motorMaxPWM;
  if (spd != 0 && spd < motorMinPWM) spd = motorMinPWM;

  if (i == LEFT) {
    if (reverse == 0) {
      m_lf.run(FORWARD);
      m_lb.run(FORWARD);
      m_lf.setSpeed(spd);
      m_lb.setSpeed(spd);
    } else if (reverse == 1) {
      m_lf.run(BACKWARD);
      m_lb.run(BACKWARD);
      m_lf.setSpeed(spd);
      m_lb.setSpeed(spd);
    }
  } else if (i == RIGHT) {
    if (reverse == 0) {
      m_rf.run(FORWARD);
      m_rb.run(FORWARD);
      m_rf.setSpeed(spd);
      m_rb.setSpeed(spd);
    } else if (reverse == 1) {
      m_rf.run(BACKWARD);
      m_rb.run(BACKWARD);
      m_rf.setSpeed(spd);
      m_rb.setSpeed(spd);
    }
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}

#else
#error A motor driver must be selected!
#endif

#endif
