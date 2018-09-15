/*
 * Step.h
 *
 *  Created on: Sep 13, 2018
 *      Author: julia
 */

#ifndef STEP_H_
#define STEP_H_

#include "Constants.h"
#include "Position.h"
#include "PositionCluster.h"
//#include "Globals.h"
#include "Body.h"
#include "Timer.h"

extern Position g_globalRobotPos;
extern Position g_localRobotPos;
extern PositionCluster g_globalFeetPos;
extern PositionCluster g_globalCornerPos;
extern PositionCluster g_globalStepCenter;
extern PositionCluster g_lastGlobalStepCenter;
extern double g_stepLengthX;
extern double g_stepLengthY;

class Step {
public:
	Step();
	virtual ~Step();


	Timer stepTimer;
	bool startedStepping = false;
	bool finishedStepping = false;
	int leg = 0;
	double shiftSpeed = 4.0;
	double stepHeight = 1;
	double updateRate = Constants::UPDATESPERSECOND;
	enum legID{frontLeft = 0, frontRight = 1, rearLeft = 2, rearRight = 3};

	bool updateStep();
	bool updateFastStep();
	void newStep(int);
	bool shiftCoM(int);
	bool balanceCoM(int);
	bool homeCoM();

private:
	double distance(Position CoMPos, Position globalFeetPos);
	bool CoMStable(Position a, Position b, Position c, Position s);
	double signum(double);

};

#endif /* STEP_H_ */
