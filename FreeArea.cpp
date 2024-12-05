#include "FreeArea.h"
//#include "BluetoothLogger.h"
// #include <ctime>
#include <stdio.h>

#define CALIB_FONT_HEIGHT (16 /*TODO: magic number*/)


FreeArea::FreeArea(FreeAreaTactics *FreeAreaTactics)
: mFreeAreaTactics(FreeAreaTactics)
{
	state = 0; //<-スタート位置から
}

FreeArea::~FreeArea()
{
}

/**
* 区間制御戦術を実行する
*/
void FreeArea::execute()
{
    //printf("FreeArea -> Current state : %d\n",state);	//stateの値を表示
    switch (state)
    {
        case 0:
            //青サークル1(角)
            mFreeAreaTactics->LineTrace_Jugde(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 10;
            }
	    break;

        case 10:
            if(mFreeAreaTactics->ObjectDetection(OBSTACLE))
            {
                mFreeAreaTactics->setFlag(false);
                state =900;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 20;
            }
        break;

        case 20: 
            mFreeAreaTactics->Turn_Right();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 30;
            }
        break;

        case 30:
            //青サークル2
            mFreeAreaTactics->LineTrace_Jugde(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 40;
            }
	    break;

        case 40:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =500;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 50;
            }
        break;

        case 50:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 60;
            }
        break;

        case 60:
            //赤サークル1
            mFreeAreaTactics->LineTrace_Jugde(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 70;
                //state = 2500;
            }
	    break;

        case 70:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =600;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 80;
            }
        break;

        case 80:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 90;
            }
        break;

        case 90:
            //赤サークル2(角)
            mFreeAreaTactics->LineTrace_Jugde(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 100;
            }
	    break;

        case 100:
            if(mFreeAreaTactics->ObjectDetection(OBSTACLE))
            {
                mFreeAreaTactics->setFlag(false);
                state =910;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 110;
            }
        break;

        case 110:
            mFreeAreaTactics->Straight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 120;
            }
        break;

        case 120:
            //赤サークル3
            mFreeAreaTactics->LineTrace_Jugde(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 130;
            }
	    break;

        case 130:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =600;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 140;
            }
        break;

        case 140:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 150;
            }
        break;

        case 150:
            //黄サークル1
            mFreeAreaTactics->LineTrace_Jugde(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 160;
            }
	    break;

        case 160:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =700;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 180;
            }
        break;

        case 180:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 190;
            }
        break;

        case 190:
        //黄サークル2(角)
            mFreeAreaTactics->LineTrace_Jugde(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 200;
            }
	    break;

        case 200:
            if(mFreeAreaTactics->ObjectDetection(OBSTACLE))
            {
                mFreeAreaTactics->setFlag(false);
                state =920;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 210;
            }
        break;

        case 210:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 220;
            }
        break;

        case 220:
            //黄サークル3
            mFreeAreaTactics->LineTrace_Jugde(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 230;
            }
	    break;

        case 230:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =700;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 240;
            }
        break;

        case 240:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 250;
            }
        break;

        case 250:
            //緑サークル1
            mFreeAreaTactics->LineTrace_Jugde(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 260;
            }
	    break;

        case 260:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =800;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 270;
            }
        break;

        case 270:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 280;
            }
        break;

        case 280:
            //緑サークル2(角)
            mFreeAreaTactics->LineTrace_Jugde(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 290;
            }
	    break;

        case 290:
            if(mFreeAreaTactics->ObjectDetection(OBSTACLE))
            {
                mFreeAreaTactics->setFlag(false);
                state =920;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 300;
            }
        break;

        case 300:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 310;
            }
        break;

        case 310:
            //緑サークル3
            mFreeAreaTactics->LineTrace_Jugde(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 320;
            }
	    break;

        case 320:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =800;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 330;
            }
        break;

        case 330:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 340;
            }
        break;

        case 340:
            //ライントレース初期設定
            mFreeAreaTactics->LineTrace_Jugde(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 350;
            }
	    break;

        case 350:
            if(mFreeAreaTactics->ObjectDetection(PRESENT))
            {
                mFreeAreaTactics->setFlag(false);
                state =500;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 360;
            }
        break;

        case 360:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 370;
            }
        break;

        case 370:
            mFreeAreaTactics->LineTrace_Jugde(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 380;
            }
	    break;

        case 380:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 30;
            }
        break;

        case 500:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 510;
            }
        break;

        case 510:
            mFreeAreaTactics->present(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                p_count ++;
                state = 520;
            }
        break;

        case 520:
            mFreeAreaTactics->Uturn();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 530;
            }
        break;

        case 530:
            mFreeAreaTactics->LineTrace(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 540;
            }
        break;

        case 540:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1000;
            }
        break;

        case 600:
           //プレゼント配送
            mFreeAreaTactics->Straight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 608;
            }
        break;

        case 605:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 610;
            }
        break;

        case 608:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 609;
            }
        break;

        case 609:
           //プレゼント配送
            mFreeAreaTactics->Straight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 610;
            }
        break;

        case 610:
            mFreeAreaTactics->present(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                p_count ++;
                state = 620;
            }
        break;

        case 620:
            mFreeAreaTactics->Uturn();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 630;
            }
        break;

        case 630:
            mFreeAreaTactics->LineTrace(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 640;
            }
        break;

        case 640:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 90;
            }
        break;

        case 700:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 710;
            }
        break;

        case 710:
            mFreeAreaTactics->present(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                p_count ++;
                state = 720;
            }
        break;

        case 720:
            mFreeAreaTactics->Uturn();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 730;
            }
        break;

        case 730:
            mFreeAreaTactics->LineTrace(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 740;
            }
        break;

        case 740:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1000;
            }
        break;

        case 800:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 810;
            }
        break;

        case 810:
            mFreeAreaTactics->present(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                p_count ++;
                state = 820;
            }
        break;

        case 820:
            mFreeAreaTactics->Uturn();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 830;
            }
        break;

        case 830:
            mFreeAreaTactics->LineTrace(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 840;
            }
        break;

        case 840:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1000;
            }
        break;

        case 900:
        //障害物除去
            mFreeAreaTactics->obstacle(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2500;
            }
        break;

        case 910:
        //障害物除去
            mFreeAreaTactics->obstacle(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 110;
            }
        break;

        case 920:
        //障害物除去
            mFreeAreaTactics->obstacle(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2500;
            }
        break;

        case 930:
        //障害物除去
            mFreeAreaTactics->obstacle(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2500;
            }
        break;
    }
}

bool FreeArea::isFinished()
{
	return flag;
}