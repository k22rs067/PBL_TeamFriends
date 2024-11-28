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

/* LCD�t�H���g�T�C�Y */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6 /*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8 /*TODO: magic number*/)

// using�錾
using ev3api::Motor;
using ev3api::ColorSensor;
// using ev3api::Clock;
using ev3api::TouchSensor;

// Device objects
// �I�u�W�F�N�g��ÓI�Ɋm�ۂ���
Motor gArmMotor(PORT_A);
Motor gRightWheel(PORT_B);
Motor gLeftWheel(PORT_C);
ColorSensor gColorSensor(PORT_2);
TouchSensor gTouchSensor(PORT_1);

// �I�u�W�F�N�g�̒�`
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
    // �I�u�W�F�N�g�̐���
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

    // //Action�N���X�ɎQ�Ƃ�ݒ肷��
    Action::setObject(gRunParameter, gRearMotor, gArmControl, gEV3ColorSensor, gCalcCurrentLocation, gLineTraceAction, gRunStraightAction);
    // //Tactics�N���X�ɎQ�Ƃ�ݒ肷��
    // Tactics::setObject(gEV3ColorSensor, gEV3SonarSensor, gEV3GyroSensor, gRunParameter, gCalcCurrentLocation,gDistanceJudgement, gTimerJudgement, gStraightDetection, gArmPositionSetAction, gLineTraceAction, gRunStraightAction, gRotateMachineAction, gRotateAction, gCurvatureRunAction, gDecelerationRotaryAction);

    // LED���I�����W�Ɍ��点��
    ev3_led_set_color(LED_ORANGE);
}

/*
static void user_system_destroy()
{
    //���[�^�̃G���R�[�_�l�����Z�b�g
    gRightWheel.reset();
    gLeftWheel.reset();
    // gArmMotor.reset();
    // gTailMotor.reset();

    //�I�u�W�F�N�g�̍폜
}
*/

void main_task(intptr_t unused) 
{
    user_system_create(); // �Z���T�⃂�[�^�̏���������
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

    gCalcCurrentLocation->calcCurrentLocation(); //�v�Z���\�b�h
  
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