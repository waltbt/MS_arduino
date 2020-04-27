#include <Servo.h>

Servo wrist_yaw;
Servo wrist_pitch;
Servo wrist_roll;

#define YAW 3
#define PITCH 4
#define ROLL 5

void setup() {
  // put your setup code here, to run once:
  wrist_yaw.attach(3); //Third joint
  wrist_yaw.writeMicroseconds(1470);
 wrist_pitch.attach(15); //Second joint
  wrist_pitch.writeMicroseconds(1450);
  wrist_roll.attach(1); //First joint
  wrist_roll.writeMicroseconds(1570);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(1);
}
