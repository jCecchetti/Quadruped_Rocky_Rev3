/*
 * Leg.h
 *
 *  Created on: Aug 4, 2018
 *      Author: julia
 */

#ifndef LEG_H_
#define LEG_H_

class Position;

class Leg {
public:
	Leg();
	Leg(int, int, int, bool);
	bool setFootPos(Position);
	virtual ~Leg();

private:
	bool calculateAngles(double, double, double);
	//AdafruitServo servo1, servo2, servo3;

	double pi = 3.1416;

	double hipAngle = pi/2.0;
	double kneeAngle = pi/2.0;
	double ankleAngle = pi/2.0;
	float hipCenter = pi/2.0;
	float kneeCenter = pi/2.0;
	float ankleCenter = 7/180.0*pi;

	float minimumPulseWidth = 0.6f;
	float neutralPulseWidth = 1.575f;
	float maximumPulseWidth = 2.55f;

	double FEMUR = 1.6;
	double TIBIA = 2.3585;
	double TARSUS = 3.4;
	double SERVOWIDTH = 1.927;

	int hipChannel;
	int kneeChannel;
	int ankleChannel;

	bool left = false;
};

#endif /* LEG_H_ */
