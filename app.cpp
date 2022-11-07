/**
 * This sample program balances a two-wheeled Segway type robot such as Gyroboy in EV3 core set.
 *
 * References:
 * http://www.hitechnic.com/blog/gyro-sensor/htway/
 * http://www.cs.bgu.ac.il/~ami/teaching/Lejos-2013/classes/src/lejos/robotics/navigation/Segoway.java
 */

#include "ev3api.h"
#include "app.h"

#include "libcpp-test.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/**
 * �Z���T�[�A���[�^�[�̐ڑ����`���܂�
 */
static const sensor_port_t
    touch_sensor    = EV3_PORT_1,
    color_sensor    = EV3_PORT_2,
    sonar_sensor    = EV3_PORT_3,
    gyro_sensor     = EV3_PORT_4;

static const motor_port_t
    left_motor      = EV3_PORT_C,
    right_motor     = EV3_PORT_B;



/**
* Button �N���X
*/
class Button {
public:
    /**
    * �R���X�g���N�^
    */
    Button() {
    }

    /**
    * ����
    */
    bool isPressed() {
        return( ev3_touch_sensor_is_pressed( touch_sensor ) );
    }
};

/**
* RunControl �N���X
*/
class RunControl {
public:
    /**
    * �R���X�g���N�^
    */
    RunControl() {
    }

    /**
    * ����
    */
    void stop() {
        ev3_motor_stop(right_motor, true);
        ev3_motor_stop(left_motor, true);
    }

    void turn(int speed) {
        ev3_motor_set_power(right_motor, speed);
        ev3_motor_set_power(left_motor, -speed);
    }

    void forward(int speed) {
        ev3_motor_set_power(right_motor, speed);
        ev3_motor_set_power(left_motor,  speed);
    }
};

/**
* ObstacleDetection �N���X
*/
class ObstacleDetection {
public:
    /**
    * ����
    */
    int obsDistance;
    
    /**
    * �֘A
    */
    
    /**
    * �R���X�g���N�^
    */
    ObstacleDetection() {
        /* 10[cm] */
        obsDistance = 10;
    }

    /**
    * ����
    */
    bool isDetected() {
        return( ev3_ultrasonic_sensor_get_distance(sonar_sensor) < obsDistance );
    }
};

/**
 * Tango�N���X
 */
class TangoClass {
public:

    /**
    * ���
    */
    enum RunState {
        STATE_STOP    = 0,
        STATE_TURN    = 1,
        STATE_FORWARD = 2,
    };

    /**
    * �R���X�g���N�^
    */
    TangoClass() {
        ev3_lcd_draw_string("Tango Class is created.", 0, 16);

        /* �Z���T�[���̓|�[�g�̐ݒ� */
        ev3_sensor_config(sonar_sensor, ULTRASONIC_SENSOR);
        ev3_sensor_config(color_sensor, COLOR_SENSOR);
        ev3_color_sensor_get_reflect(color_sensor); /* ���˗����[�h */
        ev3_sensor_config(touch_sensor, TOUCH_SENSOR);

        /* ���[�^�[�o�̓|�[�g�̐ݒ� */
        ev3_motor_config(left_motor, LARGE_MOTOR);
        ev3_motor_config(right_motor, LARGE_MOTOR);

        state = STATE_STOP;
        turnSpeed = 20;
        forwardSpeed = 30;
    }

    /**
    * ����
    */
    /* ��~��� �^�b�`�Z���T�����҂� */
    void procStopState() {
        runControl.stop();
    
        while(1) {
            if( runButton.isPressed() ) {
                state = STATE_TURN;
                break;
            };
            
            tslp_tsk(200 * 1000U); /* 200 msec�����N�� */
        };
    }

    /* ��]��� */
    void procTurnState() {
        while(1) {
            if( runButton.isPressed() ) {
                state = STATE_STOP;
                break;
            };
            
            if( obstacleDetection.isDetected() == false ) {
                state = STATE_FORWARD;
                break;
            };
            
            runControl.turn( turnSpeed );
            
            tslp_tsk(200 * 1000U); /* 200 msec�����N�� */
        };
        
        runControl.stop();
    }

    /* �O�i��� */
    void procForwardState() {
        while(1) {
            if( runButton.isPressed() ) {
                state = STATE_STOP;
                break;
            };
            
            if( obstacleDetection.isDetected() ) {
                state = STATE_TURN;
                break;
            };
        
            runControl.forward( forwardSpeed );
        
            tslp_tsk(200 * 1000U); /* 200 msec�����N�� */
        };
        
        runControl.stop();
    }

    void start() {
        while(1) {
            ev3_lcd_draw_string("                ", 0, 26);
            if( state == STATE_STOP ) {
                ev3_lcd_draw_string("Stop.", 0, 26);
                procStopState();
            } else if( state == STATE_TURN ) {
                ev3_lcd_draw_string("Turn.", 0, 26);
                procTurnState();
            } else if( state == STATE_FORWARD ) {
                ev3_lcd_draw_string("Forward.", 0, 26);
                procForwardState();
            } else {
                ev3_lcd_draw_string("State Invalid.", 0, 26);
            };
            
            tslp_tsk(100 * 1000U); /* 100 msec�����N�� */
        };
    }

private:
    /**
    * ����
    */
    int state;
    int turnSpeed;
    int forwardSpeed;
  
    /**
    * �֘A
    */
    Button            runButton;          /* Button�N���X */
    RunControl        runControl;         /* RunControl�N���X */
    ObstacleDetection obstacleDetection;  /* ObstacleDetection�N���X */
};


/* Tango�I�u�W�F�N�g���� */
TangoClass tango;

void main_task(intptr_t unused) {
    /* Tango start */
    tango.start();
}
