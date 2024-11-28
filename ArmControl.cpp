#include "ArmControl.h"

ArmControl::ArmControl(ev3api::Motor& armMotor)
: mArmMotor(armMotor)
{
}

ArmControl::~ArmControl()
{
}

/**
* モータの出力値を指定する
* @param power 出力値
*/
void ArmControl::setPower(int power){
	// 出力値を100から-100の間に修正
	if(power > 100){
		power = 100;
	}
	else if(power < -100){
		power = -100;
	}
	// 出力値を設定
	mArmMotor.setPWM(power);
}

/**
* エンコーダ値を取得する
* @return エンコーダ値
*/
int ArmControl::getEncoder(){
	return mArmMotor.getCount();
}
/**
* エンコーダ値を初期化する
*/
void ArmControl::resetEncoder(){
	mArmMotor.reset();
}
/**
* ブレーキを設定する
* @param ブレーキのオンオフ
*
*/
void ArmControl::setBrake(bool brake){
	mArmMotor.setBrake(brake);
}

