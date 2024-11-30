#ifndef ROTATE_MACHINE_ACTION_H
#define ROTATE_MACHINE_ACTION_H

#include "Action.h"
#include "Math.h"

class RotateMachineAction : public Action
{
public:
	explicit RotateMachineAction();
	virtual ~RotateMachineAction();

	void start();
	void start2();
	void right();
	void right2();
	void rightback();
	void leftback();
	void Justleft();
	void Justright();
	void stop();
	void updateParameter();
	bool isFinished();
	void updateSpeed(int speed);

private:
	int state = 0;
	int state2 = 0;
	int state3 = 0;
	int state4 = 0;
	int state5 = 0;
	int state6 = 0;
	int state7 = 0;	
	int state8 = 0;	
	bool flag = false;
	int targetAngle;
	double startAngle;
	double angle[2] = {0, 0};
	double currentAngle;
	int power;
	bool forward = false;
};

#endif
