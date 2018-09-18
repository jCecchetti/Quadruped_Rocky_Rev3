
#include <stdio.h>
#include <vector>
#include "Leg.h"
#include "PositionCluster.h"
#include <iostream>
#include "RobotMotion.h"
#include <chrono>
#include <ctime>
#include "Timer.h"
#include "PWM.h"

#include <iomanip>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#define JOY_DEV "/dev/input/js0"

using namespace std;

Position g_globalRobotPos(0.0,0.0,6.5,0.0,0.0,0.0);
Position g_localRobotPos(0.0,0.0,0.0,0.0,0.0,0.0);
PositionCluster g_globalFeetPos(Position(Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0));
PositionCluster g_globalCornerPos(Position(Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0));
PositionCluster g_globalStepCenter(Position(Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0));
PositionCluster g_lastGlobalStepCenter(Position(Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(	Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0));
double g_stepLengthX = 0;
double g_stepLengthY = 0;
vector<char> joy_button;
vector<int> joy_axis;


int main(int argc, char *argv[])
{
	int joy_fd(-1), num_of_axis(0), num_of_buttons(0);
	char name_of_joystick[80];


	if((joy_fd=open(JOY_DEV,O_RDONLY)) < 0)
	{
		cerr<<"Failed to open "<<JOY_DEV<<endl;
		return -1;
	}

	ioctl(joy_fd, JSIOCGAXES, &num_of_axis);
	ioctl(joy_fd, JSIOCGBUTTONS, &num_of_buttons);
	ioctl(joy_fd, JSIOCGNAME(80), &name_of_joystick);

	joy_button.resize(num_of_buttons,0);
	joy_axis.resize(num_of_axis,0);

	cout<<"Joystick: "<<name_of_joystick<<endl
			<<"  axis: "<<num_of_axis<<endl
			<<"  buttons: "<<num_of_buttons<<endl;

	fcntl(joy_fd, F_SETFL, O_NONBLOCK);   // using non-blocking mode

	Timer loopTimer;
	double fps = 40.0;// updates per second
	double timePerTick = 1000/fps;
	double delta = 0;
	double now = loopTimer.getMillis();
	double lastTime = now;
	double timer = 0;
	int ticks = 0;
	long totalSeconds = 0;
	//bool running = true;

	initPWM(0x40);
	Leg frontLeftLeg(12, 13, 14, true);
	Leg frontRightLeg(8, 9, 10, false);
	Leg rearLeftLeg(4, 5, 6, true);
	Leg rearRightLeg(0, 1, 2, false);

	RobotMotion motion(frontLeftLeg, frontRightLeg, rearLeftLeg, rearRightLeg);

	while(totalSeconds < 20){
		now = loopTimer.getMillis();
		delta += (now - lastTime)/timePerTick;
		timer += now - lastTime;
		lastTime = now;

		if(delta >= 1){
			motion.update();
			ticks++;
			delta--;
			//if(motion.end) running = false;
		}

		if(timer >= 1000){
			std::cout << "Updates per Second " <<  ticks << std::endl;
			timer = 0;
			ticks = 0;
			totalSeconds++;
		}

		js_event js;

		read(joy_fd, &js, sizeof(js_event));

		switch (js.type & ~JS_EVENT_INIT)
		{
		case JS_EVENT_AXIS:
			if((int)js.number>=joy_axis.size())  {cerr<<"err:"<<(int)js.number<<endl; continue;}
			joy_axis[(int)js.number]= js.value;
			break;
		case JS_EVENT_BUTTON:
			if((int)js.number>=joy_button.size())  {cerr<<"err:"<<(int)js.number<<endl; continue;}
			joy_button[(int)js.number]= js.value;
			break;
		}

		cout<<"axis: ";
		for(size_t i(0);i<joy_axis.size();++i)
			cout<<" "<<setw(2)<<joy_axis[i];
		cout<<endl;

		cout<<"  button: ";
		for(size_t i(0);i<joy_button.size();++i)
			cout<<" "<<(int)joy_button[i];
		cout<<endl;
	}

	return 0;
}


/*
int main()
{


  while(true)
  {
    js_event js;

    read(joy_fd, &js, sizeof(js_event));

    switch (js.type & ~JS_EVENT_INIT)
    {
    case JS_EVENT_AXIS:
      if((int)js.number>=joy_axis.size())  {cerr<<"err:"<<(int)js.number<<endl; continue;}
      joy_axis[(int)js.number]= js.value;
      break;
    case JS_EVENT_BUTTON:
      if((int)js.number>=joy_button.size())  {cerr<<"err:"<<(int)js.number<<endl; continue;}
      joy_button[(int)js.number]= js.value;
      break;
    }

    cout<<"axis/10000: ";
    for(size_t i(0);i<joy_axis.size();++i)
      cout<<" "<<setw(2)<<joy_axis[i]/10000;
    cout<<endl;

    cout<<"  button: ";
    for(size_t i(0);i<joy_button.size();++i)
      cout<<" "<<(int)joy_button[i];
    cout<<endl;

    usleep(100);
  }

  close(joy_fd);
  return 0;
}*/
