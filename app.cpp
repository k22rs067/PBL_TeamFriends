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
#include "Tactics.h"
#include "RotateMachineAction.h"
#include "RotateAction.h"
#include "LapSectionTactics.h"


#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (12 /*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (16 /*TODO: magic number*/)
#define N 10

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
static RotateAction *gRotateAction;
static RotateMachineAction *gRotateMachineAction; 
static LapSectionTactics *gLapSectionTactics;

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
    //gArmPositionSetAction = new ArmPositionSetAction();
    gRunStraightAction = new RunStraightAction();
    gRotateMachineAction = new RotateMachineAction();
    gRotateAction = new RotateAction(gRotateMachineAction);
    // gCurvatureRunAction = new CurvatureRunAction();
    // gDecelerationRotaryAction = new DecelerationRotaryAction();
    // gSectionControlTactics = new SectionControlTactics(gColorSensor);
    gLapSectionTactics = new LapSectionTactics();
    // gCalibration = new Calibration(gTouchSensor, gRunParameter, gTimerJudgement, gEV3ColorSensor, gRearMotor, gCalcCurrentLocation);
    // gIPCommunication = new IPCommunication();
    // gBlockBingo = new BlockBingo(gRearMotor);

    // gAlgori = new Algori();

    // gCleaningPutAction = new CleaningPutAction();

    // //Actionクラスに参照を設定する
    Action::setObject(gRunParameter, gRearMotor, gArmControl, gEV3ColorSensor, gCalcCurrentLocation, gLineTraceAction, gRunStraightAction);
    // //Tacticsクラスに参照を設定する
    Tactics::setObject(gEV3ColorSensor, gRunParameter, gCalcCurrentLocation, gDistanceJudgement, gLineTraceAction, gRunStraightAction, gRotateMachineAction, gRotateAction);

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
//static int state = 100; //色検知
static int white_brightness = 0;
static char buf[100];

void run_task(intptr_t unused) 
{
    /*
    char buf[100];
    sprintf(buf, "Brightness: %lf", gEV3ColorSensor->getColorBrightness());
    //sprintf(buf, "Brightness: %d", gEV3ColorSensor->getBrightness());
    gDisplay->display(buf,0,0);
    */
    gCalcCurrentLocation->calcCurrentLocation(); //計算メソッド
    gArmControl->setBrake(true);
    switch(state){
        case 0:
        if (gButton->Touch_sensor_isPressed())//gButton->button_left_isPressed()
        {
            state = 1;
            //state = 10;
        }
        break;

        case 1:
            gLapSectionTactics->execute();
            if(gLapSectionTactics->isFinished())
            {
                state=25;
            }
        break;

        case 10:
            gDistanceJudgement->stop();
            gDistanceJudgement->setDistance(10);
            gDistanceJudgement->start();
		    state=20;
        break;

        case 20:
            gRunStraightAction->straight(20,20);//20,20
            if(gEV3ColorSensor->isColor_YELLOW())//gDistanceJudgement->isDistanceOut()
            {
                gRunStraightAction->stop();
		        gCalcCurrentLocation->setAngle(0);
                gRunParameter->setRotateAngle(-90);
                gRunParameter->setRotateSpeed(20);
                gDistanceJudgement->stop();
                gRotateMachineAction->updateParameter();
		        state=30;
            }
        break;

        case 25:
		        gCalcCurrentLocation->setAngle(0);
                gRunParameter->setRotateAngle(-90);
                gRunParameter->setRotateSpeed(20);
                gDistanceJudgement->stop();
                gRotateMachineAction->updateParameter();
		        state=30;
        break;

        case 30:
            gRotateMachineAction->start();
            if(gRotateMachineAction->isFinished())
            {
                gRotateMachineAction->stop();
                gDistanceJudgement->stop();
                gDistanceJudgement->setDistance(10);
                gDistanceJudgement->start();
                state=40;
            }
        break;

        case 40:
            gRunStraightAction->straight(20,20);
            if(gDistanceJudgement->isDistanceOut())
            {
                gRunStraightAction->stop();
                gDistanceJudgement->stop();
                gDistanceJudgement->setDistance(10);
                gDistanceJudgement->start();
		        state=50;
            }
        break;

        case 50:
            gLineTraceAction->stop();
            if(gDistanceJudgement->isDistanceOut())
            {
                gRunStraightAction->stop();
                gDistanceJudgement->stop();
                gDistanceJudgement->setDistance(10);
                gDistanceJudgement->start();
		        state=60;
            }
        break;

        case 100:
            gEV3ColorSensor->getColorBrightness();
		    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
		    sprintf(buf, "Calibration");
		    ev3_lcd_draw_string(buf, 0, CALIB_FONT_HEIGHT * 1);
		    sprintf(buf, "Hue : %f", gEV3ColorSensor->getHue());
		    ev3_lcd_draw_string(buf, 0, CALIB_FONT_HEIGHT * 2);		    
            sprintf(buf, "Saturation : %f", gEV3ColorSensor->getSaturation());
		    ev3_lcd_draw_string(buf, 0, CALIB_FONT_HEIGHT * 3);		    
            sprintf(buf, "getBright : %f", gEV3ColorSensor->getBright());
		    ev3_lcd_draw_string(buf, 0, CALIB_FONT_HEIGHT * 4);
        break;
    }
    ext_tsk();
}