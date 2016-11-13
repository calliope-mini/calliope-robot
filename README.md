# Calliope mini Robot

See how the motor functions work and remote control a robot.

## Robot & Controller
The code has two parts

1. Robot code `CalliopeRobot.cpp`
2. Robot controller code `CalliopeRobotController.cpp`

You need two Calliope mini and program one of the two codes into each one. To compile each of the two programs,
comment out one or the other in `CalliopeRobot.h`. Build and the copy to the Device.

### Connections

Connect the two motors:

* Left Motor A to MOTOR2 and GND
* Right Motor B to MOTOR1 and GND

If you need extra power, connect a battery (+)  to VM and (-) to GND.
Connect a battery to the Calliope mini battery connector or via a USB power block.

## Controlling the Robot

1. Power on the robot
2. Power on the controller

- Hold the controller horizontally and the robot will drive slowly forward.
- Tilt the controller forward or backward to go faster or slower.
- Tilt left or right to go left or right.

The robots display will show a `<` if turning left, a `>` if turning right, and a `^` driving forward.
 
## LICENSE
 
(c) 2016 Calliope gGmbH

Author: Matthias L. Jugel ([@thinkberg](https://github.com/thinkberg))

Licensed under the Apache Software License 2.0, see LICENSE.
 

 

