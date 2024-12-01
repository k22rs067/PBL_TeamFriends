#include "LapSectionTactics.h"
//#include "BluetoothLogger.h"
// #include <ctime>
#include <stdio.h>

#define CALIB_FONT_HEIGHT (16 /*TODO: magic number*/)


LapSectionTactics::LapSectionTactics()
{
	state = 0; //<-スタート位置から
}

LapSectionTactics::~LapSectionTactics()
{
}

/**
* 区間制御戦術を実行する
*/
void LapSectionTactics::execute()
{
	switch (state)
  {
    case 0:
      //ライントレース初期設定
      mCalcCurrentLocation->setAngle(0);
		  mCalcCurrentLocation->setPointX(0);
		  mCalcCurrentLocation->setPointY(0);

      mDistanceJudgement->stop();
      mDistanceJudgement->setDistance(300);
      mDistanceJudgement->start();

		  mRunParameter->setLineTraceSpeed(section0[SPEED]);
		  mRunParameter->setKP(section0[KP]);
		  mRunParameter->setKI(section0[KI]);
		  mRunParameter->setKD(section0[KD]);
		  mLineTraceAction->updateParameter();
		  state=10;
	  break;

    case 10: 
      //Startからカーブまで
      mLineTraceAction->start();
      if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
      {
        mLineTraceAction->stop(); 
        mDistanceJudgement->stop();
        mDistanceJudgement->setDistance(30);
        mDistanceJudgement->start();
		    mRunParameter->setLineTraceSpeed(section1[SPEED]);
		    mRunParameter->setKP(section1[KP]);
		    mRunParameter->setKI(section1[KI]);
		    mRunParameter->setKD(section1[KD]);
		    mLineTraceAction->updateParameter();
        state = 20;
      }
    break;

    case 20:
      //カーブから直線まで
      mLineTraceAction->start();
      if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
      {
        mLineTraceAction->stop(); 
        mDistanceJudgement->stop();
        mDistanceJudgement->setDistance(170);
        mDistanceJudgement->start();
		    mRunParameter->setLineTraceSpeed(section2[SPEED]);
		    mRunParameter->setKP(section2[KP]);
		    mRunParameter->setKI(section2[KI]);
		    mRunParameter->setKD(section2[KD]);
		    mLineTraceAction->updateParameter();
        state = 30;
      }
    break;

    case 30:
      //直線からカーブまで
      mLineTraceAction->start();
      if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
      {
        mLineTraceAction->stop(); 
        mDistanceJudgement->stop();
        mDistanceJudgement->setDistance(60);
        mDistanceJudgement->start();
		    mRunParameter->setLineTraceSpeed(section1[SPEED]);
		    mRunParameter->setKP(section1[KP]);
		    mRunParameter->setKI(section1[KI]);
		    mRunParameter->setKD(section1[KD]);
		    mLineTraceAction->updateParameter();
        state = 40;
      }
    break;

    case 40:
      //カーブから直線まで
      mLineTraceAction->start();
      if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
      {
        mLineTraceAction->stop(); 
        mDistanceJudgement->stop();
        mDistanceJudgement->setDistance(170);
        mDistanceJudgement->start();
		    mRunParameter->setLineTraceSpeed(section2[SPEED]);
		    mRunParameter->setKP(section2[KP]);
		    mRunParameter->setKI(section2[KI]);
		    mRunParameter->setKD(section2[KD]);
		    mLineTraceAction->updateParameter();
        state = 50;
      }
    break;

    case 50:
      //カーブから直線まで
      mLineTraceAction->start();
      if (mDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
      {
        mLineTraceAction->stop(); 
        mDistanceJudgement->stop();
        mDistanceJudgement->setDistance(100);
        mDistanceJudgement->start();
		    mRunParameter->setLineTraceSpeed(section2[SPEED]);
		    mRunParameter->setKP(section2[KP]);
		    mRunParameter->setKI(section2[KI]);
		    mRunParameter->setKD(section2[KD]);
		    mLineTraceAction->updateParameter();
        state = 2500;
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

bool LapSectionTactics::isFinished()
{
	return flag;
}
