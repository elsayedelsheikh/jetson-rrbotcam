#ifdef USE_SERVOS

void initServos() {
  panServo.attach(panServoPin);
  tilServo.attach(tilServoPin);

  setServosAngles(90, 60);
}

void setServosAngles(int pan_angle, int tilt_angle) {
  panServo.write(pan_angle);

  if (tilt_angle > tiltMaxLim) tilt_angle = tiltMaxLim;
  if (tilt_angle < tiltMinLim) tilt_angle = tiltMinLim;
  tilServo.write(tilt_angle);
}

#endif