#include "RotateAction.h"
//#include "BluetoothLogger.h"

RotateAction::RotateAction(RotateMachineAction *rotateMachineAction)
    : mRotateMachineAction(rotateMachineAction)
{
}

RotateAction::~RotateAction()
{
}

void RotateAction::start()
{
	switch (state)
	{
	case 0:
		updateParameter();
        direction = (targetAngle >= 0) ? 1 : -1; // 回転方向
        remainAngle = targetAngle;               // 回転に残っている角度
        stepSpeed = power / 4.0;                 // 段階ごとに変化するスピードの範囲
        currentSpeed = 0;                        // 初速0
        stateSpeed = 0;
        state++;
		break;
	case 1: // 1つ目の設定
        if (std::abs(remainAngle) < RANGE1 + RANGE98)       // 目標の回転角度がRANGE1加速とRNAGE98減速を合わせた角度より小さいとき
        {
            mRunParameter->setRotateAngle(remainAngle);     // 回転角度
            state = 99;
        }
        else {
    		mRunParameter->setRotateAngle(direction * RANGE1);// 回転角度
            remainAngle -= direction * (RANGE1 + RANGE98);
            state++;
            //BluetoothLogger::println(stepSpeed);
            //BluetoothLogger::println(state);
        }
		mRunParameter->setRotateSpeed(currentSpeed);                  // 回転スピード
		mRotateMachineAction->updateParameter();            // 回転走行パラメータを更新
		break;
    case 2:
        // 1つ目の設定からの加速
        if (currentSpeed < stateSpeed + stepSpeed)
        {
            currentSpeed += 0.1;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();                      // 回転する
        if (mRotateMachineAction->isFinished())             // 回転完了
        {
            // 2つ目の設定
            stateSpeed = currentSpeed;
            if (std::abs(remainAngle) < RANGE2 + RANGE97)  // すでに回転したRANGE度と減速RANGE度を除き、残りRANGE*2度未満
            {
                mRunParameter->setRotateAngle(remainAngle);
                state = 98;
            }
            else
            {
                mRunParameter->setRotateAngle(direction * RANGE2);
                remainAngle -= direction * (RANGE2 + RANGE97);
                state++;
                //BluetoothLogger::println(state);
            }
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
        }
        break;
    case 3:
        // 2つ目の設定からの加速
        if (currentSpeed < stateSpeed + stepSpeed)
        {
            currentSpeed += 0.1;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();
        if (mRotateMachineAction->isFinished())
        {
            // 3つ目の設定
            stateSpeed = currentSpeed;
            if (std::abs(remainAngle) < RANGE3 + RANGE96)
            {
                mRunParameter->setRotateAngle(remainAngle);
                state = 97;
            }
            else
            {
                mRunParameter->setRotateAngle(direction * RANGE3);
                remainAngle -= direction * (RANGE3 + RANGE96);
                state++;
                //BluetoothLogger::println(state);
            }
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
        }
        break;
    case 4:
        // 3つ目の設定からの加速
        if (currentSpeed < stateSpeed + stepSpeed)
        {
            currentSpeed += 0.2;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();
        if (mRotateMachineAction->isFinished())
        {
            // 4つ目の設定
            stateSpeed = currentSpeed;
            if (std::abs(remainAngle) < RANGE4 + RANGE95)
            {
                mRunParameter->setRotateAngle(remainAngle);
                state = 96;
            }
            else
            {
                mRunParameter->setRotateAngle(direction * RANGE3);
                remainAngle -= direction * (RANGE4 + RANGE95);
                state = 50;
                //BluetoothLogger::println(state);
            }
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
        }
        break;
    case 50:
        // 4つ目の設定からの加速
        if (currentSpeed < stateSpeed + stepSpeed)
        {
            currentSpeed += 0.2;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();
        //BluetoothLogger::println(currentSpeed);
        if (mRotateMachineAction->isFinished())
        {
            // 余った角度の回転設定
            stateSpeed = currentSpeed;
            mRunParameter->setRotateAngle(remainAngle);
            remainAngle = 0;
            state = 95;
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
            //BluetoothLogger::println(state);
        }
        break;
    case 95: // 余った角度は一定速度で走行する
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->start();
        if (mRotateMachineAction->isFinished())
        {
            // 最後から4つ目の設定
            mRunParameter->setRotateAngle(direction * RANGE95);
            state++;
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
            //BluetoothLogger::println(state);
        }
        break;
    case 96:
        // 最後から4つ目の設定からの減速
        if (currentSpeed > stateSpeed - stepSpeed && currentSpeed > BASESPEED)
        {
            currentSpeed -= 0.2;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();
        if (mRotateMachineAction->isFinished())
        {
            // 最後から3つ目の設定
            stateSpeed = currentSpeed;
            mRunParameter->setRotateAngle(direction * RANGE96);
            state++;
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
            //BluetoothLogger::println(state);
        }
        break;
    case 97:
        // 最後から3つ目の設定からの減速
        if (currentSpeed > stateSpeed - stepSpeed && currentSpeed > BASESPEED)
        {
            currentSpeed -= 0.2;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();
        if (mRotateMachineAction->isFinished())
        {
            // 最後から2つ目の設定
            stateSpeed = currentSpeed;
            mRunParameter->setRotateAngle(direction * RANGE97);
            state++;
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
            //BluetoothLogger::println(state);
        }
        break;
    case 98:
        // 最後から2つ目の設定からの減速
        if (currentSpeed > stateSpeed - stepSpeed && currentSpeed > BASESPEED)
        {
            currentSpeed -= 0.2;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();
        if (mRotateMachineAction->isFinished())
        {
            // 最後から1つ目の設定
            mRunParameter->setRotateAngle(direction * RANGE98);
            state++;
            mRunParameter->setRotateSpeed(currentSpeed);
            mRotateMachineAction->updateParameter();
            //BluetoothLogger::println(state);
        }
        break;
    case 99:
        // 最後から1つ目の設定からの減速
        if (currentSpeed > BASESPEED)
        {
            currentSpeed -= 0.2;
        }
        //BluetoothLogger::println(currentSpeed);
        mRotateMachineAction->updateSpeed(currentSpeed);
        mRotateMachineAction->start();
        if (mRotateMachineAction->isFinished()
            // 目標角度に補正を加えた角度まで回転する
            || (direction == 1  && targetAngle + 1 <= mCalcCurrentLocation->getFinalAngle())  // 1度分補正
            || (direction == -1 && mCalcCurrentLocation->getFinalAngle() <= targetAngle - 3)) // 2.5度分補正
        {
            mRotateMachineAction->stop();
            flag = true;
        }
        break;
    }
}

void RotateAction::stop()
{
	mRotateMachineAction->stop();
	state = 0;
	flag = false;
}

void RotateAction::updateParameter()
{
	targetAngle = mRunParameter->getRotateAngle();
	power = mRunParameter->getRotateSpeed();
	state = 0;
	flag = false;
}

bool RotateAction::isFinished()
{
	return flag;
}
