#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *myStepper1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMS.getStepper(200, 2);

bool isRunning = 0;
//char mySteps;
int mode = -1;


void forwardstep1() {
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {
  myStepper1->onestep(BACKWARD, DOUBLE);
}

void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}

AccelStepper Astepper1(forwardstep1, backwardstep1);
AccelStepper Astepper2(forwardstep2, backwardstep2);

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);

}

void loop() {
  if (Serial.available() > 0) {
    char mySteps = Serial.read();
    Serial.println(mySteps);

    switch (mySteps) {
      case 'w':
        mode = 1;
        break;
      case 's':
        mode = 2;
        break;
      case 'a':
        mode = 3;
        break;
      case 'd':
        mode = 4;
        break;
      default:
        //nothing
        break;
    }
  }
  if (!isRunning) {
    switch (mode) {
      case 1:

        up();
        break;
      case 2:
        down();
        break;
      case 3:
        left();
        break;
      case 4:
        right();
        break;
      default:
        //nothing
        break;
    }
  }

  if (!Astepper1.run() && !Astepper2.run() && isRunning) {
    Serial.println("stepping done!");
    isRunning = false;
  }

  Astepper1.run();
  Astepper2.run();
}

void up() {
  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);
  Astepper1.move(100);
  Astepper2.move(100);
  isRunning = true;
}


void down() {
  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);
  Astepper1.move(-100);
  Astepper2.move(-100);
  isRunning = true;
}

void left() {
  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);
  Astepper1.move(100);
  Astepper2.move(-100);
  isRunning = true;
}

void right() {
  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);
  Astepper1.move(-100);
  Astepper2.move(100);
  isRunning = true;
}


