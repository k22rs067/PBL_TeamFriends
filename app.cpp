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
#include "ArmPositionSetAction.h"
#include "FreeAreaTactics.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* LCD?ｿｽt?ｿｽH?ｿｽ?ｿｽ?ｿｽg?ｿｽT?ｿｽC?ｿｽY */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (12 /*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (16 /*TODO: magic number*/)
#define N 10

// using?ｿｽ骭ｾ
using ev3api::Motor;
using ev3api::ColorSensor;
// using ev3api::Clock;
using ev3api::TouchSensor;

// Device objects
// ?ｿｽI?ｿｽu?ｿｽW?ｿｽF?ｿｽN?ｿｽg?ｿｽ?ｿｽﾃ的?ｿｽﾉ確?ｿｽﾛゑｿｽ?ｿｽ?ｿｽ
Motor gArmMotor(PORT_A);
Motor gRightWheel(PORT_B);
Motor gLeftWheel(PORT_C);
ColorSensor gColorSensor(PORT_2);
TouchSensor gTouchSensor(PORT_1);

// ?ｿｽI?ｿｽu?ｿｽW?ｿｽF?ｿｽN?ｿｽg?ｿｽﾌ抵ｿｽ`
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
static ArmPositionSetAction *gArmPositionSetAction;
static FreeAreaTactics *gFreeAreaTactics;

//static SpeedAdjustment *gSpeedAdjustment;

static void user_system_create()
{
    // ?ｿｽI?ｿｽu?ｿｽW?ｿｽF?ｿｽN?ｿｽg?ｿｽﾌ撰ｿｽ?ｿｽ?ｿｽ
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
    gArmPositionSetAction = new ArmPositionSetAction();
    gRunStraightAction = new RunStraightAction();
    gRotateMachineAction = new RotateMachineAction();
    gRotateAction = new RotateAction(gRotateMachineAction);
    // gCurvatureRunAction = new CurvatureRunAction();
    // gDecelerationRotaryAction = new DecelerationRotaryAction();
    // gSectionControlTactics = new SectionControlTactics(gColorSensor);
    gLapSectionTactics = new LapSectionTactics();
    gFreeAreaTactics = new FreeAreaTactics();
    // gCalibration = new Calibration(gTouchSensor, gRunParameter, gTimerJudgement, gEV3ColorSensor, gRearMotor, gCalcCurrentLocation);
    // gIPCommunication = new IPCommunication();
    // gBlockBingo = new BlockBingo(gRearMotor);

    // gAlgori = new Algori();

    // gCleaningPutAction = new CleaningPutAction();

    // //Action?ｿｽN?ｿｽ?ｿｽ?ｿｽX?ｿｽﾉ参?ｿｽﾆゑｿｽﾝ定す?ｿｽ?ｿｽ
    Action::setObject(gRunParameter, gRearMotor, gArmControl, gEV3ColorSensor, gCalcCurrentLocation, gLineTraceAction, gRunStraightAction, gArmPositionSetAction);
    // //Tactics?ｿｽN?ｿｽ?ｿｽ?ｿｽX?ｿｽﾉ参?ｿｽﾆゑｿｽﾝ定す?ｿｽ?ｿｽ
    Tactics::setObject(gEV3ColorSensor, gRunParameter, gCalcCurrentLocation, gDistanceJudgement, gLineTraceAction, gRunStraightAction, gRotateMachineAction, gRotateAction, gArmControl);

    // LED?ｿｽ?ｿｽ?ｿｽI?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽW?ｿｽﾉ鯉ｿｽ?ｿｽ轤ｹ?ｿｽ?ｿｽ
    ev3_led_set_color(LED_ORANGE);
}

/*
static void user_system_destroy()
{
    //?ｿｽ?ｿｽ?ｿｽ[?ｿｽ^?ｿｽﾌエ?ｿｽ?ｿｽ?ｿｽR?ｿｽ[?ｿｽ_?ｿｽl?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽZ?ｿｽb?ｿｽg
    gRightWheel.reset();
    gLeftWheel.reset();
    // gArmMotor.reset();
    // gTailMotor.reset();

    //?ｿｽI?ｿｽu?ｿｽW?ｿｽF?ｿｽN?ｿｽg?ｿｽﾌ削除
}
*/

void main_task(intptr_t unused) 
{
    user_system_create(); // ?ｿｽZ?ｿｽ?ｿｽ?ｿｽT?ｿｽ窿ゑｿｽ[?ｿｽ^?ｿｽﾌ擾ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ
    sta_cyc(EV3_CYC_RUN);
    slp_tsk();
    stp_cyc(EV3_CYC_RUN);
    ext_tsk();
}

static int state = 0;
//static int state = 100; //?ｿｽF?ｿｽ?ｿｽ?ｿｽm
static char buf[100];

void run_task(intptr_t unused) 
{
    /*
    char buf[100];
    sprintf(buf, "Brightness: %lf", gEV3ColorSensor->getColorBrightness());
    //sprintf(buf, "Brightness: %d", gEV3ColorSensor->getBrightness());
    gDisplay->display(buf,0,0);
    */
    gCalcCurrentLocation->calcCurrentLocation(); //?ｿｽv?ｿｽZ?ｿｽ?ｿｽ?ｿｽ\?ｿｽb?ｿｽh
    switch(state){
        case 0:
        if (gButton->Touch_sensor_isPressed())//gButton->button_left_isPressed()
        {
            //state = 5;
            state = 10;
            //state = 50;
        }
        break;

        case 5:
            gArmControl->setPower(10);
            if (gArmControl->getEncoder()>=0)
            {
	            ev3_speaker_play_tone(NOTE_G6, 100);
		        gArmControl->setPower(0);	//?ｿｽA?ｿｽ[?ｿｽ?ｿｽ?ｿｽ?ｿｽ~
		        gArmControl->setBrake(true);
		        gArmControl->resetEncoder();	//?ｿｽG?ｿｽ?ｿｽ?ｿｽR?ｿｽ[?ｿｽ_?ｿｽl?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽZ?ｿｽb?ｿｽg
                state = 10;
            }
        break;

        case 10:
            gLapSectionTactics->execute();
            if(gLapSectionTactics->isFinished())
            {
                state=20;
            }
        break;

        case 20:
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
            gFreeAreaTactics->execute();
            if(gFreeAreaTactics->isFinished())
            {
                state=999;
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