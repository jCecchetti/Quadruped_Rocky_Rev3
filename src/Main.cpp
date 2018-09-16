
#include <stdio.h>
#include "Leg.h"
#include "PositionCluster.h"
#include <iostream>
#include "RobotMotion.h"
#include <chrono>
#include <ctime>
#include "Timer.h"


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
		Position(Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0,0,0,0),
		Position(-Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0,0,0,0));
double g_stepLengthX = 0;
double g_stepLengthY = 0;


int main(int argc, char *argv[])
{
	Leg frontLeftLeg(12, 13, 14, true);
	Leg frontRightLeg(8, 9, 10, false);
	Leg rearLeftLeg(4, 5, 6, true);
	Leg rearRightLeg(0, 1, 2, false);

	RobotMotion motion(frontLeftLeg, frontRightLeg, rearLeftLeg, rearRightLeg);
	//std::cout << "YAY" << std::endl;

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

	while(totalSeconds < 5){
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
	}

	return 0;
}
