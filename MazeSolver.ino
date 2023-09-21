#include "HBridgeMotors.h"

#define inl1 2
#define inl2 3
#define enl 6
#define inr1 4
#define inr2 5
#define enr 9

#define NSpeedL 124  // Normal Speed Left
#define NSpeedR 124  // Normal Speed Rigth
#define FSpeedL 150  // Faster Speed Left
#define FSpeedR 150  // Faster Speed Right

#define irC A0   // Center IR
#define irCR A1  // Center Right IR
#define irL A2   // Left IR
#define irR A3   // Right IR

#define isBlack(IR) digitalRead(IR)

HBridgeMotors motors(inl1, inl2, enl, inr1, inr2, enr);

void makeDecision();

void setup() {
  motors.initIOMotor();

  pinMode(irC, INPUT);
  pinMode(irCR, INPUT);
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);

  motors.setDirs(Forward, Forward);
  motors.setDurs(10, 4);
}

bool Ends = 0, TurnLS1 = 0, TurnLS2 = 0, ForwardR = 0, TurnR = 0, Reversing = 0;
unsigned long ForwardRT = 0;

void loop() {
  if (Ends) {

    motors.runConstSpeeds(0, 0);

  } else if (TurnLS1) {

    motors.runPWMSpeeds(0, NSpeedR);
    if (!isBlack(irC)) {
      TurnLS1 = 0;
      TurnLS2 = 1;
    }

  } else if (TurnLS2) {

    motors.runPWMSpeeds(0, NSpeedR);
    if (isBlack(irC))
      TurnLS2 = 0;

  } else if (ForwardR) {

    motors.runPWMSpeeds(NSpeedL, FSpeedR);
    if (millis() - ForwardRT >= 500) {
      ForwardR = 0;
      Reversing = 1;
    }

  } else if (TurnR) {

    motors.runPWMSpeeds(NSpeedL, 0);
    if (isBlack(irC) || isBlack(irL))
      TurnR = 0;

  } else if (Reversing) {

    motors.runPWMSpeeds(NSpeedL, NSpeedR);
    if (isBlack(irC) || isBlack(irL)) {
      Reversing = 0;
      motors.setDirs(Forward, Forward);
    }

  } else {

    makeDecision();
  }
}

void makeDecision() {
  if (isBlack(irC) && isBlack(irCR) && isBlack(irL) && isBlack(irR)) {

    Ends = 1;

  } else if (isBlack(irL)) {

    TurnLS1 = 1;

  } else if (isBlack(irC)) {

    motors.runPWMSpeeds(NSpeedL, NSpeedR);

  } else if (!isBlack(irC) && isBlack(irCR)) {

    motors.runPWMSpeeds(FSpeedL, NSpeedR);

  } else if (!isBlack(irC) && !isBlack(irCR)) {

    ForwardR = 1;
    ForwardRT = millis();

  } else if (isBlack(irR)) {

    TurnR = 1;

  } else {

    motors.setDirs(Backward, Forward);
    Reversing = 1;
  }
}
