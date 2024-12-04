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

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(45);
            mDistanceJudgement->start();

            mRunParameter->setLineTraceSpeed(15);
            mRunParameter->setKP(section4[KP]);
            mRunParameter->setKI(section4[KI]);
            mRunParameter->setKD(section4[KD]);
            mLineTraceAction->updateParameter();
            state_line ++;
        break;

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
/*
        case 10:
            mLineTraceAction->stop();
            setFlag(true);
            state_line = 0;
        break; 
        */

        case 10:
            mLineTraceAction->stop();
            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(backDistance);
            mDistanceJudgement->start();
            state_line = 20;
        break;  

        case 20:
            mRunStraightAction->straight(-15,-15);
            if(mDistanceJudgement->isDistanceOutBack())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_line = 0;
            }
        break;
    }
}

void FreeAreaTactics::LineTrace_Jugde(int color)
{
    switch(state){
        case 0:
            //ライントレース初期設定
            mCalcCurrentLocation->setAngle(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(45);
            mDistanceJudgement->start();

            mRunParameter->setLineTraceSpeed(15);
            mRunParameter->setKP(section4[KP]);
            mRunParameter->setKI(section4[KI]);
            mRunParameter->setKD(section4[KD]);
            mLineTraceAction->updateParameter();
            state ++;

        case 1:
            mLineTraceAction->start();
            if(color == 0)////gEV3ColorSensor->isColor_BLUE()//mDistanceJudgement->isDistanceOut()
            {
                state = 2;
            }else if (color == 1)
            {
                state = 3;
            }else if (color == 2)
            {
                state = 4;
            }else 
            {
                state = 5;
            }
        break;

        case 2:
            if(mEV3ColorSensor->isColor_BLUE())//青検知
            {
                blue_count ++;
                state = 10;
            }else
            {
                state = 1;
            }
        break;

        case 3:
            if(mEV3ColorSensor->isColor_RED())//赤検知
            {
                red_count ++;
                state = 10;
            }else
            {
                state = 1;
            }
        break;

        case 4:
            if(mEV3ColorSensor->isColor_GREEN())//緑検知
            {
                green_count ++;
                state = 10;
            }else
            {
                state = 1;
            }
        break;

        case 5:
            if(mEV3ColorSensor->isColor_YELLOW())//黄検知
            {
                yellow_count ++;
                state = 10;
            }else
            {
                state = 1;
            }
        break;

        case 10:
            mLineTraceAction->stop();
            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(backDistance);
            mDistanceJudgement->start();
            state = 20;
        break;  

        case 20:
            mRunStraightAction->straight(-10,-10);
            if(mDistanceJudgement->isDistanceOutBack())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                state = 30;
            }
        break;

        case 30:
            mArmControl->setPower(5);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        //mArmControl->setPower(0);	//アーム停止
                //mArmControl->resetEncoder();    //エンコーダ値をリセット
                state = 40;
            }
        break;

        case 40:
            mArmControl->setPower(0);
            if (mEV3ColorSensor->isColor_PRESENT())
            {
                p_count = 1;
            }else if (mEV3ColorSensor->isColor_OBSTACLE())
            {
                o_count = 1;
            }
            state = 50;
        break;

        case 50:
            mArmControl->setPower(-5);
            if (mArmControl->getEncoder() <= 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state= 60;
            }
        break;

        case 60:
            setFlag(true);
            state = 0;
        break;
    }
}

/*
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
            mArmControl->setPower(0);
            if (mEV3ColorSensor->isColor_PRESENT())
            {
                p_count = 1;
            }else if (mEV3ColorSensor->isColor_OBSTACLE())
            {
                o_count = 1;
            }
            state_arm = 20;
        break;

        case 20:
            mArmControl->setPower(-5);
            if (mArmControl->getEncoder() <= 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state_arm = 30;
            }
        break;

        case 30:
            setFlag(true);
            state_arm = 0;
        break;
    }
}

void FreeAreaTactics::Straight_Back()
{
    switch (state_back)
    {
        case 0:
            //旋回初期設定
            mCalcCurrentLocation->setAngle(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(backDistance);
            mDistanceJudgement->start();
            state_back = 10;
        break;  

        case 10:
            mRunStraightAction->straight(-20,-20);
            if(mDistanceJudgement->isDistanceOutBack())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_back = 0;
            }
        break;
    }
}
*/

void FreeAreaTactics::Turn_Right()
{
    switch(state_right){
        case 0:
            mLineTraceAction->stop();
            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(-(backDistance));
            mDistanceJudgement->start();
            state_right = 10;
        break;  

        case 10:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mCalcCurrentLocation->setAngle(0);
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state_right = 20;
            }
        break;

        case 20:
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
            mLineTraceAction->stop();
            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(-(backDistance));
            mDistanceJudgement->start();
            state_left = 10;
        break;  

        case 10:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mCalcCurrentLocation->setAngle(0);
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state_left = 20;
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
            mDistanceJudgement->setDistance(-(rotateDistance));
            mDistanceJudgement->start();

            state_Uturn = 10;
        break;

        case 10:
            mRunStraightAction->straight(-15,-15);
            if(mDistanceJudgement->isDistanceOutBack())
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
    }
}

