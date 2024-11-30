#include "Action.h"

/**
* オブジェクトのポインタ変数を初期化
*/
RearMotor *Action::mRearMotor;
EV3ColorSensor *Action::mEV3ColorSensor;
Action *Action::mLineTraceAction;
RunParameter *Action::mRunParameter;
ArmControl *Action::mArmControl;
CalcCurrentLocation *Action::mCalcCurrentLocation;
Action *Action::mRunStraightAction;


Action::~Action()
{
}

/**
* 使用するクラスの参照を設定する
*/
void Action::setObject(
	RunParameter *runParameter,
	RearMotor *rearMotor,
	ArmControl *armControl,
	EV3ColorSensor *ev3ColorSensor,
	// EV3SonarSensor *ev3SonarSensor,
	// EV3GyroSensor *ev3GyroSensor,
	CalcCurrentLocation *calcCurrentLocation,
	Action *lineTraceAction,
	Action *runStraightAction)
	//Action *curvatureRunAction)
{
	mRunParameter = runParameter;
	mRearMotor = rearMotor;
	mArmControl = armControl;
	mEV3ColorSensor = ev3ColorSensor;
	//mEV3SonarSensor = ev3SonarSensor;
	//mEV3GyroSensor = ev3GyroSensor;
	mCalcCurrentLocation = calcCurrentLocation;
	mLineTraceAction = lineTraceAction;
	mRunStraightAction = runStraightAction;
	//mCurvatureRunAction = curvatureRunAction;
}
