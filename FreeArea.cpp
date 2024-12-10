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
    
    char buf[32];
    //char buf2[32];
    sprintf(buf, "FreeArea->state: %d", mFreeAreaTactics->getPresent(0));
    //sprintf(buf, "FreeArea->state: %d", mFreeAreaTactics->getObstacle());
    mDisplay->display(buf);


    mEV3ColorSensor->getColorBrightness();
    memfile_t memfile; // メモリファイルの構造体を作成
    ev3_memfile_load("ev3rt/res/Jinnguru2.wav", &memfile); //SDカード内の"test.wav"をメモリファイルとしてロード
    ev3_speaker_set_volume(5); //音量の設定
    ev3_speaker_play_file(&memfile, SOUND_MANUAL_STOP); // 音声ファイルを再生

    //printf("FreeArea -> Current state : %d\n",state);	//stateの値を表示
    
    switch (state)
    {
        case 0:
            //青サークル1(角)
            mFreeAreaTactics->LineTrace_Jugde_O(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setObstacle(1);//パターン1,4
                mFreeAreaTactics->setFlag(false);
                //state = 10;
                state = 20;
            }
	    break;

        case 10:
            if(mFreeAreaTactics->getObstacle() == 1)
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
            mFreeAreaTactics->LineTrace_Jugde_P(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setPresent(1); //パターン1
                mFreeAreaTactics->setFlag(false);
                state = 40;
                //state = 50;
            }
	    break;

        case 40:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state =500;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 50;
            }
        break;

        case 50:
            //青サークル2直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 60;
            }
        break;

        case 60:
            //赤サークル1
            mFreeAreaTactics->LineTrace_Jugde_P(RED);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setPresent(1); //パターン1
                mFreeAreaTactics->setFlag(false);
                state = 70;
                //state = 80;
            }
	    break;

        case 70:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state =600;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 80;
            }
        break;

        case 80:
            //赤サークル1直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 85;
            }
        break;

        case 85:
            if (mFreeAreaTactics->getPresent(1) == 2)
            {
                state = 2000;
            }else {
                state = 90;
            }
        break;

        case 90:
            //赤サークル2(角)
            mFreeAreaTactics->LineTrace_Jugde_O(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setObstacle(1);
                mFreeAreaTactics->setFlag(false);
                state = 100;
                //state = 110;
            }
	    break;

        case 100:
            if(mFreeAreaTactics->getObstacle() == 1)
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
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 120;
            }
        break;

        case 120:
            //赤サークル3
            mFreeAreaTactics->LineTrace_Jugde_P(RED);
            if (mFreeAreaTactics->isFinished())
            {                
                //mFreeAreaTactics->setPresent(1); //パターン2
                mFreeAreaTactics->setFlag(false);
                state = 130;
                //state = 140;
            }
	    break;

        case 130:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state =600;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 145;
            }
        break;

        case 140:
            if (mFreeAreaTactics->getPresent(1) == 2)
            {
                state = 2030;
            }else {
                state = 145;
            }
        break;

        case 145:
            //赤サークル3直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 150;
            }
        break;

        case 150:
            //黄サークル1
            mFreeAreaTactics->LineTrace_Jugde_P(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setPresent(1);
                mFreeAreaTactics->setFlag(false);
                state = 160;
                //state = 180; 
            }
	    break;

        case 160:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setFlag(false);
                state =700;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 185;
            }
        break;

        case 180:
            if (mFreeAreaTactics->getPresent(1) == 2)
            {
                state = 2030;
            }else {
                state = 185;
            }
        break;

        case 185:
            //黄サークル1直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state = 190;
            }
        break;

        case 190:
        //黄サークル2(角)
            mFreeAreaTactics->LineTrace_Jugde_O(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setObstacle(1);
                mFreeAreaTactics->setFlag(false);
                //state = 200;
                state = 195; 
            }
	    break;

        case 195:
            if((mFreeAreaTactics->getPresent(1)) == 2 && (mFreeAreaTactics->getObstacle()) == 1)
            {
                state = 1000;
            }else if (mFreeAreaTactics->getObstacle() == 1)
            {
                state = 200;
            }else {
                state = 210;
            }
        break;

        case 200:
            if(mFreeAreaTactics->getObstacle() == 1)
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
            mFreeAreaTactics->LineTrace_Jugde_P(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setPresent(1); //パターン2,3
                mFreeAreaTactics->setFlag(false);
                state = 230;
                //state = 240; 
            }
	    break;

        case 230:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state =700;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 240;
            }
        break;

        case 240:
            //黄サークル3直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 250;
            }
        break;

        case 250:
            //緑サークル1
            mFreeAreaTactics->LineTrace_Jugde_P(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setPresent(1); //パターン3
                mFreeAreaTactics->setFlag(false);
                state = 260;
                //state = 270; 
            }
	    break;

        case 260:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state =800;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 270;
            }
        break;

        case 270:
            //緑サークル1直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 280;
            }
        break;

        case 280:
            //緑サークル2(角)
            mFreeAreaTactics->LineTrace_Jugde_O(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 290;
                //state = 300; 
            }
	    break;

        case 290:
            if(mFreeAreaTactics->getObstacle() == 1)
            {
                mFreeAreaTactics->setFlag(false);
                state =930;
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
            mFreeAreaTactics->LineTrace_Jugde_P(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setPresent(1); //パターン4
                mFreeAreaTactics->setFlag(false);
                state = 320;
                //state = 330;  
            }
	    break;

        case 320:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state =800;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 330;
            }
        break;

        case 330:
            //緑サークル3直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 340;
            }
        break;

        case 340:
            //ライントレース初期設定
            mFreeAreaTactics->LineTrace_Jugde_P(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setPresent(1); //パターン4
                mFreeAreaTactics->setFlag(false);
                state = 350;
                //state = 360; //ループさせたいなら
            }
	    break;

        case 350:
            if(mFreeAreaTactics->getPresent(0) == 1)
            {
                mFreeAreaTactics->setPresent(0);
                mFreeAreaTactics->setFlag(false);
                state =500;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 360;
            }
        break;

        case 360:
            //青サークル3直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 370;
            }
        break;

        case 370:
            mFreeAreaTactics->LineTrace_Jugde_O(BLUE);
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

        case 490:
            mFreeAreaTactics->Turn_Right();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 485;
            }
        break;

        case 485:
            mFreeAreaTactics->LineTrace2(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 480;
            }
        break;

        case 480:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 475;
            }
        break;

        case 475:
            mFreeAreaTactics->Turn_Right();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 470;
            }
        break;

        case 470:
            mFreeAreaTactics->LineTrace2(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 465;
            }
        break;

        case 465:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 460;
            }
        break;

        case 460:
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 455;
            }
        break;

        case 455:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                if ((mFreeAreaTactics->getColor(YELLOW)) == 5 && (mFreeAreaTactics->getColor(GREEN) >= 1))
                {
                    state = 430;
                }else if (mFreeAreaTactics->getColor(YELLOW) == 4)
                {
                    state = 430;
                }else{
                    state = 410;
                }
            }
        break;

        case 430:
            mFreeAreaTactics->stop();
        break;

        case 500:
            mFreeAreaTactics->Straight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 508;
            }
        break;

        case 508:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 509;
            }
        break;

        case 509:
           //プレゼント配送
            mFreeAreaTactics->Straight();
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
            mFreeAreaTactics->LineTrace2(BLUE);
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
                if ((mFreeAreaTactics->getColor(BLUE)) == 2)
                {
                    state = 50;
                }else if ((mFreeAreaTactics->getColor(BLUE)) == 3)
                {
                    state = 5000;
                }
                state = 50;
            }
        break;

        case 5000:
            mFreeAreaTactics->Turn_Right2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5005;
            }
        break;

        case 5005:
            mFreeAreaTactics->LineTrace2(GREEN);
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5010;
            }
        break;

        case 5010:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5015;
            }
        break;

        case 5015:
            mFreeAreaTactics->LineTrace2(GREEN);
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5020;
            }
        break;

        case 5020:
            mFreeAreaTactics->Turn_Right();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5025;
            }
        break;

        case 5025:
            mFreeAreaTactics->LineTrace2(GREEN);
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5030;
            }
        break;

        case 5030:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5035;
            }
        break;

        case 5035:
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5040;
            }
        break;

        case 5040:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 5045;
            }
        break;

        case 5045:
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3000;
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
            mFreeAreaTactics->LineTrace2(RED);
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
                if ((mFreeAreaTactics->getColor(RED)) == 1)
                {
                    state = 90;
                }else if ((mFreeAreaTactics->getColor(RED)) == 3)
                {
                    state = 150;
                }else if ((mFreeAreaTactics->getPresent(1)) == 2)
                {
                    state = 1300;
                }
                state = 90;
            }
        break;

        case 700:
           //プレゼント配送
            mFreeAreaTactics->Straight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 701;
            }
        break;

        case 701:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 709;
            }
        break;

        case 709:
           //プレゼント配送
            mFreeAreaTactics->Straight();
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
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                if ((mFreeAreaTactics->getColor(YELLOW)) == 3 && (mFreeAreaTactics->getPresent(1)) == 2)
                {
                    state = 400;
                }else {
                    state = 740; 
                }
                state = 740;
            }
        break;

        case 400:
            mFreeAreaTactics->Turn_Right2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 405;
            }
        break;

        case 405:
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 410;
            }
        break;

        case 410:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3000;
            }
        break;

        case 740:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                if (mFreeAreaTactics->getColor(YELLOW) == 1)
                {
                    state = 190;
                }else if (mFreeAreaTactics->getColor(YELLOW) == 3)
                {
                    state = 250;
                }
                state = 2075;
            }
        break;

        case 800:
           //プレゼント配送
            mFreeAreaTactics->Straight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 801;
            }
        break;

        case 801:
           //プレゼント配送
            mFreeAreaTactics->Turn_Left2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 809;
            }
        break;

        case 809:
           //プレゼント配送
            mFreeAreaTactics->Straight();
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
            mFreeAreaTactics->LineTrace2(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                if ((mFreeAreaTactics->getColor(YELLOW)) == 3 && (mFreeAreaTactics->getPresent(1)) == 2)
                {
                    state = 4000;
                }else {
                    state = 840;
                }
            }
        break;

        case 4000:
            mFreeAreaTactics->Turn_Right2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 4010;
            }
        break;

        case 4010:
            mFreeAreaTactics->LineTrace2(YELLOW);
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 4015;
            }
        break;

        case 4015:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 4020;
            }
        break;

        case 4020:
            mFreeAreaTactics->LineTrace2(YELLOW);
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3000;
            }
        break;

        case 4025:
            mFreeAreaTactics->CircleStraight();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3000;
            }
        break;

        case 1375:
            mFreeAreaTactics->Turn_Right2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1370;
            }
        break;

        case 840:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                if ((mFreeAreaTactics->getColor(GREEN)) == 1)
                {
                    state = 280;
                }else if ((mFreeAreaTactics->getColor(GREEN)) == 3)
                {
                    state = 340;
                }
            }
        break;

        case 900:
        //障害物除去
            mFreeAreaTactics->obstacle(BLUE);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 15;
            }
        break;

        case 910:
        //障害物除去
            mFreeAreaTactics->obstacle(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                if ((mFreeAreaTactics->getPresent(1)) == 2)
                {
                    state = 2020;
                }else {
                    state = 110;
                }
            }
        break;

        case 920:
        //障害物除去
            mFreeAreaTactics->obstacle(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                if ((mFreeAreaTactics->getPresent(1)) == 2)
                {
                    state = 3000;
                }
                state = 210;
            }
        break;

        case 930:
        //障害物除去
            mFreeAreaTactics->obstacle(GREEN);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 300;
            }
        break;

        case 1000:
            //右折する
            mFreeAreaTactics->Turn_Right2();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3000;
            }
        break;

        case 1300:
            if (mFreeAreaTactics->getObstacle() == 0)
            {
                state = 3000;
            }else {
                state = 1310;
            }
        break;


        case 1310:
            //赤サークル3まで
            mFreeAreaTactics->LineTrace2(RED);
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1320;
            }
        break;

        case 1320:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1330;
            }
        break;

        case 1330:
            //赤サークル3
            mFreeAreaTactics->LineTrace2(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1340;
            }
        break;

        case 1340:
            //赤サークル3直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1350;
            }
        break;

        case 1350:
            //黄サークル1
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1360;
            }
	    break;

        case 1360:
            //黄サークル1直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1370;
            }
        break;

        case 1370:
            //黄サークル2
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 1380;
            }
	    break;

        case 1380:
            //黄サークル2直進
            mFreeAreaTactics->Turn_Right2();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3000;
            }

        case 2000:
            //プレゼント全て配送後
            //赤サークル2(角)
            mFreeAreaTactics->LineTrace_Jugde_O(RED);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setObstacle(1);
                mFreeAreaTactics->setFlag(false);
                state = 2010;
                //state = 110;
            }
	    break;

        case 2010:
            if((mFreeAreaTactics->getObstacle()) == 1)
            {
                mFreeAreaTactics->setFlag(false);
                state =910;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 2020;
            }
        break;

        case 2020:
            mFreeAreaTactics->Turn_Left();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2030;
            }
        break;

        case 2030:
            mFreeAreaTactics->LineTrace2(RED);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2040;
                //state = 140;
            }
	    break;

        case 2040:
            //赤サークル2直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2050;
            }
        break;

        case 2050:
            //黄サークル1
            mFreeAreaTactics->LineTrace2(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2060;
                //state = 140;
            }
	    break;

        case 2060:
            //黄サークル1直進
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2070;
            }
        break;

        case 2070:
            if (mFreeAreaTactics->getObstacle() == 1)
            {
                state = 2090;
            }else {
                state = 2075;
            }
        break;

        case 2075:
            //黄サークル2
            mFreeAreaTactics->LineTrace_Jugde_O(YELLOW);
            if (mFreeAreaTactics->isFinished())
            {
                //mFreeAreaTactics->setObstacle(1);
                mFreeAreaTactics->setFlag(false);
                state = 2080;
            }
        break;

        case 2080:
            if(mFreeAreaTactics->getObstacle() == 1)
            {
                mFreeAreaTactics->setFlag(false);
                state =920;
            }else
            {   
                mFreeAreaTactics->setFlag(false);
                state = 3000;
            }
        break;

        case 2090:
            mFreeAreaTactics->LineTrace2(YELLOW);
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3000;
            }

        case 20400:
            if ((mFreeAreaTactics->getColor(YELLOW)) == 2)
            {
                state = 2500;
            }else {
                state = 2050;
            }
        break;


        case 20500:
            mFreeAreaTactics->CircleStraight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 2030;
            }
        break;

        case 3000:
            mFreeAreaTactics->Turn_Right();
            if (mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3010;
            }
        break;

        case 3010:
            mFreeAreaTactics->Straight();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3020;
            }
        break;

        case 3020:
            mFreeAreaTactics->Uturn();
            if(mFreeAreaTactics->isFinished())
            {
                mFreeAreaTactics->setFlag(false);
                state = 3030;
            }
        break;

        case 3030:
            mFreeAreaTactics->Straight_Back();
            if(mFreeAreaTactics->isFinished())
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
