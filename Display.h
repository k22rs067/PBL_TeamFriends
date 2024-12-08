#ifndef DISPLAY_SENSOR_H
#define DISPLAY_SENSOR_H

#include "ev3api.h"

class Display
{
    public:
    explicit Display();
    virtual ~Display();
    void display(const char *str);

    private:
    int count = 0;
};
#endif
