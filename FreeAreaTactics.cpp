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
    switch (state)
    {
        case 0:
            //ライントレース初期設定
            mCalcCurrentLocation->setAngle(0);
		    mCalcCurrentLocation->setPointX(0);
		    mCalcCurrentLocation->setPointY(0);

            mDistanceJudgement->stop();
            mDistanceJudgement->setDistance(45);
            mDistanceJudgement->start();

		    mRunParameter->setLineTraceSpeed(section4[SPEED]);
		    mRunParameter->setKP(section4[KP]);
		    mRunParameter->setKI(section4[KI]);
		    mRunParameter->setKD(section4[KD]);
		    mLineTraceAction->updateParameter();
            mArmControl->resetEncoder();	//エンコーダ値をリセット
		    state=10;
            //state = 490;
	    break;

        case 10: 
            //青サークル1まで
            mLineTraceAction->start();
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()//mDistanceJudgement->isDistanceOut()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
                state = 20;
            }
        break;

        case 20:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        //mArmControl->setBrake(true);
		        mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 30;
            }
        break;

        case 30:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state = 40;
            }
        break;

        case 40: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(90);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 50;
            }
        break;

        case 50:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state=60;
            }
        break;
        
        case 60:
            mRunStraightAction->straight(25,25);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=70;
            }
        break;

        case 70:
           //青サークル2まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=80;
            }
        break;

        case 80:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 90;
            }
        break;

        case 90:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 100;
            }
        break;

        case 100: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 110;
            }
        break;

        case 110:
           //赤サークル1まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=120;
            }
        break;

        case 120:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 130;
            }
        break;

        case 130:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 140;
            }
        break;

        case 140: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 150;
            }
        break;

        case 150:
           //赤サークル2まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=160;
            }
        break;

        case 160:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 170;
            }
        break;

        case 170:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0 )
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state = 180;
            }
        break;

        case 180: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(-90);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 190;
            }
        break;

        case 190:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state=200;
            }
        break;

        case 200:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=210;
            }
        break;

        case 210:
           //赤サークル3まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=220;
            }
        break;

        case 220:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 230;
            }
        break;

        case 230:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 240;
            }
        break;

        case 240: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 250;
            }
        break;

        case 250:
           //黄サークル1まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
		        state=260;
            }
        break;

        case 260:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 270;
            }
        break;

        case 270:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 280;
            }
        break;

        case 280: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 290;
            }
        break;

        case 290:
           //黄サークル2まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                /*
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                */
		        state=300;
                //state = 1000; //GOAL2へ
            }
        break;

        case 300:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 310;
            }
        break;

        case 310:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state = 320;
            }
        break;

        case 320: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(-90);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 330;
            }
        break;

        case 330:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state=340;
            }
        break;

        case 340:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=350;
            }
        break;

        case 350:
           //黄サークル3まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=360;
            }
        break;

        case 360:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 370;
            }
        break;

        case 370:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 380;
            }
        break;

        case 380: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 390;
            }
        break;

        case 390:
           //緑サークル1まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=400;
            }
        break;

        case 400:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 410;
            }
        break;

        case 410:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 420;
            }
        break;

        case 420: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 430;
            }
        break;

        case 430:
           //緑サークル2まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=440;
            }
        break;

        case 440:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 450;
            }
        break;

        case 450:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state = 460;
            }
        break;

        case 460: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(-90);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 470;
            }
        break;

        case 470:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state=480;
            }
        break;

        case 480:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=490;
            }
        break;

        case 490:
           //緑サークル3まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state=500;
            }
        break;

        case 500:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        //mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 510;
            }
        break;

        case 510:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() <= 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 520;
            }
        break;

        case 520: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 530;
            }
        break;

        case 530:
           //青サークル1まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
		        //state=540;
                state = 560;
            }
        break;

        case 540:
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 540;
            }
        break;

        case 550:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 560;
                //state = 2000; //GOAL2まで時計回りで走行
            }
        break;

        case 560: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 570;
            }
        break;

        case 570:
           //青サークル2まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
		        state = 580; //サークルループ
                //state = 2500 //動作終了
            }
        break;

        case 580:
            //サークルループ
            mArmControl->setPower(10);
            if (mArmControl->getEncoder() >= armAngle)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                state = 590;
            }
        break;

        case 590:
            mArmControl->setPower(-10);
            if (mArmControl->getEncoder() == 0)
            {
		        mArmControl->setPower(0);	//アーム停止
		        mArmControl->setBrake(true);
		        //mArmControl->resetEncoder();	//エンコーダ値をリセット
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state = 600;
            }
        break;

        case 600: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(-90);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 610;
            }
        break;

        case 610:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state=620;
            }
        break;

        case 620:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=70;
            }
        break;

        case 1000: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(90);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 1010;
            }
        break;

        case 1010:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state=1020;
            }
        break;

        case 1020:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=2500;
            }
        break;

        case 2000: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(180);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 2010;
            }
        break;

        case 2010:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state=2020;
            }
        break;

        case 2020:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=2030;
            }
        break;

        case 2030:
           //緑サークル3まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
                state = 2040;
            }
        break;

        case 2040: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 2050;
            }
        break;

        case 2050:
           //緑サークル2まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
		        state=2060;
            }
        break;

        case 2060: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mLineTraceAction->stop(); 
                mDistanceJudgement->stop();
		        mCalcCurrentLocation->setAngle(0);
                mRunParameter->setRotateAngle(90);
                mRunParameter->setRotateSpeed(20);
                mRotateMachineAction->updateParameter();
		        state = 2070;
            }
        break;

        case 2070:
            mRotateMachineAction->start();
            if(mRotateMachineAction->isFinished())
            {
                mRotateMachineAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(rotateDistance);
                mDistanceJudgement->start();
                state=2080;
            }
        break;

        case 2080:
            mRunStraightAction->straight(20,20);
            if(mDistanceJudgement->isDistanceOut())
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state=2090;
            }
        break;

        case 2090:
           //緑サークル1まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
		        state = 2100;
            }
        break;

        case 2100: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 2110;
            }
        break;

        case 2110:
           //黄サークル3まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
		        state=2120;
            }
        break;

        case 2120: 
            //直進
            mRunStraightAction->straight(20,20);
            if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
            {
                mRunStraightAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(lineDistance);
                mDistanceJudgement->start();
		        state = 2130;
            }
        break;

        case 2130:
           //黄サークル2まで
            mLineTraceAction->start();
            if(mDistanceJudgement->isDistanceOut())
            {
                mLineTraceAction->stop();
                mDistanceJudgement->stop();
                mDistanceJudgement->setDistance(straightDistance);
                mDistanceJudgement->start();
		        state=2500;
            }
        break;

	case 2500://動作完了用
		mLineTraceAction->stop();
		flag = true;
		break;
	default:
		break;
	}
}

bool FreeAreaTactics::isFinished()
{
	return flag;
}
