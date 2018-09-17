/*
 * RobotMotion.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: julia
 */

#include "RobotMotion.h"
#include "math.h"
//#include "Body.h"

RobotMotion::RobotMotion(Leg frontLeftLeg, Leg frontRightLeg, Leg hindLeftLeg, Leg hindRightLeg) {
	this->frontLeftLeg = frontLeftLeg;
	this->frontRightLeg = frontRightLeg;
	this->hindLeftLeg = hindLeftLeg;
	this->hindRightLeg = hindRightLeg;

}

void RobotMotion::updateGlobalRobotPos(){

}

void RobotMotion::setWantedState(State wantedState){

	switch(wantedState){
	case walking:
		handleWalkingLegs();
		break;
	case trotting:
		handleTrottingLegs();
		break;
	case laying:
		break;
	case stopping:
	case stopped:
		home();
		break;
	case standing:
		handleStanding();
		break;
	}
}

void RobotMotion::update(){

	if(false) currentState = stopped;
	else if(false) currentState = trotting;
	else if(true) currentState = walking;
	else if(false) end = true;
	else if(true) currentState = standing;
	setWantedState(currentState);
}

void RobotMotion::handleWalkingLegs(){
	updateGlobalRobotPos();
	g_globalStepCenter = Body::getGlobalStepCenter(g_localRobotPos, g_globalRobotPos);
	g_globalCornerPos = Body::getGlobalCornerPos(g_localRobotPos, g_globalRobotPos);
	frontLeftLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[0], g_globalFeetPos.position[0]));
	frontRightLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[1], g_globalFeetPos.position[1]));
	hindLeftLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[2], g_globalFeetPos.position[2]));
	hindRightLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[3], g_globalFeetPos.position[3]));
	g_stepLengthX = currentRobotSpeedX*stepTime*2.0;
	g_stepLengthY = currentRobotSpeedY*stepTime*2.0;
	switch(steppingLeg){
	case frontLeft:
		if(step.shiftCoM(frontLeft) && step.updateStep()){
			steppingLeg = rearLeft;
			step.newStep(2);
		}
		break;
	case rearLeft:
		if(step.shiftCoM(rearLeft) && step.updateStep()){
			steppingLeg = rearRight;
			step.newStep(3);
		}
		break;
	case frontRight:
		if(step.shiftCoM(frontRight) && step.updateStep()){
			steppingLeg = frontLeft;
			step.newStep(0);
		}
		break;
	case rearRight:
		if(step.shiftCoM(rearRight) && step.updateStep()){
			steppingLeg = frontRight;
			step.newStep(1);
		}
		break;
	}
	if(steppingLeg != lastSteppingLeg) g_lastGlobalStepCenter.copy(g_globalStepCenter);
	lastSteppingLeg = steppingLeg;
}

void RobotMotion::handleTrottingLegs(){
	updateGlobalRobotPos();
	g_globalStepCenter = Body::getGlobalStepCenter(g_localRobotPos, g_globalRobotPos);
	g_globalCornerPos = Body::getGlobalCornerPos(g_localRobotPos, g_globalRobotPos);
	frontLeftLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[0], g_globalFeetPos.position[0]));
	frontRightLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[1], g_globalFeetPos.position[1]));
	hindLeftLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[2], g_globalFeetPos.position[2]));
	hindRightLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[3], g_globalFeetPos.position[3]));
	g_stepLengthX = currentRobotSpeedX*stepTime*2.0;
	g_stepLengthY = currentRobotSpeedY*stepTime*2.0;
	switch(steppingLeg){
	case rearRight:
	case frontLeft:
		if(step.balanceCoM(steppingLeg) && (step.updateFastStep() & stepMir.updateFastStep())){
			steppingLeg = frontRight;
			step.newStep(2);
			stepMir.newStep(1);
		}
		break;
	case rearLeft:
	case frontRight:
		if(step.balanceCoM(steppingLeg) && (step.updateFastStep() & stepMir.updateFastStep())){
			steppingLeg = frontLeft;
			step.newStep(0);
			stepMir.newStep(3);
		}
		break;
	}
	if(steppingLeg != lastSteppingLeg){
		g_lastGlobalStepCenter.copy(g_globalStepCenter);
	}
	lastSteppingLeg = steppingLeg;
}

bool RobotMotion::home(){
	return false;
}

void RobotMotion::handleStanding(){
	updateGlobalRobotPos();
	g_globalCornerPos = Body::getGlobalCornerPos(g_localRobotPos, g_globalRobotPos);
	frontLeftLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[0], g_globalFeetPos.position[0]));
	frontRightLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[1], g_globalFeetPos.position[1]));
	hindLeftLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[2], g_globalFeetPos.position[2]));
	hindRightLeg.setFootPos(Body::getRelativeFootPos(g_globalCornerPos.position[3], g_globalFeetPos.position[3]));

}

RobotMotion::~RobotMotion() {
	// TODO Auto-generated destructor stub
}

