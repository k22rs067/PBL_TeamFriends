#include "ev3api.h"
#include "Action.h"
#include "app.h"
#include "Button.h"
#include "EV3ColorSensor.h"
#include "LineTraceAction.h"
#include "Motor.h"
#include "RearMotor.h"
#include "RunParameter.h"
#include "TouchSensor.h"
#include "Display.h"
#include "ArmControl.h"
#include "CalcCurrentLocation.h"
#include "RunStraightAction.h"
#include "stdio.h"
#include "DistanceJudgement.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6 /*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8 /*TODO: magic number*/)

// using宣言
using ev3api::Motor;
using ev3api::ColorSensor;
// using ev3api::Clock;
using ev3api::TouchSensor;

// Device objects
// オブジェクトを静的に確保する
Motor gArmMotor(PORT_A);
Motor gRightWheel(PORT_B);
Motor gLeftWheel(PORT_C);
ColorSensor gColorSensor(PORT_2);
TouchSensor gTouchSensor(PORT_1);

// オブジェクトの定義
static RearMotor *gRearMotor;
static EV3ColorSensor *gEV3ColorSensor;
static RunParameter *gRunParameter;
static LineTraceAction *gLineTraceAction;
static Button *gButton;
static Display *gDisplay;
static ArmControl *gArmControl;
static RunStraightAction *gRunStraightAction;
static CalcCurrentLocation *gCalcCurrentLocation;
static DistanceJudgement *gDistanceJudgement;

//static SpeedAdjustment *gSpeedAdjustment;

static void user_system_create()
{
    // オブジェクトの生成
    // gTimerJudgement = new TimerJudgement(gClock);
    gEV3ColorSensor = new EV3ColorSensor(gColorSensor);
    // gEV3SonarSensor = new EV3SonarSensor(gSonarSensor, gClock);
    // gEV3GyroSensor = new EV3GyroSensor(gGyroSensor);
    gRearMotor = new RearMotor(gLeftWheel, gRightWheel);
    gArmControl = new ArmControl(gArmMotor);
    gCalcCurrentLocation = new CalcCurrentLocation(gRearMotor);
    gDistanceJudgement = new DistanceJudgement(gCalcCurrentLocation);
    // gStraightDetection = new StraightDetection(gRearMotor, gTimerJudgement);
    gRunParameter = new RunParameter();
    // gSpeedAdjustment = new SpeedAdjustment(gClock, gRunParameter);
    gLineTraceAction = new LineTraceAction();
    gDisplay = new Display();
    gButton = new Button(gTouchSensor);
    // gArmPositionSetAction = new ArmPositionSetAction();
    gRunStraightAction = new RunStraightAction();
    // gRotateMachineAction = new RotateMachineAction();
    // gRotateAction = new RotateAction(gRotateMachineAction);
    // gCurvatureRunAction = new CurvatureRunAction();
    // gDecelerationRotaryAction = new DecelerationRotaryAction();
    // gSectionControlTactics = new SectionControlTactics(gColorSensor);
    // gSectionControlTactics = new SectionControlTactics(gColorSensor, gRearMotor,gArmControl);
    // gCalibration = new Calibration(gTouchSensor, gRunParameter, gTimerJudgement, gEV3ColorSensor, gRearMotor, gCalcCurrentLocation);
    // gIPCommunication = new IPCommunication();
    // gBlockBingo = new BlockBingo(gRearMotor);

    // gAlgori = new Algori();

    // gCleaningPutAction = new CleaningPutAction();

    // //Actionクラスに参照を設定する
    Action::setObject(gRunParameter, gRearMotor, gArmControl, gEV3ColorSensor, gCalcCurrentLocation, gLineTraceAction, gRunStraightAction);
    // //Tacticsクラスに参照を設定する
    // Tactics::setObject(gEV3ColorSensor, gEV3SonarSensor, gEV3GyroSensor, gRunParameter, gCalcCurrentLocation,gDistanceJudgement, gTimerJudgement, gStraightDetection, gArmPositionSetAction, gLineTraceAction, gRunStraightAction, gRotateMachineAction, gRotateAction, gCurvatureRunAction, gDecelerationRotaryAction);

    // LEDをオレンジに光らせる
    ev3_led_set_color(LED_ORANGE);
}

/*
static void user_system_destroy()
{
    //モータのエンコーダ値をリセット
    gRightWheel.reset();
    gLeftWheel.reset();
    // gArmMotor.reset();
    // gTailMotor.reset();

    //オブジェクトの削除
}
*/

void main_task(intptr_t unused) 
{
    user_system_create(); // センサやモータの初期化処理
    sta_cyc(EV3_CYC_RUN);
    slp_tsk();
    stp_cyc(EV3_CYC_RUN);
    ext_tsk();
}

static int state = 0;

void run_task(intptr_t unused) 
{
    char buf[100];
    sprintf(buf, "Brightness: %lf", gEV3ColorSensor->getColorBrightness());
    //sprintf(buf, "Brightness: %d", gEV3ColorSensor->getBrightness());
    gDisplay->display(buf,0,0);

    gCalcCurrentLocation->calcCurrentLocation(); //計算メソッド
  
    switch (state)
    {
        case 0:
        if (gButton->Touch_sensor_isPressed())
        {
            gDistanceJudgement->stop();
            gDistanceJudgement->setDistance(580);
            gDistanceJudgement->start();
            gRunParameter->setLineTraceSpeed(30);
            gRunParameter->setKP(0.2);
            gRunParameter->setKI(0);
            gRunParameter->setKD(1);
            gLineTraceAction->updateParameter();
            state = 1;
        }
        break;

        case 1:
        //gRunStraightAction->straight(50,50);
        gLineTraceAction->start();
        if (gDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
        {
            gLineTraceAction->stop(); 
            //gRunStraightAction->stop();
            gDistanceJudgement->stop();
            gDistanceJudgement->setDistance(20);
            gDistanceJudgement->start();
            state = 2;
        }
        break;

        case 2:
        gRunStraightAction->straight(30,28);
        if (gDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
        {
            //gRunStraightAction->stop();
            gDistanceJudgement->stop();
            gDistanceJudgement->setDistance(115);
            gDistanceJudgement->start();
            state = 3;
        }
        break;

        case 3:
        //gRunStraightAction->straight(50,50);
        gLineTraceAction->start();
        if (gDistanceJudgement->isDistanceOut())////gEV3ColorSensor->isColor_BLUE()
        {
            gLineTraceAction->stop(); 
            //gRunStraightAction->stop();
            gDistanceJudgement->stop();
            gDistanceJudgement->setDistance(20);
            gDistanceJudgement->start();
            state = 999;
        }
        break;







/**
        case 0:
        if (gButton->Touch_sensor_isPressed())
        {
            printf("left button pressed\n");
            char buf[32];
            sprintf(buf, "Brightness: %lf", gEV3ColorSensor->getColorBrightness());
            gDisplay->display(buf);
        }
        break
        */
    }
}