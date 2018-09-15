
#include <stdio.h>
#include "Leg.h"
#include "PositionCluster.h"
#include <iostream>
#include "RobotMotion.h"

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
	Leg frontLeftLeg;
	Leg frontRightLeg;
	Leg rearLeftLeg;
	Leg rearRightLeg;

	RobotMotion motion(frontLeftLeg, frontRightLeg, rearLeftLeg, rearRightLeg);
	motion.update();
	std::cout << "YAY" << std::endl;

	//time timer = time();
	/*double fps = 60;// updates per second
	double timePerTick = 1000000000/fps;
	double delta = 0;
	long now;
	long lastTime = 0;//nanotime
	long timer = 0;
	int ticks = 0;
	long totalSeconds = 0;
	bool running = true;*/

	/*
	while(running){
		now = std::chrono::system_clock::now();
		delta += (now - lastTime) / timePerTick;
		timer += now - lastTime;
		lastTime = now;
		//cout << now;

		if(delta >= 1){
			//update();
			ticks++;
			delta--;
			//if(motion.end) running = false;
		}

		if(timer >= 1000000000){
			//System.out.println("Ticks and Frames " + ticks);
			timer = 0;
			ticks = 0;
			totalSeconds++;
		}
	}*/

	return 0;
}
