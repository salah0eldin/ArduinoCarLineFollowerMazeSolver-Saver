#include <Arduino.h>
#include "HBridgeMotors.h"

int runDur = 1, stopDur = 0;
bool running = 0;
unsigned long x = 0;

void HBridgeMotors::initIOMotor() {
  pinMode(INL1, OUTPUT);
  pinMode(INL2, OUTPUT);
  pinMode(INR1, OUTPUT);
  pinMode(INR2, OUTPUT);
  pinMode(ENL, OUTPUT);
  pinMode(ENR, OUTPUT);
}

void HBridgeMotors::setDirs(bool dirL, bool dirR) {
  digitalWrite(INL1, dirL);
  digitalWrite(INL2, !dirL);
  digitalWrite(INR1, dirR);
  digitalWrite(INR2, !dirR);
}

void HBridgeMotors::setDurs(int x, int y) {
  runDur = x;
  stopDur = y;
}

void HBridgeMotors::runConstSpeeds(int speedL, int speedR) {
  analogWrite(ENL, speedL);
  analogWrite(ENR, speedR);
}

void HBridgeMotors::runPWMSpeeds(int speedL, int speedR) {
  if (!running && millis() - x >= stopDur) {
    running = 1;
    x = millis();
    runConstSpeeds(speedL, speedR);
  } else if (running && millis() - x >= runDur) {
    running = 0;
    x = millis();
    runConstSpeeds(0, 0);
  }
}
