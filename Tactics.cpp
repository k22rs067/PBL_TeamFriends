#include "Tactics.h"

/**
* オブジェクトのポインタ変数を初期化
*/
EV3ColorSensor *Tactics::mEV3ColorSensor;

RunParameter *Tactics::mRunParameter;
CalcCurrentLocation *Tactics::mCalcCurrentLocation;

DistanceJudgement *Tactics::mDistanceJudgement;

LineTraceAction *Tactics::mLineTraceAction;
RunStraightAction *Tactics::mRunStraightAction;
RotateMachineAction *Tactics::mRotateMachineAction;
RotateAction *Tactics::mRotateAction;
ArmControl* Tactics::mArmControl;

Tactics::~Tactics()
{
}

/**
* 使用するクラスの参照を設定する
*/
void Tactics::setObject(
	EV3ColorSensor *ev3ColorSensor,
	RunParameter *runParameter,
	CalcCurrentLocation *calcCurrentLocation,
	DistanceJudgement *distanceJudgement,
	LineTraceAction *lineTraceAction,
	RunStraightAction *runStraightAction,
	RotateMachineAction *rotateMachineAction,
	RotateAction *rotateAction,
	ArmControl *armControl)
{
	mEV3ColorSensor = ev3ColorSensor;
	mRunParameter = runParameter;
	mCalcCurrentLocation = calcCurrentLocation;
	mDistanceJudgement = distanceJudgement;
	mLineTraceAction = lineTraceAction;
	mRunStraightAction = runStraightAction;
	mRotateMachineAction = rotateMachineAction;
	mRotateAction = rotateAction;
	mArmControl = armControl;
}
