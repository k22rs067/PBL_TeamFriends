#ifndef RUN_STRAIGHT_ACTION_H
#define RUN_STRAIGHT_ACTION_H

#include "ev3api.h"
#include "Action.h"

class RunStraightAction : public Action
{
  public:
	explicit RunStraightAction();
	virtual ~RunStraightAction();

	void setOffset(int power);
	void start(int targetAngle);
	void start(); //動作開始
	void setTargetAngle(double angle);
	void stop();  //動作停止
	void straight(int left,int right);
	void straight2();
	void straight3();
	void straight4();
	void straight5();
	void straight6();
	void back();
	void back2();
	void back3();
	void turnleft();
	void turnRight();
	void updateParameter(); //パラメータ更新

	void syouto();
	void fukki();
	void fukki2();
    void fukki3();
	void origin();
	void origin2();
	void origin3();
	void origin4();
	void origin5();
	void origin6();
	void origin7();
	void origin8();
	void origin9();
	void origincur();
	void accel();


  private:
	int state = 0;
	double currentAngle;	   //現在の機体の角度
	double targetAngle;		   //目標角度
	bool resetFlag = true;	 //角度再設定フラグ
	bool setAngleFlag = false; //角度指定フラグ
	int speed;				   //速度
	int offset = 3; //補正値
	
};

#endif
