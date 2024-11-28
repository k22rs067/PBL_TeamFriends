#ifndef BOTTON_SENSOR_H
#define BOTTON_SENSOR_H

#include "ev3api.h"
#include "TouchSensor.h"

class Button
{
    public:
    explicit Button(ev3api::TouchSensor &touchSensor);
    virtual ~Button();
    bool Touch_sensor_isPressed();
    bool button_left_isPressed();

    private:
    	ev3api::TouchSensor &touch_sensor;
};
#endif