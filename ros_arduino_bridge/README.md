# Arduino Motor Controller
This code turns an Arduino into a motor controller!
It provides a simple serial interface to communicate with a high-level computer (e.g. running ROS), and generates the appropriate PWM signals for a motor driver, to drive two or four dc motors (depending on the driver board) and servos.

This is a fork of the original code, with some changes. Check out `README-orig.md` for the original README. 
Currenytly I'm using this for 2x Servos to drive a camera platform.

## Functionality
The main functionality provided is to receive servo angle requests over a serial connection, and provide angle feedback.
Used commands:
- `b` - Get baud rate
- `r` - Reset servo angles and motor pwm signals to 0
- `s <panAngle> <tiltAngle>` - Set the servo angles (0-180) for each servo in degrees
- `t` - Read the current servo angles, returns `<panAngle> <tiltAngle>`

Additional commands:
- `m <PWM1> <PWM2>` - Set the raw PWM speed of each motor (-255 to 255)

## Notes
- Position limits are set for tilt servo "2nd servo" (10-90) degrees 
- Initial position is set to 90 degrees for pan servo "1st servo" and 60 degrees for tilt servo "2nd servo"
- Default baud rate 57600
- Needs carriage return (CR)
- Make sure serial is enabled (user in dialout group)
- Check out the original readme for more