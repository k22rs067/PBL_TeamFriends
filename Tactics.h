#ifndef TACTICS_H
#define TACTICS_H

#include "EV3ColorSensor.h"
#include "RunParameter.h"
#include "CalcCurrentLocation.h"
#include "DistanceJudgement.h"
#include "LineTraceAction.h"
#include "RunStraightAction.h"
#include "RotateMachineAction.h"
#include "RotateAction.h"
#include "ArmControl.h"

class Tactics
{
  public:
	virtual ~Tactics();

	virtual void execute() = 0; //戦術を実行する

	/* 使用するクラスのオブジェクトへの参照を設定 */
	static void setObject(
		EV3ColorSensor *ev3ColorSensor,
		RunParameter *runParameter,
		CalcCurrentLocation *calcCurrentLocation,
		DistanceJudgement *distanceJudgement,
		LineTraceAction *lineTraceAction,
		RunStraightAction *runStraightAction,
		RotateMachineAction *rotateMachineAction,
		RotateAction *rotateAction,
		ArmControl *armControl);

  protected:
	/* 使用するクラスのオブジェクト */
	static EV3ColorSensor *mEV3ColorSensor;
	static RunParameter *mRunParameter;
	static CalcCurrentLocation *mCalcCurrentLocation;

	static DistanceJudgement *mDistanceJudgement;

	static LineTraceAction *mLineTraceAction;
	static RunStraightAction *mRunStraightAction;
	static RotateMachineAction *mRotateMachineAction;
	static RotateAction *mRotateAction;
	static ArmControl *mArmControl;

	//状態
	int state;
};

#endif
