/*
 * RobotMotion.h
 *
 *  Created on: Sep 12, 2018
 *      Author: julia
 */

#ifndef ROBOTMOTION_H_
#define ROBOTMOTION_H_

#include "Position.h"
#include "PositionCluster.h"
#include "Timer.h"
#include "Leg.h"
#include "Constants.h"
#include "Step.h"
#include <vector>

class Leg;
//class Step;

extern Position g_globalRobotPos;
extern Position g_localRobotPos;
extern PositionCluster g_globalFeetPos;
extern PositionCluster g_globalCornerPos;
extern PositionCluster g_globalStepCenter;
extern PositionCluster g_lastGlobalStepCenter;
extern double g_stepLengthX;
extern double g_stepLengthY;
extern vector<int> joy_axis;

class RobotMotion {
public:

	enum State{walking, trotting, laying, stopped, stopping, standing};
	State currentState = standing;

	RobotMotion(Leg frontLeftLeg, Leg frontRightLeg, Leg hindLeftLeg, Leg hindRightLeg);
	virtual ~RobotMotion();
	void updateGlobalRobotPos();
	void setWantedState(State wantedState);
	void update();
	void handleWalkingLegs();
	void handleStanding();
	void handleTrottingLegs();
	bool home();
	bool end = false;

	Step step;
	Step stepMir;
	Leg leg;

	enum legID{frontLeft = 0, frontRight = 1, rearLeft = 2, rearRight = 3};
	legID steppingLeg = frontLeft;
	legID lastSteppingLeg = frontLeft;

	double stepTime = 1.0;

private:
	double robotSpeed = 1.0;// in/s
	double currentRobotSpeedX = 0;
	double currentRobotSpeedY = 0;
	double turningSpeed = 7.0;// degrees/s
	double pivotSpeed = 25.0;
	double updateRate = Constants::UPDATESPERSECOND;
	Leg frontLeftLeg, frontRightLeg, hindLeftLeg, hindRightLeg;
	double deadBand = .05;
	Timer timer;
};

#endif /* ROBOTMOTION_H_ */
