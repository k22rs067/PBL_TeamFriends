#include "FreeAreaTactics.h"
//#include "BluetoothLogger.h"
// #include <ctime>
#include <stdio.h>

#define CALIB_FONT_HEIGHT (16 /*TODO: magic number*/)


FreeAreaTactics::FreeAreaTactics()
{
	state = 0; //<-スタート位置から
}

FreeAreaTactics::~FreeAreaTactics()
{
}

/**
* 区間制御戦術を実行する
*/
void FreeAreaTactics::execute()
{

}

void FreeAreaTactics::stop()
{
    mLineTraceAction->stop();
}

void FreeAreaTactics::LineTrace(int color)
{
    switch(state_line){
        case 0:
            //ライントレース初期設定
            mCalcCurrentLocation->setAngle(0);
            mCalcCurrentLocation->setPointX(0);
            mCalcCurrentLocation->setPointY(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(45);
            mDistanceJudgement->start();

            mRunParameter->setLineTraceSpeed(20);
            mRunParameter->setKP(section4[KP]);
            mRunParameter->setKI(section4[KI]);
            mRunParameter->setKD(section4[KD]);
            mLineTraceAction->updateParameter();
            state_line ++;

        case 1:
            mLineTraceAction->start();
            if(color == 0)////gEV3ColorSensor->isColor_BLUE()//mDistanceJudgement->isDistanceOut()
            {
                state_line = 2;
            }else if (color == 1)
            {
                state_line = 3;
            }else if (color == 2)
            {
                state_line = 4;
            }else 
            {
                state_line = 5;
            }
        break;

        case 2:
            if(mEV3ColorSensor->isColor_BLUE())//青検知
            {
                state_line = 10;
            }else
            {
                state_line = 1;
            }
        break;

        case 3:
            if(mEV3ColorSensor->isColor_RED())//赤検知
            {
                state_line = 10;
            }else
            {
                state_line = 1;
            }
        break;

        case 4:
            if(mEV3ColorSensor->isColor_GREEN())//緑検知
            {
                state_line = 10;
            }else
            {
                state_line = 1;
            }
        break;

        case 5:
            if(mEV3ColorSensor->isColor_YELLOW())//黄検知
            {
                state_line = 10;
            }else
            {
                state_line = 1;
            }
        break;

        case 10:
            mLineTraceAction->stop();
            setFlag(true);
            state_line = 0;
        break;
    }
}


void FreeAreaTactics::ArmControl()
{
    switch(state_arm){
        case 0:
            mArmControl->setPower(5);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
                //mArmControl->resetEncoder();    //エンコーダ値をリセット
                state_arm = 10;
            }
        break;

        case 10:
            mArmControl->setPower(-5);
            if (mArmControl->getEncoder() <= 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state_arm = 20;
            }
        break;

        case 20:
            setFlag(true);
            state_arm = 0;
        break;
    }
}

void FreeAreaTactics::Turn_Right()
{
    switch(state_right){
        case 0:
            //旋回初期設定
            mCalcCurrentLocation->setAngle(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(rotateDistance);
            mDistanceJudgement->start();
            state_right = 10;
        break;

        case 10:
            mRunStraightAction->straight(20,0);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_right = 0;
            }
        break;
    }
}

void FreeAreaTactics::Turn_Left()
{
    switch(state_left){
        case 0:
            //旋回初期設定
            mCalcCurrentLocation->setAngle(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(10);//5
            mDistanceJudgement->start();

            state_left = 20;
        break;

        case 10:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
		        state_left=20;
            }
        break;

        case 20:
            mRunStraightAction->straight(0,30);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_left = 0;
            }
        break;
    }
}

void FreeAreaTactics::Uturn()
{
    switch(state_Uturn){
        case 0:
            //旋回初期設定
            mCalcCurrentLocation->setAngle(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(rotateDistance);
            mDistanceJudgement->start();

            state_Uturn = 10;
        break;

        case 10:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(180);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
                state_Uturn = 20;
            }
        break;

        case 20:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_Uturn = 0;
            }
        break;
    }
}

void FreeAreaTactics::CircleStraight()
{
    switch(state_straight){
        case 0:
            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(straightDistance);
            mDistanceJudgement->start();
            state_straight = 10;
        break;

        case 10:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_straight = 0;
            }
        break;

        default:
        break;
    }
}

void FreeAreaTactics::setFlag(bool setflag)
{
    flag = setflag;
}

bool FreeAreaTactics::isFinished()
{
	return flag;
}
