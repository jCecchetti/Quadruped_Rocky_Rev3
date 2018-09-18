/*
 * Leg.cpp
 *
 *  Created on: Aug 4, 2018
 *      Author: julia
 */

#include "Leg.h"
#include <math.h>
#include "Position.h"
#include <iostream>
#include "Constants.h"
#include "PWM.h"

Leg::Leg(){

}
Leg::Leg(int hipChannel, int kneeChannel, int ankleChannel, bool left){
	this->left = left;
	this->hipChannel = hipChannel;
	this->kneeChannel = kneeChannel;
	this->ankleChannel = ankleChannel;
}

bool Leg::setFootPos(Position pos){
		calculateAngles(pos.x, pos.y, pos.z);
		//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
		setAngle(hipChannel, hipAngle-90);
		setAngle(kneeChannel, kneeAngle-90);
		setAngle(ankleChannel, ankleAngle-90);

		return true;
}

bool Leg::calculateAngles(double x, double y, double z){

	if(!left) y = -y;

	double C = pow(z*z + y*y, 0.5);

	double c = pi/2 + atan(FEMUR/SERVOWIDTH*2);//Okay
	double A = pow(FEMUR*FEMUR + SERVOWIDTH*SERVOWIDTH/4, 0.5);
	if((left && y > 0) || (!left && y > 0)) hipAngle = hipCenter - (pi - c - asin(A*sin(c)/C) + acos(-z/C) - atan(SERVOWIDTH/FEMUR/2));
	else hipAngle = hipCenter - (pi - c - asin(A*sin(c)/C) - acos(-z/C) - atan(SERVOWIDTH/FEMUR/2));
	if(!left){
		if(y > 0) hipAngle = hipCenter - (hipAngle - hipCenter);
		else hipAngle =  hipCenter + (hipCenter - hipAngle);
	}
	double B = C * sin(pi - c - asin(A*sin(c)/C))/sin(c);
	double L = sqrt(B*B + x*x);
	double absoluteKneeAngle = acos((L*L + TIBIA*TIBIA - TARSUS*TARSUS)/(2*L*TIBIA));
	kneeAngle = kneeCenter - (absoluteKneeAngle - atan2(x, B));
	if(left) ankleAngle = ankleCenter + (pi - acos((TIBIA*TIBIA + TARSUS*TARSUS - L*L)/(2*TIBIA*TARSUS)));
	else ankleAngle = pi - (ankleCenter + (pi - acos((TIBIA*TIBIA + TARSUS*TARSUS - L*L)/(2*TIBIA*TARSUS))));

	hipAngle *= 57.2958;
	kneeAngle *= 57.2958;
	ankleAngle *= 57.2958;

	//std::cout << hipAngle << std::endl;
	//std::cout << kneeAngle << std::endl;
	//std::cout << ankleAngle << "\n" << std::endl;

	return true;
}

Leg::~Leg() {
	// TODO Auto-generated destructor stub
}

