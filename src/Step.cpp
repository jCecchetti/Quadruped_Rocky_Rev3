/*
 * Step.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: julia
 */

#include "Step.h"

Step::Step() {

}

bool Step::updateStep(){
	if(!startedStepping) stepTimer.reset();//timer doesn't start until updateStep() is first called
	startedStepping = true;
	if(stepTimer.getSeconds() < .15){
		g_globalFeetPos.position[leg].z = stepHeight;
		//System.out.println("lifting");
	}
	else if(stepTimer.getSeconds() < .4){
		g_globalFeetPos.position[leg].x = g_lastGlobalStepCenter.position[leg].x + g_stepLengthX;
		g_globalFeetPos.position[leg].y = g_lastGlobalStepCenter.position[leg].y + g_stepLengthY;
		g_globalFeetPos.position[leg].z = stepHeight;
	}
	else if(stepTimer.getSeconds() < .5){
		g_globalFeetPos.position[leg].x = g_lastGlobalStepCenter.position[leg].x + g_stepLengthX;
		g_globalFeetPos.position[leg].y = g_lastGlobalStepCenter.position[leg].y + g_stepLengthY;
		g_globalFeetPos.position[leg].z = 0;
		//g_localRobotPos.y = -.5;
	}
	else{
		finishedStepping = true;
	}
	return finishedStepping;
}

bool Step::updateFastStep(){
	if(!startedStepping) stepTimer.reset();//timer doesn't start until updateStep() is first called
	startedStepping = true;
	if(stepTimer.getSeconds() < .15){
		g_globalFeetPos.position[leg].x = g_lastGlobalStepCenter.position[leg].x + g_stepLengthX;
		g_globalFeetPos.position[leg].y = g_lastGlobalStepCenter.position[leg].y + g_stepLengthY;
		g_globalFeetPos.position[leg].z = stepHeight/2.0;
	}
	else if(stepTimer.getSeconds() < .4){
		g_globalFeetPos.position[leg].x = g_lastGlobalStepCenter.position[leg].x + g_stepLengthX;
		g_globalFeetPos.position[leg].y = g_lastGlobalStepCenter.position[leg].y + g_stepLengthY;
		g_globalFeetPos.position[leg].z = 0;
		//g_localRobotPos.y = -.5;
	}
	else{
		finishedStepping = true;
	}
	return finishedStepping;
}

bool Step::shiftCoM(int steppingLeg){
	double speed = shiftSpeed/updateRate;
	Position adjustedCoMPos = Body::getGlobalAdjustedCoMPos(g_localRobotPos, g_globalRobotPos, steppingLeg);
	switch(steppingLeg){
	case legID::frontLeft:
		if(!CoMStable(g_globalFeetPos.position[1], g_globalFeetPos.position[2], g_globalFeetPos.position[3], adjustedCoMPos)){
			double dist = distance(adjustedCoMPos, g_globalFeetPos.position[3]);
			g_localRobotPos.y += speed*(g_globalFeetPos.position[3].y - adjustedCoMPos.y)/dist;
			g_localRobotPos.x += speed*(g_globalFeetPos.position[3].x - adjustedCoMPos.x)/dist;
		}
		else return true;
		break;
	case legID::frontRight:
		if(!CoMStable(g_globalFeetPos.position[0], g_globalFeetPos.position[2], g_globalFeetPos.position[3], adjustedCoMPos)){
			double dist = distance(adjustedCoMPos, g_globalFeetPos.position[2]);
			g_localRobotPos.y += speed*(g_globalFeetPos.position[2].y - adjustedCoMPos.y)/dist;
			g_localRobotPos.x += speed*(g_globalFeetPos.position[2].x - adjustedCoMPos.x)/dist;
		}
		else return true;
		break;
	case legID::rearLeft:
		if(!CoMStable(g_globalFeetPos.position[0], g_globalFeetPos.position[1], g_globalFeetPos.position[3], adjustedCoMPos)){
			double dist = distance(adjustedCoMPos, g_globalFeetPos.position[1]);
			g_localRobotPos.y += speed*(g_globalFeetPos.position[1].y - adjustedCoMPos.y)/dist;
			g_localRobotPos.x += speed*(g_globalFeetPos.position[1].x - adjustedCoMPos.x)/dist;
		}
		else return true;
		break;
	case legID::rearRight:
		if(!CoMStable(g_globalFeetPos.position[0], g_globalFeetPos.position[1], g_globalFeetPos.position[2], adjustedCoMPos)){
			double dist = distance(adjustedCoMPos, g_globalFeetPos.position[0]);
			g_localRobotPos.y += speed*(g_globalFeetPos.position[0].y - adjustedCoMPos.y)/dist;
			g_localRobotPos.x += speed*(g_globalFeetPos.position[0].x - adjustedCoMPos.x)/dist;
		}
		else return true;
		break;
	}
	return false;
}

