/*
  simpleMovements.ino

  This  sketch simpleMovements shows how they move each servo motor of Braccio

  Created on 18 Nov 2015
  by Andrea Martino

  This example is in the public domain.
*/

#include <Braccio.h>
#include <Servo.h>

#define joyX A0
#define joyY A1

int button = 2;
int buttonState = 0;
int buttonState1 = 0;
bool grab = false;

int servoPosition[6] = {0, 0, 0, 0, 0, 0};

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {

  pinMode(7, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);

  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Braccio.begin();
  Serial.begin(9600);
}

void loop() {
  /*
    Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
    M1=base degrees. Allowed values from 0 to 180 degrees
    M2=shoulder degrees. Allowed values from 15 to 165 degrees
    M3=elbow degrees. Allowed values from 0 to 180 degrees
    M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
    M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
    M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */

  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);

  if (xValue > 700) {
    servoPosition[0] ++;
  } else if (xValue < 400) {
    servoPosition[0]--;
  }

  if (yValue > 700) {
    servoPosition[1] ++;
    servoPosition[2] ++;
    servoPosition[3] --;

  } else if (yValue < 400) {
    servoPosition[1] --;
    servoPosition[2] --;
    servoPosition[3] ++;
  }

  if (digitalRead(button) == LOW) {
    grab = !grab;
  }

  if (grab) {
    servoPosition[5] = 73;
  } else {
    servoPosition[5] = 10;
  }

  servoPosition[0] = constrain(servoPosition[0], 0, 180);
  servoPosition[1] = constrain(servoPosition[1], 15, 165);
  servoPosition[2] = constrain(servoPosition[2], 0, 180);
  servoPosition[3] = constrain(servoPosition[3], 0, 180);
  servoPosition[4] = constrain(servoPosition[4], 0, 180);
  servoPosition[5] = constrain(servoPosition[5], 10, 73);

  Braccio.ServoMovement(20, servoPosition[0],  servoPosition[1], servoPosition[2], servoPosition[3], servoPosition[4], servoPosition[5]);
  delay(30);
}
