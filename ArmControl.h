#ifndef ARM_CONTROL_H
#define ARM_CONTROL_H

#include "ev3api.h"
#include "Motor.h"

class ArmControl
{
  public:
	explicit ArmControl(ev3api::Motor &armMotor);
	virtual ~ArmControl();
	void setPower(int power);  //モータの出力値を設定する
	int getEncoder();		   //エンコーダ値を取得する
	void resetEncoder();	   //エンコーダ値を初期化する
	void setBrake(bool brake); //ブレーキを設定する(true:オン, false:オフ)
	bool positionCalibrate();  //アーム位置のキャリブレーション
	bool positionreset(); 
  private:
	ev3api::Motor &mArmMotor;

	int state = 0;
	int state1 = 0;
	int armEncoder[2] = {0, 0}; //エンコーダ値
};

#endif
