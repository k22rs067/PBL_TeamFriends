#include "RunStraightAction.h"

RunStraightAction::RunStraightAction()
{
}
RunStraightAction::~RunStraightAction()
{
}
void RunStraightAction::setOffset(int power)
{
	offset=power;
}


void RunStraightAction::start(int targetAngle)
{
	currentAngle = mCalcCurrentLocation->getFinalAngle(); //現在の機体の角度を更新
	if (currentAngle < targetAngle - 0.5)
	{ //左方向に逸れる
		mRearMotor->setSpeed(speed + offset, speed - offset);
	}
	else if (currentAngle > targetAngle + 0.5)
	{ //右方向に逸れる
		mRearMotor->setSpeed(speed - offset, speed + offset);
	}
	else
	{
		mRearMotor->setSpeed(speed, speed);
	}
}
void RunStraightAction::start()
{ //動作開始
	switch (state)
	{
	case 0:
		updateParameter();
		targetAngle = mCalcCurrentLocation->getFinalAngle(); //角度を保持
		state++;
		break;
	case 1:
		currentAngle = mCalcCurrentLocation->getFinalAngle(); //現在の機体の角度を更新
		if (currentAngle < targetAngle - 0.5)
		{ //左方向に逸れる
			mRearMotor->setSpeed(speed + offset, speed - offset);
		}
		else if (currentAngle > targetAngle + 0.5)
		{ //右方向に逸れる
			mRearMotor->setSpeed(speed - offset, speed + offset);
		}
		else
		{
			mRearMotor->setSpeed(speed, speed);
		}
		
		break;
	}
}

void RunStraightAction::setTargetAngle(double angle)
{
	targetAngle = angle;
}

void RunStraightAction::stop()
{
	mRearMotor->setSpeed(0, 0);
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::straight(int left, int right)
{
	mRearMotor->setSpeed(left, right);
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::straight2()
{
	mRearMotor->setSpeed(16, 16);//13.5
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::straight3()
{
	mRearMotor->setSpeed(17, 16);//16.3
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::straight4()
{
	mRearMotor->setSpeed(17, 12);
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::straight5()
{
	mRearMotor->setSpeed(16.5, 17);//16.3
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::back3()
{
    mRearMotor->setSpeed(-5, -5);
    if (resetFlag)
    {
        state = 0;
    }
} 

void RunStraightAction::straight6()
{
    mRearMotor->setSpeed(8, 8);//16.3
    if (resetFlag)
    {
        state = 0;
    }
}

void RunStraightAction::back()
{
	mRearMotor->setSpeed(-15, -15);
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::back2()
{
	mRearMotor->setSpeed(0, -10);
	if (resetFlag)
	{
		state = 0;
	}
}
void RunStraightAction::turnleft()
//赤・黄・緑
{
	mRearMotor->setSpeed(-10, 30);//-10,30
	if (resetFlag)
	{
		state = 0;
	}
}
void RunStraightAction::turnRight()
//赤・黄・緑
{
	mRearMotor->setSpeed(30, -10);
	if (resetFlag)
	{
		state = 0;
	}
}

void RunStraightAction::updateParameter()
{
	speed = mRunParameter->getForwardSpeed();
	resetFlag = mRunParameter->getAngleResetFlag();
	setAngleFlag = mRunParameter->getTargetAngleFlag();
	if (setAngleFlag)
	{
		targetAngle = mRunParameter->getStraightAngle();
		mRunParameter->setTargetAngleFlag(false);
		state = 1;
	}
	else if (resetFlag)
	{
		state = 0;
	}
}
