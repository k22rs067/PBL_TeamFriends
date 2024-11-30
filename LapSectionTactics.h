#ifndef SECTION_CONTROL_TACTICS_H
#define SECTION_CONTROL_TACTICS_H
#include "Tactics.h"
#include "RearMotor.h"

class LapSectionTactics : public Tactics
{
public:
  explicit LapSectionTactics();
  virtual ~LapSectionTactics();

  void execute(); //戦術を実行する
  bool isFinished();

private:
  /* パラメータ指定用の添字 */
  double target = 30;
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

  double section0[4] = {55, 0.02, 0, 1};    //スタート 
  double section1[4] = {48, 0.2, 0, 4};  //カーブ1
  double section2[4] = {55, 0.02, 0, 1};  //ストレート
  double section3[4] = {38, 0.6, 0, 5};  //カーブ2
  double section4[4] = {52, 0.2, 0, 5};  //ゴール
};


#endif