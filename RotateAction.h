/**
 * 超信地旋回において、開始と終了の速度を小さくする旋回をするクラスです。
 * 旋回時のモータPWM値は30前後を想定しています。
 * 開始と終了は10度ずつ4段階で速度を変えています。
 * RANGEは、1から4が開始時、95から98が終了時を示しています。
 */

#pragma once

#include "Action.h"
#include "RotateMachineAction.h"

#define STEP 4

#define RANGE1 10
#define RANGE2 10
#define RANGE3 10
#define RANGE4 10
#define RANGE95 10
#define RANGE96 10
#define RANGE97 10
#define RANGE98 10

#define BASESPEED 3.5 // 速度の下限（これ以上遅くすると回転しなくなる）

class RotateAction : public Action
{
public:
	explicit RotateAction(RotateMachineAction *rotateMachineAction);
	virtual ~RotateAction();

	void start();
	void stop();
	void updateParameter();
	bool isFinished();

private:
    RotateMachineAction *mRotateMachineAction;

	int state = 0;
	bool flag = false;
	int targetAngle = 0;
    int power = 0;
    int direction = 0;   // 回転方向：時計回り+1、反時計回り-1
	int remainAngle = 0; // 残り回転角度（減速分を除く）
	double stepSpeed = 0;
	double currentSpeed = 0;
	double stateSpeed = 0;
	double diffSpeed = 0;
};