bool Step::balanceCoM(int steppingLeg){
	double speed = shiftSpeed/updateRate;
	Position CoMPos = Body::getGlobalCoMPos(g_localRobotPos, g_globalRobotPos);
	Position frontBalanceLimit = Body::getGlobalAdjustedCoMPos(g_localRobotPos, g_globalRobotPos, steppingLeg);
	Position rearBalanceLimit = Body::getGlobalAdjustedCoMPos(g_localRobotPos, g_globalRobotPos, 3 - steppingLeg);
	switch(steppingLeg){
	case legID::rearRight:
	case legID::frontLeft:
		if(!CoMStable(g_globalFeetPos.position[1], g_globalFeetPos.position[2], g_globalFeetPos.position[3], CoMPos)){
			double dist = distance(CoMPos, g_globalFeetPos.position[3]);
			g_localRobotPos.y += speed*(g_globalFeetPos.position[3].y - CoMPos.y)/dist;
			g_localRobotPos.x += speed*(g_globalFeetPos.position[3].x - CoMPos.x)/dist;
		}
		else{
			double dist = distance(CoMPos, g_globalFeetPos.position[3]);
			g_localRobotPos.y -= speed*(g_globalFeetPos.position[3].y - CoMPos.y)/dist;
			g_localRobotPos.x -= speed*(g_globalFeetPos.position[3].x - CoMPos.x)/dist;
		}
		if(CoMStable(g_globalFeetPos.position[1], g_globalFeetPos.position[2], g_globalFeetPos.position[3], frontBalanceLimit) &&
				!CoMStable(g_globalFeetPos.position[1], g_globalFeetPos.position[2], g_globalFeetPos.position[3], rearBalanceLimit));
		else return true;
		break;
	case legID::rearLeft:
	case legID::frontRight:
		if(!CoMStable(g_globalFeetPos.position[0], g_globalFeetPos.position[2], g_globalFeetPos.position[3], CoMPos)){
			double dist = distance(CoMPos, g_globalFeetPos.position[2]);
			g_localRobotPos.y += speed*(g_globalFeetPos.position[2].y - CoMPos.y)/dist;
			g_localRobotPos.x += speed*(g_globalFeetPos.position[2].x - CoMPos.x)/dist;
		}
		else{
			double dist = distance(CoMPos, g_globalFeetPos.position[2]);
			g_localRobotPos.y -= speed*(g_globalFeetPos.position[2].y - CoMPos.y)/dist;
			g_localRobotPos.x -= speed*(g_globalFeetPos.position[2].x - CoMPos.x)/dist;
		}
		if(CoMStable(g_globalFeetPos.position[0], g_globalFeetPos.position[2], g_globalFeetPos.position[3], frontBalanceLimit) &&
				!CoMStable(g_globalFeetPos.position[0], g_globalFeetPos.position[2], g_globalFeetPos.position[3], rearBalanceLimit));
		else return true;
		break;

	}
	return false;
}

bool Step::homeCoM(){
	if(abs(g_localRobotPos.y) > .1) g_localRobotPos.y -= signum(g_localRobotPos.y)*shiftSpeed/updateRate;
	else g_localRobotPos.y = 0;
	if(abs(g_localRobotPos.y) > .1) g_localRobotPos.x -= signum(g_localRobotPos.x)*shiftSpeed/updateRate;
	else g_localRobotPos.x = 0;
	if(g_localRobotPos.y == 0 && g_localRobotPos.x == 0) return true;
	else return false;
}


bool Step::CoMStable(Position a, Position b, Position c, Position s){
	double as_x = s.x-a.x;
	double as_y = s.y-a.y;

	bool s_ab = (b.x-a.x)*as_y - (b.y-a.y)*as_x > 0;

	if(((c.x-a.x)*as_y - (c.y-a.y)*as_x > 0) == s_ab) return false;
	if(((c.x-b.x)*(s.y-b.y) - (c.y-b.y)*(s.x-b.x) > 0) != s_ab) return false;
	return true;
}

double Step::distance(Position CoMPos, Position globalFeetPos){
	return hypot(CoMPos.x - globalFeetPos.x, CoMPos.y - globalFeetPos.y);
}

void Step::newStep(int legnum){
	leg = legnum;
}

double Step::signum(double a){
	if(a < 0) return -1.0;
	else if(a > 0) return 1.0;
	else return 0;

}



Step::~Step() {
	// TODO Auto-generated destructor stub
}

