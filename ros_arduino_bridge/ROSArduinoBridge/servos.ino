#ifdef USE_SERVOS

void initServos() {
  panServo.attach(panServoPin);
  tilServo.attach(tilServoPin);

  setServosAngles(90, 60);
}

void setServosAngles(int pan_angle, int tilt_angle) {
  if (pan_angle > panMaxLim) pan_angle = panMaxLim;
  if (pan_angle < panMinLim) pan_angle = panMinLim;
  panServo.write(pan_angle);

  if (tilt_angle > tiltMaxLim) tilt_angle = tiltMaxLim;
  if (tilt_angle < tiltMinLim) tilt_angle = tiltMinLim;
  tilServo.write(tilt_angle);
}

#endif