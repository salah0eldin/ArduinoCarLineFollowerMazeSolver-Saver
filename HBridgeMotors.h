#define Forward 1
#define Backward 0

class HBridgeMotors {
private:
  byte INL1;
  byte INL2;
  byte ENL;
  byte INR1;
  byte INR2;
  byte ENR;
public:
  HBridgeMotors(byte inl1, byte inl2, byte enl, byte inr1, byte inr2, byte enr)
    : INL1(inl1), INL2(inl2), ENL(enl), INR1(inr1), INR2(inr2), ENR(enr) {}
  void initIOMotor();
  void setDirs(bool dirL, bool dirR);
  void setDurs(int runDur, int stopDur);
  void runConstSpeeds(int speedL, int speedR);
  void runPWMSpeeds(int speedL, int speedR);
};
