#include "LineTraceAction.h"

LineTraceAction::LineTraceAction()
{
}
LineTraceAction::~LineTraceAction()
{
}

/**
* ライントレース走行を開始する
*/
void LineTraceAction::start()
{
	/* 輝度値を取得 */
	//brightness = mEV3ColorSensor->getBrightness();
	brightness = mEV3ColorSensor->getColorBrightness();
	changeSpeed = speed;
	changeKp = kp;
	changeKi = ki;
	changeKd = kd;
	target = 30;
	
	/* PIDで旋回量を計算する */
	deviation = target - brightness;
	integral = deviation + integral * 0.5;
	turn = changeKp * deviation + changeKi * integral + changeKd * (deviation - prev_deviation);
	prev = prev_deviation;
	prev_deviation = deviation;

	//BluetoothLogger::dataLogger((uint8_t)speed, (uint8_t)turn, 0, (uint16_t)(kp*deviation*10),(uint16_t)(ki*integral*10),(uint16_t)(kd*(deviation-prev_deviation*10)));
	/* ライントレース走行 */
    mRearMotor->setSpeed(changeSpeed + turn, changeSpeed - turn);

}

/**
* ライントレース走行を停止する
*/
void LineTraceAction::stop()
{
	/* モータを停止 */
	mRearMotor->setSpeed(0, 0);
}

/**
* 走行パラメータを取得する
* (パラメータ更新時にのみ呼ぶこと)
*/
void LineTraceAction::updateParameter()
{
	speed = (double)mRunParameter->getLineTraceSpeed();
	prev_Speed = speed - deceleration;
	kp = mRunParameter->getKP();
	prev_Kp = kp - decelerationKp;
	ki = mRunParameter->getKI();
	prev_Ki = ki - decelerationKi;
	kd = mRunParameter->getKD();
	kd = mRunParameter->getKD();
	target = mRunParameter->getTargetBrightness();
	run_right_edge_flag = mRunParameter->getRunRighEdgeFlag();
	change_speed_flag = mRunParameter->getChangeSpeedFlag();
}


double LineTraceAction::getKP()
{
	return kp * deviation * 10;
}

double LineTraceAction::getKI()
{
	return ki * integral * 10;
}

double LineTraceAction::getKD()
{
	return kd * (deviation - prev) * 10;
}

double LineTraceAction::getSpeed()
{
	return changeSpeed;
}