#include "Button.h"

Button::Button(ev3api::TouchSensor &touchSensor)
    : touch_sensor(touchSensor)
{
}

Button::~Button()
{
}

bool Button::Touch_sensor_isPressed() 
{
    return ev3_touch_sensor_is_pressed((sensor_port_t)PORT_1);
}

bool Button::button_left_isPressed() 
{
    return ev3_button_is_pressed(LEFT_BUTTON);
}