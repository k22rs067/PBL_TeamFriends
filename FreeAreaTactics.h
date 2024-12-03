#ifndef FREE_AREA_TACTICS_H
#define FREE_AREA_TACTICS_H

#include "Tactics.h"
#include "RearMotor.h"

class FreeAreaTactics : public Tactics
{
public:
  explicit FreeAreaTactics();
  virtual ~FreeAreaTactics();

  void execute(); //戦術を実行する
  bool isFinished();

  void stop();
  void LineTrace(int color);
  void ArmControl();
  void Turn_Right();
  void Turn_Left();
  void Uturn();
  void CircleStraight();
  void setFlag(bool setflag);

private:
  /* パラメータ指定用の添字 */
  double target = 38.5;
  double rotateDistance = 14;     //旋回前後のstraightの距離
  double straightDistance = 15;   //旋回以外のstraightの距離
  double lineDistance = 25;       //サークル間の距離
  double armAngle = 50;
  const int SPEED = 0;
  const int KP = 1;
  const int KI = 2;
  const int KD = 3;
  double retentionAngle[2];
  bool flag = false;
  //あまり触らない
  const int offset1 = 8; //6 8
  const int offset2 = 8;
  const int angle1 = 90;
  const int angle2 = 53; //53

  double section4[4] = {12, 0.02, 0, 1};  //格子状

  int state = 0;
  int state_line = 0;
  int state_right = 0;
  int state_left = 0;
  int state_Uturn = 0;
  int state_straight = 0;
  int state_arm = 0;
};


#endif