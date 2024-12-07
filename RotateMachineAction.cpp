#include "RotateMachineAction.h"

RotateMachineAction::RotateMachineAction()
{
}
RotateMachineAction::~RotateMachineAction()
{
}

void RotateMachineAction::start()
{
	switch (state)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state = 1;
		}
		else
		{
			state = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(power, -power-1);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-power, power+1);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}

void RotateMachineAction::start2()
{
	switch (state2)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state2 = 1;
		}
		else
		{
			state2 = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(power-5, -power);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-power+5, power);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}

void RotateMachineAction::right()
{
	switch (state3)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state3 = 1;
		}
		else
		{
			state3 = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(power, -power+7.7);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-power, power-7.7);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}

void RotateMachineAction::right2()
{
	switch (state4)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state4 = 1;
		}
		else
		{
			state4 = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(power, -power+1);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-power, power-1);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}

void RotateMachineAction::rightback()
{
	switch (state5)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state5 = 1;
		}
		else
		{
			state5 = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(power, -1);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-power, -1);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}

void RotateMachineAction::leftback()
{
	switch (state6)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state6 = 1;
		}
		else
		{
			state6 = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-1, -power);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-1, power);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}

void RotateMachineAction::Justleft()
{
	switch (state7)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state7 = 1;
		}
		else
		{
			state7 = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(power, -power);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-power, power);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}

void RotateMachineAction::Justright()
{
	switch (state8)
	{
	case 0:
		updateParameter();
		startAngle = mCalcCurrentLocation->getFinalAngle();
		angle[0] = 0;
		if (targetAngle >= 0)
		{
			state8 = 1;
		}
		else
		{
			state8 = 2;
		}
		break;
	case 1:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(power, -power);
		if (currentAngle >= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	case 2:
		angle[1] = angle[0] + mCalcCurrentLocation->getDeltaAngle();
		angle[0] = angle[1];
		currentAngle = angle[1] / M_PI * 180;

		//			currentAngle = mCalcCurrentLocation -> getFinalAngle();

		mRearMotor->setSpeed(-power, power);
		if (currentAngle <= targetAngle)
		{
			//ev3_speaker_play_tone(NOTE_C6, 200);
			flag = true;
		}
		break;
	}
}


void RotateMachineAction::stop()
{
	mRearMotor->setSpeed(0, 0);
	state = 0;
	state2 = 0;
	state3 = 0;
	state4 = 0;
	state6 = 0;
	state5 = 0;
	state7 = 0;	
	state8 = 0;	
	flag = false;
}

void RotateMachineAction::updateParameter()
{
	targetAngle = mRunParameter->getRotateAngle();
	power = mRunParameter->getRotateSpeed();
	state = 0;
	state2 = 0;
	state3 = 0;
	state4 = 0;
	state5 = 0;
	state6 = 0;	
	state7 = 0;	
	state8 = 0;	

	flag = false;
}

bool RotateMachineAction::isFinished()
{
	return flag;
}

void RotateMachineAction::updateSpeed(int speed)
{
	power = speed;
}