void FreeAreaTactics::obstacle(int color)
{
    switch(state_obstacle){
        case 0:
            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(8);
            mDistanceJudgement->start();
            state_obstacle = 10;
        break;

        case 10:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mRunParameter->setRotateAngle(45);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
                state_obstacle = 20;
            }
        break;

        case 20:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(15);
                mDistanceJudgement->start();
                state_obstacle = 30;
            }
        break;

        case 30:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(-15);
                mDistanceJudgement->start();
                state_obstacle = 40;
            }
        break;

        case 40:
            mRunStraightAction->straight(-15,-15);
            if(mDistanceJudgement->isDistanceOutBack())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mRunParameter->setRotateAngle(-45);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
                state_obstacle = 50;
            }
        break;

        case 50:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(-15);
                mDistanceJudgement->start();
                state_obstacle = 60;
            }
        break;

        case 60:
            mRunStraightAction->straight(-15,-15);
            if(color == 0)////gEV3ColorSensor->isColor_BLUE()//mDistanceJudgement->isDistanceOut()
            {
                state_obstacle = 2;
            }else if (color == 1)
            {
                state_obstacle = 3;
            }else if (color == 2)
            {
                state_obstacle = 4;
            }else 
            {
                state_obstacle = 5;
            }
        break;

        case 2:
            if(mEV3ColorSensor->isColor_BLUE())//青検知
            {
                state_obstacle = 70;
            }else
            {
                state_obstacle = 1;
            }
        break;

        case 3:
            if(mEV3ColorSensor->isColor_RED())//赤検知
            {
                state_obstacle = 70;
            }else
            {
                state_obstacle = 1;
            }
        break;

        case 4:
            if(mEV3ColorSensor->isColor_GREEN())//緑検知
            {
                state_obstacle = 70;
            }else
            {
                state_obstacle = 1;
            }
        break;

        case 5:
            if(mEV3ColorSensor->isColor_YELLOW())//黄検知
            {
                state_obstacle = 70;
            }else
            {
                state_obstacle = 1;
            }
        break;

        case 70:
            mRunStraightAction->stop();
            setFlag(true);
            state_obstacle = 0;
        break;
    }
}

void FreeAreaTactics::present(int color)
{
    switch (state_present)
    {
        case 0:
            //ライントレース初期設定
            mCalcCurrentLocation->setAngle(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(45);
            mDistanceJudgement->start();

            mRunParameter->setLineTraceSpeed(15);
            mRunParameter->setKP(section4[KP]);
            mRunParameter->setKI(section4[KI]);
            mRunParameter->setKD(section4[KD]);
            mLineTraceAction->updateParameter();
            state_present ++;
        break;

        case 1:
            mLineTraceAction->start();
            if(color == 0)////gEV3ColorSensor->isColor_BLUE()//mDistanceJudgement->isDistanceOut()
            {
                state_present = 2;
            }else if (color == 1)
            {
                state_present = 3;
            }else if (color == 2)
            {
                state_present = 4;
            }else 
            {
                state_present = 5;
            }
        break;

        case 2:
            if(mEV3ColorSensor->isColor_BLUE())//青検知
            {
                state_present = 10;
            }else
            {
                state_present = 1;
            }
        break;

        case 3:
            if(mEV3ColorSensor->isColor_RED() && red_count == 1)//赤検知
            {
                state_present = 10;
            }else if (mEV3ColorSensor->isColor_RED() && red_count == 3)
            {
                state_present = 60;
            }else
            {
                state_present = 1;
            }
        break;

        case 4:
            if(mEV3ColorSensor->isColor_GREEN())//緑検知
            {
                state_present = 10;
            }else
            {
                state_present = 1;
            }
        break;

        case 5:
            if(mEV3ColorSensor->isColor_YELLOW())//黄検知
            {
                state_present = 10;
            }else
            {
                state_present = 1;
            }
        break;

        case 10:
            mLineTraceAction->stop();
            mDistanceJudgement->stop();
            mRunParameter->setRotateAngle(-45);
            mRunParameter->setRotateSpeed(20);
            mRotateMachineAction->updateParameter();
            state_present = 20;
        break;

        case 20:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(20);
                mDistanceJudgement->start();
                state_present= 30;
            }
        break;

        case 30:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(-20);
                mDistanceJudgement->start();
                state_present = 40;
            }
        break;

        case 40:
            mRunStraightAction->straight(-15,-15);
            if(mDistanceJudgement->isDistanceOutBack())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mRunParameter->setRotateAngle(45);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
                state_present = 50;
            }
        break;

        case 50:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_present = 0;
            }
        break;

        case 60:
            mLineTraceAction->stop();
            mDistanceJudgement->stop();
            mRunParameter->setRotateAngle(45);
            mRunParameter->setRotateSpeed(20);
            mRotateMachineAction->updateParameter();
            state_present = 70;
        break;

        case 70:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(20);
                mDistanceJudgement->start();
                state_present= 80;
            }
        break;

        case 80:
            mRunStraightAction->straight(15,15);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(-20);
                mDistanceJudgement->start();
                state_present = 90;
            }
        break;

        case 90:
            mRunStraightAction->straight(-15,-15);
            if(mDistanceJudgement->isDistanceOutBack())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mRunParameter->setRotateAngle(-45);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
                state_present = 100;
            }
        break;

        case 100:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                setFlag(true);
                state_present = 0;
            }
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
