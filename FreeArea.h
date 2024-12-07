#ifndef FREE_AREA_H
#define FREE_AREA_H

#include "Tactics.h"
#include "FreeAreaTactics.h"
#include "RearMotor.h"

class FreeArea
{
public:
  explicit FreeArea(FreeAreaTactics *FreeAreaTactics);
  virtual ~FreeArea();

  void execute(); //戦術を実行する
  bool isFinished();

private:
FreeAreaTactics *mFreeAreaTactics;

  const int BLUE = 0;
  const int RED = 1;
  const int GREEN = 2;
  const int YELLOW = 3;

  const int PRESENT = 0;
  const int OBSTACLE = 1;

  /* パラメータ指定用の添字 */
  double target = 38.5;
  double rotateDistance = 7;     //旋回前後のstraightの距離
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

};


#endif